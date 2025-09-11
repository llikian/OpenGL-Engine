/***************************************************************************************************
 * @file  GLTF.cpp
 * @brief Implementation of the GLTF namespace
 **************************************************************************************************/

#include "assets/GLTF.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "engine/SceneGraph.hpp"

GLTF::Scene::Scene(const std::filesystem::path& path, SceneGraph* scene_graph, unsigned int scene_node_index) {
    load(path, scene_graph, scene_node_index);
}

void GLTF::Scene::load(const std::filesystem::path& path, SceneGraph* scene_graph, unsigned int scene_node_index) {
    /* ---- TinyGLTF Load Model ---- */
    tinygltf::TinyGLTF loader;
    loader.SetPreserveImageChannels(true);

    tinygltf::Model model;
    std::string error;
    std::string warning;

    bool success;

    if(path.extension() == ".glb") {
        success = loader.LoadBinaryFromFile(&model, &error, &warning, path.string());
    } else {
        success = loader.LoadASCIIFromFile(&model, &error, &warning, path.string());
    }

    if(!warning.empty()) { std::cerr << "Warning loading GLTF scene: " << warning << '\n'; }
    if(!error.empty()) { std::cerr << "Error loading GLTF scene: " << error << '\n'; }
    if(!success) { throw std::runtime_error("Failed to load GLTF scene from file '" + path.string() + "'."); }

    /* ---- Meshes ---- */
    size_t meshes_count = model.meshes.size();
    meshes.resize(meshes_count);

    for(unsigned int i = 0 ; i < meshes_count ; ++i) {
        tinygltf::Mesh& t_mesh = model.meshes[i];
        Mesh& mesh = meshes[i];

        mesh.name = t_mesh.name;
        if(mesh.name.empty()) { std::cerr << "Mesh with no name\n"; }

        size_t primitives_count = t_mesh.primitives.size();
        mesh.primitives.resize(primitives_count);

        std::cout << "Mesh '" << mesh.name << "'\n";

        for(unsigned int j = 0 ; j < primitives_count ; ++j) {
            tinygltf::Primitive& t_primitive = t_mesh.primitives[j];
            Primitive& primitive = mesh.primitives[i];

            std::cout << "\tPrimitive " << j << ' ';

            switch(t_primitive.mode) {
                case TINYGLTF_MODE_POINTS:
                    primitive.set_primitive(MeshPrimitive::POINTS);
                    std::cout << "(POINTS)\n";
                    break;
                case TINYGLTF_MODE_LINE:
                    primitive.set_primitive(MeshPrimitive::LINES);
                    std::cout << "(LINES)\n";
                    break;
                case TINYGLTF_MODE_LINE_LOOP:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_LINE_LOOP.");
                case TINYGLTF_MODE_LINE_STRIP:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_LINE_STRIP.");
                case TINYGLTF_MODE_TRIANGLES:
                    primitive.set_primitive(MeshPrimitive::TRIANGLES);
                    std::cout << "(TRIANGLES)\n";
                    break;
                case TINYGLTF_MODE_TRIANGLE_STRIP:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_TRIANGLE_STRIP.");
                case TINYGLTF_MODE_TRIANGLE_FAN:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_TRIANGLE_FAN.");
                default:
                    throw std::runtime_error("Unknown primitive mode: " + std::to_string(t_primitive.mode) + '.');
            }

            static const std::map<std::string, Attribute> GLTF_STRING_TO_ATTR{
                { "POSITION", ATTRIBUTE_POSITION },
                { "NORMAL", ATTRIBUTE_NORMAL },
                { "TEXCOORD_0", ATTRIBUTE_TEX_COORDS },
                { "COLOR_0", ATTRIBUTE_COLOR },
                { "TANGENT", ATTRIBUTE_TANGENT },
            };

            std::vector<AttributeInfo> attribute_infos;

            for(const auto& [attribute_name, accessor_index] : t_primitive.attributes) {
                const tinygltf::Accessor& t_accessor = model.accessors[accessor_index];
                const tinygltf::BufferView& t_buffer_view = model.bufferViews[t_accessor.bufferView];
                const tinygltf::Buffer& t_buffer = model.buffers[t_buffer_view.buffer];

                auto iterator = GLTF_STRING_TO_ATTR.find(attribute_name);
                if(iterator == GLTF_STRING_TO_ATTR.end()) {
                    std::cout << "\t\tUnhandled attribute " << attribute_name << ", " << accessor_index << '\n';
                } else {
                    AttributeType attribute_type;
                    switch(model.accessors[accessor_index].type) {
                        case TINYGLTF_TYPE_VEC2:
                            attribute_type = AttributeType::VEC2;
                            break;
                        case TINYGLTF_TYPE_VEC3:
                            attribute_type = AttributeType::VEC3;
                            break;
                        case TINYGLTF_TYPE_VEC4:
                            attribute_type = AttributeType::VEC4;
                            break;
                        case TINYGLTF_TYPE_MAT2:
                            throw std::runtime_error("Unhandled attribute type: TINYGLTF_TYPE_MAT2.");
                        case TINYGLTF_TYPE_MAT3:
                            throw std::runtime_error("Unhandled attribute type: TINYGLTF_TYPE_MAT3.");
                        case TINYGLTF_TYPE_MAT4:
                            throw std::runtime_error("Unhandled attribute type: TINYGLTF_TYPE_MAT4.");
                        case TINYGLTF_TYPE_SCALAR:
                            attribute_type = AttributeType::FLOAT;
                            break;
                        case TINYGLTF_TYPE_VECTOR:
                            throw std::runtime_error("Unhandled attribute type: TINYGLTF_TYPE_VECTOR.");
                        case TINYGLTF_TYPE_MATRIX:
                            throw std::runtime_error("Unhandled attribute type: TINYGLTF_TYPE_MATRIX.");
                        default:
                            throw std::runtime_error(
                                "Unknown attribute type: " + std::to_string(t_accessor.type) + '.');
                    }

                    size_t byte_offset = t_accessor.byteOffset + t_buffer_view.byteOffset;
                    size_t stride_in_floats = t_buffer_view.byteStride == 0
                                                  ? get_attribute_type_count(attribute_type)
                                                  : t_buffer_view.byteStride / sizeof(float);

                    attribute_infos.emplace_back(attribute_name,
                                                 iterator->second,
                                                 attribute_type,
                                                 t_accessor.count,
                                                 reinterpret_cast<const float*>(t_buffer.data.data() + byte_offset),
                                                 stride_in_floats,
                                                 get_attribute_type_count(attribute_type)
                    );
                }
            }

            std::ranges::sort(attribute_infos, [](const AttributeInfo& a1, const AttributeInfo& a2) {
                return a1.attribute < a2.attribute;
            });

            size_t vertex_count = 0;
            for(const auto& attr_info : attribute_infos) {
                std::cout << "\t\t" << attr_info.name
                    << " (" << static_cast<unsigned int>(attr_info.attribute) << ')'
                    << ", " << attr_info.values_count << " values"
                    << " of type " << attribute_type_to_string(attr_info.attribute_type)
                    << " with stride of " << attr_info.stride_in_floats << " floats"
                    << '\n';

                if(vertex_count == 0) {
                    vertex_count = attr_info.values_count;
                } else if(vertex_count != attr_info.values_count) {
                    throw std::runtime_error("Not the same amount of values between vertex attributes.");
                }

                primitive.enable_attribute(attr_info.attribute, attr_info.attribute_type);
            }

            for(size_t k = 0 ; k < vertex_count ; ++k) {
                for(const AttributeInfo& attribute_info : attribute_infos) {
                    primitive.push_values(attribute_info.data + k * attribute_info.stride_in_floats,
                                          attribute_info.elements_count);
                }
            }

            if(t_primitive.indices != -1) {
                const tinygltf::Accessor& t_accessor = model.accessors[t_primitive.indices];
                const tinygltf::BufferView& t_buffer_view = model.bufferViews[t_accessor.bufferView];
                const tinygltf::Buffer& t_buffer = model.buffers[t_buffer_view.buffer];

                size_t byte_offset = t_accessor.byteOffset + t_buffer_view.byteOffset;
                const unsigned int* data = reinterpret_cast<const unsigned int*>(
                    t_buffer.data.data() + byte_offset);

                for(size_t k = 0 ; k < t_accessor.count ; ++k) {
                    primitive.add_index(data[k]);
                }
            }

            primitive.bind_buffers();

            std::cout << "\tPrimitive has: " << primitive.get_vertices_amount() << " vertices\n";
            std::cout << "\tPrimitive has: " << primitive.get_indices_amount() << " indices\n";
        }
    }

    for(const Mesh& mesh : meshes) {
        int mesh_node_index = scene_graph->add_simple_node(mesh.name, scene_node_index);

        unsigned int i = 0;
        for(const Primitive& primitive : mesh.primitives) {
            scene_graph->add_flat_shaded_mesh_node("Primitive " + std::to_string(i++),
                                                   mesh_node_index,
                                                   &primitive,
                                                   vec4(1.0f)
            );
        }
    }
}
