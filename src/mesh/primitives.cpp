/***************************************************************************************************
 * @file  primitives.cpp
 * @brief Implementation of functions aimed at creating basic meshes such as cubes or spheres
 **************************************************************************************************/

#include "mesh/primitives.hpp"

#include <cmath>
#include <functional>
#include "maths/constants.hpp"

void create_sphere_mesh(Mesh& mesh, unsigned int horizontal_slices, unsigned int vertical_slices) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);
    mesh.enable_attribute(ATTRIBUTE_NORMAL);
    mesh.enable_attribute(ATTRIBUTE_TEX_COORDS);

    const float theta_step = PI_F / horizontal_slices; // theta in [-PI/2 ; PI/2]
    const float phi_step = TAU_F / vertical_slices;    // phi in [0 ; 2PI]

    for(unsigned int i = 0; i <= horizontal_slices; ++i) {
        float theta = PI_HALF_F - i * theta_step;
        float cos_theta = std::cos(theta);
        Point point(0.0f, std::sin(theta), 0.0f);

        for(unsigned int j = 0; j <= vertical_slices; ++j) {
            float phi = j * phi_step;
            point.x = cos_theta * std::cos(phi);
            point.z = cos_theta * std::sin(phi);

            // TODO : Check if the texture coordinates are correct.
            mesh.add_vertex(point, point, vec2(1.0f - phi / TAU_F, 0.5f + 0.5f * point.y));
        }
    }

    auto index = [&vertical_slices](int i, int j) -> unsigned int { return j + i * (vertical_slices + 1); };

    for(unsigned int j = 0; j < vertical_slices; ++j) {
        mesh.add_triangle(index(0, j), index(1, j + 1), index(1, j));
        mesh.add_triangle(index(horizontal_slices - 1, j),
                          index(horizontal_slices - 1, j + 1),
                          index(horizontal_slices, j));
    }

    for(unsigned int i = 1; i < horizontal_slices; ++i) {
        for(unsigned int j = 0; j < vertical_slices; ++j) {
            mesh.add_face(index(i + 1, j + 1), index(i + 1, j), index(i, j), index(i, j + 1));
        }
    }

    mesh.bind_buffers();
}

void create_cube_mesh(Mesh& mesh) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);
    mesh.enable_attribute(ATTRIBUTE_NORMAL);
    mesh.enable_attribute(ATTRIBUTE_TEX_COORDS);

    static const Point positions[8] {
        Point(1.0f, 1.0f, 1.0f),   // 0: TOP - RIGHT - FRONT
        Point(1.0f, 1.0f, -1.0f),  // 1: TOP - RIGHT - BACK
        Point(1.0f, -1.0f, 1.0f),  // 2: BOTTOM - RIGHT - FRONT
        Point(1.0f, -1.0f, -1.0f), // 3: BOTTOM - RIGHT - BACK
        Point(-1.0f, 1.0f, 1.0f),  // 4: TOP - LEFT - FRONT
        Point(-1.0f, 1.0f, -1.0f), // 5: TOP - LEFT - BACK
        Point(-1.0f, -1.0f, 1.0f), // 6: BOTTOM - LEFT - FRONT
        Point(-1.0f, -1.0f, -1.0f) // 7: BOTTOM - LEFT - BACK
    };

    static const Vector normals[6] {
        Vector(1.0f, 0.0f, 0.0f),  // 0: RIGHT
        Vector(-1.0f, 0.0f, 0.0f), // 1: LEFT
        Vector(0.0f, 1.0f, 0.0f),  // 2: TOP
        Vector(0.0f, -1.0f, 0.0f), // 3: BOTTOM
        Vector(0.0f, 0.0f, 1.0f),  // 4: FRONT
        Vector(0.0f, 0.0f, -1.0f)  // 5: BACK
    };

    static const unsigned int faces[6][5] {
        { 0, 2, 3, 1 }, // 0: RIGHT
        { 5, 7, 6, 4 }, // 1: LEFT
        { 5, 4, 0, 1 }, // 2: TOP
        { 6, 7, 3, 2 }, // 3: BOTTOM
        { 4, 6, 2, 0 }, // 4: FRONT
        { 1, 3, 7, 5 }  // 5: BACK
    };

    static const vec2 tex_coords[4] { vec2(0.0f, 1.0f), vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f) };

    for(unsigned int i = 0; i < 6; ++i) {
        mesh.add_vertex(positions[faces[i][0]], normals[i], tex_coords[0]);
        mesh.add_vertex(positions[faces[i][1]], normals[i], tex_coords[1]);
        mesh.add_vertex(positions[faces[i][2]], normals[i], tex_coords[2]);
        mesh.add_vertex(positions[faces[i][3]], normals[i], tex_coords[3]);
        mesh.add_face(i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
    }

    mesh.bind_buffers();
}

