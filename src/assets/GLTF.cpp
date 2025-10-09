/***************************************************************************************************
 * @file  GLTF.cpp
 * @brief Implementation of the GLTF namespace
 **************************************************************************************************/

#include "assets/GLTF.hpp"

#include <algorithm>

#include "stb_image_write.h"
#include "assets/AssetManager.hpp"
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

        mesh.name = t_mesh.name.empty() ? "Mesh " + std::to_string(i) : t_mesh.name;

        size_t primitives_count = t_mesh.primitives.size();
        mesh.primitives.resize(primitives_count);

        std::cout << "Mesh '" << mesh.name << "'\n";

        for(unsigned int j = 0 ; j < primitives_count ; ++j) {
            const tinygltf::Primitive& t_primitive = t_mesh.primitives[j];
            Primitive& primitive = mesh.primitives[j];

            if(t_primitive.material != -1) {
                const tinygltf::Material& t_material = model.materials[t_primitive.material];

                primitive.material = new MRMaterial(t_material.name);
                MRMaterial* material = primitive.material;

                material->base_color = vec4(
                    t_material.pbrMetallicRoughness.baseColorFactor[0],
                    t_material.pbrMetallicRoughness.baseColorFactor[1],
                    t_material.pbrMetallicRoughness.baseColorFactor[2],
                    t_material.pbrMetallicRoughness.baseColorFactor[3]
                );

                material->metallic = t_material.pbrMetallicRoughness.metallicFactor;
                material->roughness = t_material.pbrMetallicRoughness.roughnessFactor;

                int base_color_texture_index = t_material.pbrMetallicRoughness.baseColorTexture.index;
                if(base_color_texture_index == -1) {
                    material->base_color_map.create(255, 255, 255);
                } else {
                    const tinygltf::Image& t_image = model.images[model.textures[base_color_texture_index].source];
                    material->base_color_map.create(t_image.width, t_image.height, t_image.image.data(), GL_SRGB);
                }

                int MR_texture_index = t_material.pbrMetallicRoughness.metallicRoughnessTexture.index;
                if(MR_texture_index == -1) {
                    material->metallic_roughness_map.create(vec3(0.0f, 0.5f, 0.0f));
                } else {
                    const tinygltf::Image& t_image = model.images[model.textures[MR_texture_index].source];
                    material->metallic_roughness_map.create(t_image.width, t_image.height, t_image.image.data(), GL_RGB);
                }

                int normal_map_index = t_material.normalTexture.index;
                if(normal_map_index == -1) {
                    material->normal_map.create(vec3(1.0f, 0.5f, 0.5f));
                } else {
                    const tinygltf::Image& t_image = model.images[model.textures[normal_map_index].source];
                    material->normal_map.create(t_image.width, t_image.height, t_image.image.data(), GL_RGB);
                }
            }

            std::cout << "\tPrimitive " << j << ' ';

            switch(t_primitive.mode) {
                case TINYGLTF_MODE_POINTS:
                    primitive.primitive.set_primitive(MeshPrimitive::POINTS);
                    std::cout << "(POINTS)\n";
                    break;
                case TINYGLTF_MODE_LINE:
                    primitive.primitive.set_primitive(MeshPrimitive::LINES);
                    std::cout << "(LINES)\n";
                    break;
                case TINYGLTF_MODE_LINE_LOOP:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_LINE_LOOP.");
                case TINYGLTF_MODE_LINE_STRIP:
                    throw std::runtime_error("Unhandled primitive mode: TINYGLTF_MODE_LINE_STRIP.");
                case TINYGLTF_MODE_TRIANGLES:
                    primitive.primitive.set_primitive(MeshPrimitive::TRIANGLES);
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
                    switch(t_accessor.type) {
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

                primitive.primitive.enable_attribute(attr_info.attribute, attr_info.attribute_type);
            }

            for(size_t k = 0 ; k < vertex_count ; ++k) {
                for(const AttributeInfo& attribute_info : attribute_infos) {
                    primitive.primitive.push_values(attribute_info.data + k * attribute_info.stride_in_floats,
                                                    attribute_info.elements_count);
                }
            }

            if(t_primitive.indices != -1) {
                const tinygltf::Accessor& t_accessor = model.accessors[t_primitive.indices];
                const tinygltf::BufferView& t_buffer_view = model.bufferViews[t_accessor.bufferView];
                const tinygltf::Buffer& t_buffer = model.buffers[t_buffer_view.buffer];

                size_t byte_offset = t_accessor.byteOffset + t_buffer_view.byteOffset;

                switch(t_accessor.componentType) {
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: {
                        const unsigned char* data = t_buffer.data.data() + byte_offset;
                        for(size_t k = 0 ; k < t_accessor.count ; ++k) { primitive.primitive.add_index(data[k]); }
                        break;
                    }
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: {
                        auto data = reinterpret_cast<const unsigned short*>(t_buffer.data.data() + byte_offset);
                        for(size_t k = 0 ; k < t_accessor.count ; ++k) { primitive.primitive.add_index(data[k]); }
                        break;
                    }
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: {
                        auto data = reinterpret_cast<const unsigned int*>(t_buffer.data.data() + byte_offset);
                        for(size_t k = 0 ; k < t_accessor.count ; ++k) { primitive.primitive.add_index(data[k]); }
                        break;
                    }
                    default: throw std::runtime_error("Wrong or unknown component type in indices accessor.");
                }
            }

            primitive.primitive.bind_buffers();

            std::cout << "\t\tPrimitive has: " << primitive.primitive.get_vertices_amount() << " vertices"
                << " and " << primitive.primitive.get_indices_amount() << " indices.\n";
        }
    }

    /* ---- Scenes ---- */
    if(model.scenes.size() == 0) {
        throw std::runtime_error("Unhandled case, no scene in GLTF file.");
    } else if(model.scenes.size() == 1) {
        const tinygltf::Scene& t_scene = model.scenes[0];
        if(!t_scene.name.empty()) { scene_graph->nodes[scene_node_index].name = t_scene.name; }

        for(int node_index : t_scene.nodes) {
            add_node(model.nodes, model.nodes[node_index], scene_graph, scene_node_index);
        }
    } else {
        unsigned int i = 0;

        for(const tinygltf::Scene& t_scene : model.scenes) {
            unsigned int sg_node_index = scene_graph->add_simple_node(t_scene.name.empty()
                                                                          ? "Scene " + std::to_string(i)
                                                                          : t_scene.name,
                                                                      scene_node_index);

            for(int node_index : t_scene.nodes) {
                add_node(model.nodes, model.nodes[node_index], scene_graph, sg_node_index);
            }

            ++i;
        }
    }
}

