/***************************************************************************************************
 * @file  Mesh.cpp
 * @brief Implementation of the Mesh class
 **************************************************************************************************/

#include "mesh/Mesh.hpp"

#include "culling/Ray.hpp"
#include "maths/constants.hpp"
#include "maths/mat3.hpp"

Mesh::Mesh(MeshPrimitive primitive)
    : primitive(primitive),
      stride(0),
      active_attributes_count(0),
      VAO(0),
      VBO(0),
      EBO(0) {
    for(AttributeType& attribute : attributes) { attribute = AttributeType::NONE; }
    enable_attribute(ATTRIBUTE_POSITION);
}

Mesh::~Mesh() {
    delete_buffers();
}

void Mesh::draw() const {
    if(primitive == MeshPrimitive::NONE) {
        std::cout << "[WARNING] Mesh wasn't drawn as it didn't have a primitive.\n";
        return;
    }

    if(stride == 0) {
        std::cout << "[WARNING] Mesh wasn't drawn as it didn't have any active attributes.\n";
        return;
    }

    if(VAO == 0 || VBO == 0) {
        std::cout << "[WARNING] Mesh wasn't drawn as its buffers aren't bound.\n";
        return;
    }

    glBindVertexArray(VAO);

    if(indices.empty()) {
        glDrawArrays(get_opengl_enum_for_primitive(primitive), 0, get_vertices_amount());
    } else {
        glDrawElements(get_opengl_enum_for_primitive(primitive), indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void Mesh::draw_normals() const {
    if(primitive == MeshPrimitive::NONE) {
        std::cout << "[WARNING] Normals weren't drawn as the mesh didn't have a primitive.\n";
        return;
    }

    if(stride == 0) {
        std::cout << "[WARNING] Normals weren't drawn as the mesh didn't have any active attributes.\n";
        return;
    }

    if(VAO == 0 || VBO == 0) {
        std::cout << "[WARNING] Normals weren't drawn as the mesh's buffers aren't bound.\n";
        return;
    }

    if(primitive != MeshPrimitive::TRIANGLES) {
        std::cout << "[WARNING] Normals weren't drawn as the mesh wasn't a triangle mesh.\n";
        return;
    }

    if(!has_attribute(ATTRIBUTE_NORMAL)) {
        std::cout << "[WARNING] Normals weren't drawn as the mesh didn't have any normals.\n";
        return;
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, get_vertices_amount());
}

void Mesh::draw_wireframe() const {
    if(primitive == MeshPrimitive::NONE) {
        std::cout << "[WARNING] Wireframe wasn't drawn as the mesh didn't have a primitive.\n";
        return;
    }

    if(stride == 0) {
        std::cout << "[WARNING] Wireframe wasn't drawn as the mesh didn't have any active attributes.\n";
        return;
    }

    if(VAO == 0 || VBO == 0) {
        std::cout << "[WARNING] Wireframe wasn't drawn as the mesh's buffers aren't bound.\n";
        return;
    }

    if(primitive != MeshPrimitive::TRIANGLES) {
        std::cout << "[WARNING] Wireframe wasn't drawn as the mesh wasn't a triangle mesh.\n";
        return;
    }

    glBindVertexArray(VAO);

    glLineWidth(2);
    if(indices.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, get_vertices_amount());
    } else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    glLineWidth(1);
}

void Mesh::set_primitive(MeshPrimitive primitive) {
    this->primitive = primitive;
}

MeshPrimitive Mesh::get_primitive() const {
    return primitive;
}

AttributeType Mesh::get_attribute_type(Attribute attribute) const {
    return attributes[attribute];
}

bool Mesh::has_attribute(Attribute attribute) const {
    return get_attribute_type(attribute) != AttributeType::NONE;
}

size_t Mesh::get_vertices_amount() const {
    return data.size() / stride;
}

size_t Mesh::get_indices_amount() const {
    return indices.size();
}

AttributeType Mesh::get_attribute_type(Attribute attribute) {
    return attributes[attribute];
}

AABB Mesh::get_AABB() const {
    return aabb;
}

void Mesh::get_min_max_axis_aligned_coordinates(Point& minimum, Point& maximum) const {
    if(has_attribute(ATTRIBUTE_POSITION)) {
        const unsigned int offset = get_attribute_offset(ATTRIBUTE_POSITION);
        for(unsigned int i = offset; i < data.size(); i += stride) {
            minimum.x = std::min(minimum.x, data[i]);
            minimum.y = std::min(minimum.y, data[i + 1]);
            minimum.z = std::min(minimum.z, data[i + 2]);

            maximum.x = std::max(maximum.x, data[i]);
            maximum.y = std::max(maximum.y, data[i + 1]);
            maximum.z = std::max(maximum.z, data[i + 2]);
        }
    }
}

float Mesh::intersect(const Ray& ray, const mat4& model_matrix) const {
    // TODO Implement for other primitives.
    if(primitive != MeshPrimitive::TRIANGLES) { return -INFINITY_F; }

    auto intersect_triangle = [&](size_t index0, size_t index1, size_t index2) -> float {
        std::size_t baseA = index0 * stride;
        std::size_t baseB = index1 * stride;
        std::size_t baseC = index2 * stride;

        return ray.intersect_triangle(model_matrix * Point(data[baseA], data[baseA + 1], data[baseA + 2]),
                                      model_matrix * Point(data[baseB], data[baseB + 1], data[baseB + 2]),
                                      model_matrix * Point(data[baseC], data[baseC + 1], data[baseC + 2]));
    };

    float distance = INFINITY_F;
    if(indices.empty()) {
        const std::size_t vertices_count = get_vertices_amount();
        for(std::size_t i = 0; i + 2 < vertices_count; i += 3) {
            float dist = intersect_triangle(i, i + 1, i + 2);
            if(dist > 0.0f) { distance = std::min(distance, dist); }
        }
    } else {
        const std::size_t indices_count = get_indices_amount();
        for(std::size_t i = 0; i + 2 < indices_count; i += 3) {
            float dist = intersect_triangle(indices[i], indices[i + 1], indices[i + 2]);
            if(dist > 0.0f) { distance = std::min(distance, dist); }
        }
    }

    return distance == INFINITY_F ? -INFINITY_F : distance;
}

void Mesh::clear() {
    delete_buffers();
    data.clear();
    indices.clear();
    stride = 0;
    active_attributes_count = 0;
    for(AttributeType& attribute : attributes) { attribute = AttributeType::NONE; }
    enable_attribute(ATTRIBUTE_POSITION);
}

void Mesh::delete_buffers() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    VAO = VBO = EBO = 0;
}

void Mesh::apply_model_matrix(const mat4& model) {
    const unsigned int pos_offset = get_attribute_offset(ATTRIBUTE_POSITION);
    const unsigned int normal_offset = get_attribute_offset(ATTRIBUTE_NORMAL);

    for(unsigned int i = 0; i < data.size(); i += stride) {
        if(has_attribute(ATTRIBUTE_POSITION)) {
            vec4 pos = model * reinterpret_cast<Point&>(data[pos_offset + i]);
            data[pos_offset + i] = pos.x / pos.w;
            data[pos_offset + i + 1] = pos.y / pos.w;
            data[pos_offset + i + 2] = pos.z / pos.w;
        }

        if(has_attribute(ATTRIBUTE_NORMAL)) {
            mat4 normals_model = transpose(inverse_transform(model)); // assumes model is a transform, bc it should be
            Vector normal = normals_model * reinterpret_cast<Vector&>(data[normal_offset + i]);
            data[pos_offset + i] = normal.x;
            data[pos_offset + i + 1] = normal.y;
            data[pos_offset + i + 2] = normal.z;
        }
    }

    bind_buffers();
}

void Mesh::enable_attribute(Attribute attribute, AttributeType type) {
    if(type == AttributeType::NONE) { type = get_default_attribute_type(attribute); }

    unsigned int stride_difference = get_attribute_type_count(type) - get_attribute_type_count(attributes[attribute]);
    stride += stride_difference;
    active_attributes_count += stride_difference > 0 ? 1 : -1;
    attributes[attribute] = type;
}

void Mesh::disable_attribute(Attribute attribute) {
    stride -= get_attribute_type_count(attributes[attribute]);
    active_attributes_count--;
    attributes[attribute] = AttributeType::NONE;
}

void Mesh::add_index(unsigned int index) {
    indices.push_back(index);
}

void Mesh::add_line(unsigned int start, unsigned int end) {
    indices.push_back(start);
    indices.push_back(end);
}

void Mesh::add_line_triangle(unsigned int A, unsigned int B, unsigned int C) {
    add_line(A, B);
    add_line(B, C);
    add_line(C, A);
}

void Mesh::add_line_quad(unsigned int A, unsigned int B, unsigned int C, unsigned int D) {
    add_line(A, B);
    add_line(B, C);
    add_line(C, D);
    add_line(D, A);
}

void Mesh::add_triangle(unsigned int top, unsigned int left, unsigned int right) {
    indices.push_back(top);
    indices.push_back(left);
    indices.push_back(right);
}

void Mesh::add_face(unsigned int topL, unsigned int bottomL, unsigned int bottomR, unsigned int topR) {
    add_triangle(topL, bottomL, bottomR);
    add_triangle(topL, bottomR, topR);
}

void Mesh::bind_buffers() {
    /* AABB */
    Point min(FLOAT_MAX);
    Point max(FLOAT_MIN);
    get_min_max_axis_aligned_coordinates(min, max);
    aabb.set(min, max);

    /* VAO */
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* VBO */
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    /* Vertex Attributes */
    float stride_in_bytes = stride * sizeof(float);
    unsigned int offset = 0;

    for(unsigned int attr = 0; attr < ATTRIBUTE_AMOUNT; ++attr) {
        AttributeType type = attributes[attr];
        if(type != AttributeType::NONE) {
            unsigned int size = get_attribute_type_count(type);
            glVertexAttribPointer(attr, size, GL_FLOAT, false, stride_in_bytes, reinterpret_cast<void*>(offset));
            glEnableVertexAttribArray(attr);
            offset += size * sizeof(float);
        }
    }

    /* Indices & EBO */
    if(!indices.empty()) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
}

void Mesh::push_value(float value) {
    data.push_back(value);
}

void Mesh::push_value(const vec2& value) {
    data.push_back(value.x);
    data.push_back(value.y);
}

void Mesh::push_value(const Point& value) {
    data.push_back(value.x);
    data.push_back(value.y);
    data.push_back(value.z);
}

void Mesh::push_value(const Vector& value) {
    data.push_back(value.x);
    data.push_back(value.y);
    data.push_back(value.z);
}

void Mesh::push_value(const Color& value) {
    data.push_back(value.r);
    data.push_back(value.g);
    data.push_back(value.b);
}

void Mesh::push_value(const float3& value) {
    data.push_back(value.x);
    data.push_back(value.y);
    data.push_back(value.z);
}

void Mesh::push_value(const vec4& value) {
    data.push_back(value.x);
    data.push_back(value.y);
    data.push_back(value.z);
    data.push_back(value.w);
}

void Mesh::push_values(const float* values, unsigned int n) {
    for(unsigned int i = 0; i < n; ++i) { data.push_back(values[i]); }
}

void Mesh::push_indices_buffer(const std::vector<unsigned int>& indices) {
    this->indices.insert(this->indices.end(), indices.begin(), indices.end());
}

unsigned int Mesh::get_attribute_offset(Attribute attribute) const {
    unsigned int offset = 0;

    for(unsigned char attr = 0; attr < attribute; ++attr) { offset += get_attribute_type_count(attributes[attr]); }

    return offset;
}