void create_wireframe_cube_mesh(Mesh& mesh) {
    mesh.set_primitive(MeshPrimitive::LINES);

    mesh.add_vertex(Point(1.0f, 1.0f, 1.0f));    // 0: TOP - RIGHT - FRONT
    mesh.add_vertex(Point(1.0f, 1.0f, -1.0f));   // 1: TOP - RIGHT - BACK
    mesh.add_vertex(Point(1.0f, -1.0f, 1.0f));   // 2: BOTTOM - RIGHT - FRONT
    mesh.add_vertex(Point(1.0f, -1.0f, -1.0f));  // 3: BOTTOM - RIGHT - BACK
    mesh.add_vertex(Point(-1.0f, 1.0f, 1.0f));   // 4: TOP - LEFT - FRONT
    mesh.add_vertex(Point(-1.0f, 1.0f, -1.0f));  // 5: TOP - LEFT - BACK
    mesh.add_vertex(Point(-1.0f, -1.0f, 1.0f));  // 6: BOTTOM - LEFT - FRONT
    mesh.add_vertex(Point(-1.0f, -1.0f, -1.0f)); // 7: BOTTOM - LEFT - BACK

    // RIGHT  : (0, 2, 3, 1)
    // LEFT   : (5, 7, 6, 4)
    // TOP    : (5, 4, 0, 1)
    // BOTTOM : (6, 7, 3, 2)
    // FRONT  : (4, 6, 2, 0)
    // BACK   : (1, 3, 7, 5)

    // RIGHT
    mesh.add_line(0, 2);
    mesh.add_line(2, 3);
    mesh.add_line(3, 1);
    mesh.add_line(1, 0);

    // LEFT
    mesh.add_line(5, 7);
    mesh.add_line(7, 6);
    mesh.add_line(6, 4);
    mesh.add_line(4, 5);

    // FRONT
    mesh.add_line(6, 2);
    mesh.add_line(0, 4);

    // BACK
    mesh.add_line(3, 7);
    mesh.add_line(5, 1);

    mesh.bind_buffers();
}

void create_quad_mesh(Mesh& mesh, const Point& A, const Point& B, const Point& C) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);
    mesh.enable_attribute(ATTRIBUTE_NORMAL);
    mesh.enable_attribute(ATTRIBUTE_TEX_COORDS);

    const Vector BA(A - B);
    const Vector BC(C - B);
    const Vector normal(normalize(cross(BA, BC)));

    mesh.add_vertex(A, normal, vec2(0.0f, 1.0f));
    mesh.add_vertex(B, normal, vec2(0.0f, 0.0f));
    mesh.add_vertex(C, normal, vec2(1.0f, 0.0f));
    mesh.add_vertex(B + BA + BC, normal, vec2(1.0f, 1.0f));

    mesh.add_face(0, 1, 2, 3);

    mesh.bind_buffers();
}

void create_triangle_mesh(Mesh& mesh, const Point& A, const Point& B, const Point& C) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);
    mesh.enable_attribute(ATTRIBUTE_NORMAL);
    mesh.enable_attribute(ATTRIBUTE_TEX_COORDS);

    const Vector normal(normalize(cross(A - B, C - B)));

    mesh.add_vertex(A, normal, vec2(0.0f, 1.0f));
    mesh.add_vertex(B, normal, vec2(0.0f, 0.0f));
    mesh.add_vertex(C, normal, vec2(1.0f, 0.0f));

    mesh.bind_buffers();
}

void create_screen_mesh(Mesh& mesh) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);

    mesh.add_vertex(Point(-1.0f, 3.0f, 1.0f));
    mesh.add_vertex(Point(-1.0f, -1.0f, 1.0f));
    mesh.add_vertex(Point(3.0f, -1.0f, 1.0f));

    mesh.bind_buffers();
}

void create_axes_mesh(Mesh& mesh, float length) {
    mesh.set_primitive(MeshPrimitive::LINES);
    mesh.enable_attribute(ATTRIBUTE_COLOR);

    const Point origin(0.0f, 0.0f, 0.0f);
    const Vector axes[3] { Vector(1.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), Vector(0.0f, 0.0f, 1.0f) };

    for(const Vector& axis : axes) {
        mesh.add_vertex(origin, axis);
        mesh.add_vertex(length * axis, axis);
    }

    mesh.bind_buffers();
}