void GLTF::Scene::add_node(const std::vector<tinygltf::Node>& t_nodes,
                           const tinygltf::Node& t_node,
                           SceneGraph* scene_graph,
                           int sg_parent_index) {
    if(t_node.mesh == -1) {
        sg_parent_index = scene_graph->add_simple_node(t_node.name, sg_parent_index);
    } else {
        const auto& [mesh_name, primitives] = meshes[t_node.mesh];
        sg_parent_index = scene_graph->add_simple_node(mesh_name, sg_parent_index);

        for(unsigned int j = 0 ; j < primitives.get_size() ; ++j) {
            const Primitive& primitive = primitives[j];
            std::string primitive_name = "Primitive " + std::to_string(j);

            if(primitive.material != nullptr) {
                ShaderName shader_name = primitive.primitive.has_attribute(ATTRIBUTE_TANGENT)
                                             ? SHADER_METALLIC_ROUGHNESS
                                             : SHADER_METALLIC_ROUGHNESS_NO_TANGENT;

                unsigned int node_index = scene_graph->add_mesh_node(primitive_name,
                                                                     sg_parent_index,
                                                                     &primitive.primitive,
                                                                     shader_name);

                scene_graph->add_material_to_node(node_index, primitive.material);
            } else {
                ShaderName shader_name = AssetManager::get_relevant_shader_name_from_mesh(primitive.primitive);

                unsigned int node_index = scene_graph->add_mesh_node(primitive_name,
                                                                     sg_parent_index,
                                                                     &primitive.primitive,
                                                                     shader_name);

                switch(shader_name) {
                    case SHADER_FLAT:
                    case SHADER_LAMBERT:
                        scene_graph->add_color_to_node(node_index, vec4(1.0f));
                        break;
                    default: break;
                }
            }
        }
    }

    bool transformed = false;

    if(t_node.translation.size() == 3) {
        scene_graph->transforms[sg_parent_index].set_local_position(t_node.translation[0],
                                                                    t_node.translation[1],
                                                                    t_node.translation[2]);
        transformed = true;
    }

    if(t_node.rotation.size() == 4) {
        scene_graph->transforms[sg_parent_index].set_local_orientation(t_node.rotation[0],
                                                                       t_node.rotation[1],
                                                                       t_node.rotation[2],
                                                                       t_node.rotation[3]);
        transformed = true;
    }

    if(t_node.scale.size() == 3) {
        scene_graph->transforms[sg_parent_index].set_local_scale(t_node.scale[0],
                                                                 t_node.scale[1],
                                                                 t_node.scale[2]);
        transformed = true;
    }

    if(!transformed && t_node.matrix.size() == 16) {
        scene_graph->transforms[sg_parent_index].set_local_model(t_node.matrix.data());
    }

    for(int node_index : t_node.children) {
        add_node(t_nodes,
                 t_nodes[node_index],
                 scene_graph,
                 sg_parent_index);
    }
}