void create_pyramid_mesh(Mesh& mesh, const Point& A, const Point& B, const Point& C, float height) {
    mesh.set_primitive(MeshPrimitive::LINES);

    const Vector BA = A - B;
    const Vector BC = C - B;

    mesh.add_vertex(A + 0.5f * (C - A) + height * normalize(cross(BA, BC)));
    mesh.add_vertex(A);
    mesh.add_vertex(B);
    mesh.add_vertex(C);
    mesh.add_vertex(B + BA + BC);

    mesh.add_line(0, 1);
    mesh.add_line(0, 2);
    mesh.add_line(0, 3);
    mesh.add_line(0, 4);

    mesh.add_line(1, 2);
    mesh.add_line(2, 3);
    mesh.add_line(3, 4);
    mesh.add_line(4, 1);

    mesh.bind_buffers();
}

void create_frustum_meshes(Mesh& faces, Mesh& lines, const Camera& camera) {
    static const Point projection_space_points[8] { Point(1.0f, 1.0f, 1.0f),   Point(1.0f, 1.0f, -1.0f),
                                                    Point(1.0f, -1.0f, 1.0f),  Point(1.0f, -1.0f, -1.0f),
                                                    Point(-1.0f, 1.0f, 1.0f),  Point(-1.0f, 1.0f, -1.0f),
                                                    Point(-1.0f, -1.0f, 1.0f), Point(-1.0f, -1.0f, -1.0f) };

    vec4 points[8];
    mat4 inverse_projection = camera.get_inverse_projection_matrix();
    for(int i = 0; i < 8; ++i) {
        points[i] = inverse_projection * projection_space_points[i];
        points[i] /= points[i].w;
    }

    /* Line Mesh */
    lines.set_primitive(MeshPrimitive::LINES);

    lines.add_vertex(reinterpret_cast<Point&>(points[0]));
    lines.add_vertex(reinterpret_cast<Point&>(points[1]));
    lines.add_vertex(reinterpret_cast<Point&>(points[2]));
    lines.add_vertex(reinterpret_cast<Point&>(points[3]));
    lines.add_vertex(reinterpret_cast<Point&>(points[4]));
    lines.add_vertex(reinterpret_cast<Point&>(points[5]));
    lines.add_vertex(reinterpret_cast<Point&>(points[6]));
    lines.add_vertex(reinterpret_cast<Point&>(points[7]));

    // Far to Near Lines
    lines.add_line(0, 4);
    lines.add_line(1, 5);
    lines.add_line(2, 6);
    lines.add_line(3, 7);

    // Far Lines
    lines.add_line(0, 1);
    lines.add_line(1, 2);
    lines.add_line(2, 3);
    lines.add_line(3, 0);

    // Near Lines
    lines.add_line(4, 5);
    lines.add_line(5, 6);
    lines.add_line(6, 7);
    lines.add_line(7, 4);

    /* Face Mesh */
    faces.set_primitive(MeshPrimitive::TRIANGLES);

    faces.add_vertex(reinterpret_cast<Point&>(points[0]));
    faces.add_vertex(reinterpret_cast<Point&>(points[1]));
    faces.add_vertex(reinterpret_cast<Point&>(points[2]));
    faces.add_vertex(reinterpret_cast<Point&>(points[3]));
    faces.add_vertex(reinterpret_cast<Point&>(points[4]));
    faces.add_vertex(reinterpret_cast<Point&>(points[5]));
    faces.add_vertex(reinterpret_cast<Point&>(points[6]));
    faces.add_vertex(reinterpret_cast<Point&>(points[7]));

    faces.add_face(0, 1, 2, 3); // FAR
    faces.add_face(4, 5, 6, 7); // NEAR
    faces.add_face(0, 4, 7, 3); // TOP
    faces.add_face(5, 1, 2, 6); // BOTTOM
    faces.add_face(0, 1, 5, 4); // LEFT
    faces.add_face(7, 6, 2, 3); // RIGHT

    lines.bind_buffers();
    faces.bind_buffers();
}

void create_icosphere_mesh(Mesh& mesh, unsigned int subdivisions) {
    mesh.set_primitive(MeshPrimitive::TRIANGLES);
    mesh.enable_attribute(ATTRIBUTE_NORMAL);
    mesh.enable_attribute(ATTRIBUTE_TEX_COORDS);

    static constexpr unsigned int faces[12][5] {
        { 13, 5,  18, 4,  12 },
        { 12, 4,  10, 8,  0  },
        { 13, 12, 0,  16, 1  },
        { 13, 1,  9,  11, 5  },
        { 1,  16, 17, 3,  9  },
        { 0,  8,  2,  17, 16 },
        { 5,  11, 7,  19, 18 },
        { 4,  18, 19, 6,  10 },
        { 9,  3,  15, 7,  11 },
        { 10, 6,  14, 2,  8  },
        { 17, 2,  14, 15, 3  },
        { 19, 7,  15, 14, 6  }
    };

    std::vector<Point> vertices {
        normalize(Point(1.0f, 1.0f, 1.0f).as_vector()).as_point(),    // 0
        normalize(Point(1.0f, 1.0f, -1.0f).as_vector()).as_point(),   // 1
        normalize(Point(1.0f, -1.0f, 1.0f).as_vector()).as_point(),   // 2
        normalize(Point(1.0f, -1.0f, -1.0f).as_vector()).as_point(),  // 3
        normalize(Point(-1.0f, 1.0f, 1.0f).as_vector()).as_point(),   // 4
        normalize(Point(-1.0f, 1.0f, -1.0f).as_vector()).as_point(),  // 5
        normalize(Point(-1.0f, -1.0f, 1.0f).as_vector()).as_point(),  // 6
        normalize(Point(-1.0f, -1.0f, -1.0f).as_vector()).as_point(), // 7

        normalize(Point(INV_GOLDEN_RATIO_F, 0.0f, GOLDEN_RATIO_F).as_vector()).as_point(),   // 8
        normalize(Point(INV_GOLDEN_RATIO_F, 0.0f, -GOLDEN_RATIO_F).as_vector()).as_point(),  // 9
        normalize(Point(-INV_GOLDEN_RATIO_F, 0.0f, GOLDEN_RATIO_F).as_vector()).as_point(),  // 10
        normalize(Point(-INV_GOLDEN_RATIO_F, 0.0f, -GOLDEN_RATIO_F).as_vector()).as_point(), // 11

        normalize(Point(0.0f, GOLDEN_RATIO_F, INV_GOLDEN_RATIO_F).as_vector()).as_point(),   // 12
        normalize(Point(0.0f, GOLDEN_RATIO_F, -INV_GOLDEN_RATIO_F).as_vector()).as_point(),  // 13
        normalize(Point(0.0f, -GOLDEN_RATIO_F, INV_GOLDEN_RATIO_F).as_vector()).as_point(),  // 14
        normalize(Point(0.0f, -GOLDEN_RATIO_F, -INV_GOLDEN_RATIO_F).as_vector()).as_point(), // 15

        normalize(Point(GOLDEN_RATIO_F, INV_GOLDEN_RATIO_F, 0.0f).as_vector()).as_point(),  // 16
        normalize(Point(GOLDEN_RATIO_F, -INV_GOLDEN_RATIO_F, 0.0f).as_vector()).as_point(), // 17
        normalize(Point(-GOLDEN_RATIO_F, INV_GOLDEN_RATIO_F, 0.0f).as_vector()).as_point(), // 18
        normalize(Point(-GOLDEN_RATIO_F, -INV_GOLDEN_RATIO_F, 0.0f).as_vector()).as_point() // 19
    };

    std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)> add_triangle =
        [&](unsigned int A, unsigned int B, unsigned int C, unsigned int depth) {
            if(depth > 0) {
                vertices.push_back(vertices[A] + 0.5f * (vertices[B] - vertices[A]));
                unsigned int AB = vertices.size() - 1;
                vertices.push_back(vertices[B] + 0.5f * (vertices[C] - vertices[B]));
                unsigned int BC = vertices.size() - 1;
                vertices.push_back(vertices[C] + 0.5f * (vertices[A] - vertices[C]));
                unsigned int CA = vertices.size() - 1;

                add_triangle(A, AB, CA, depth - 1);
                add_triangle(AB, B, BC, depth - 1);
                add_triangle(CA, BC, C, depth - 1);
                add_triangle(AB, BC, CA, depth - 1);
            } else {
                mesh.add_triangle(A, B, C);
            }
        };

    for(unsigned int i = 0; i < 12; ++i) {
        const unsigned int* face = faces[i];
        Vector sum = vertices[face[0]].as_vector()   //
                     + vertices[face[1]].as_vector() //
                     + vertices[face[2]].as_vector() //
                     + vertices[face[3]].as_vector() //
                     + vertices[face[4]].as_vector();
        vertices.push_back((0.2f * sum).as_point());

        unsigned int index = vertices.size() - 1;

        add_triangle(face[0], face[1], index, subdivisions);
        add_triangle(face[1], face[2], index, subdivisions);
        add_triangle(face[2], face[3], index, subdivisions);
        add_triangle(face[3], face[4], index, subdivisions);
        add_triangle(face[4], face[0], index, subdivisions);
    }

    for(const Point& vertex : vertices) {
        Point project_on_sphere = normalize(vertex.as_vector()).as_point();
        vec2 tex_coords(std::atan2(project_on_sphere.x, project_on_sphere.z) / (2.0f * PI_F) + 0.5f,
                        0.5f + 0.5f * project_on_sphere.y);
        mesh.add_vertex(project_on_sphere, project_on_sphere, tex_coords);
    }

    mesh.bind_buffers();
}
