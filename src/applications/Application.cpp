/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "applications/Application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "assets/AssetManager.hpp"
#include "engine/EventHandler.hpp"
#include "engine/Window.hpp"
#include "glad/glad.h"
#include "maths/constants.hpp"
#include "maths/functions.hpp"
#include "maths/geometry.hpp"
#include "mesh/primitives.hpp"
#include "utility/LifetimeLogger.hpp"
#include "utility/Random.hpp"

Application::Application()
    : camera(vec3(0.0f, 10.0f, 0.0f), PI_HALF_F, 0.1f, 1024.0f),
      framebuffer(Window::get_width(), Window::get_height()),
      are_axes_drawn(false) {
    /* ---- Event Handler ---- */
    EventHandler::set_active_camera(&camera);
    EventHandler::associate_action_to_key(GLFW_KEY_Q, false, [this] { are_axes_drawn = !are_axes_drawn; });

    /* ---- ImGui ---- */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = "data/imgui.ini";
    ImGui_ImplGlfw_InitForOpenGL(Window::get_glfw(), true);
    ImGui_ImplOpenGL3_Init();

    /* ---- Asset Manager ---- */
    /* Shaders */
    AssetManager::add_shader("point mesh", {
                                 "shaders/point_mesh/point_mesh.vert",
                                 "shaders/point_mesh/point_mesh.frag"
                             });
    AssetManager::add_shader("line mesh", {
                                 "shaders/line_mesh/line_mesh.vert",
                                 "shaders/line_mesh/line_mesh.frag"
                             });
    AssetManager::add_shader("background", {
                                 "shaders/vertex/position_only-no_mvp.vert",
                                 "shaders/fragment/background.frag"
                             });
    AssetManager::add_shader("flat", {
                                 "shaders/vertex/position_only.vert",
                                 "shaders/fragment/flat.frag"
                             });
    AssetManager::add_shader("lambert", {
                                 "shaders/vertex/position_and_normal.vert",
                                 "shaders/fragment/lambert.frag"
                             });
    AssetManager::add_shader("blinn-phong", {
                                 "shaders/vertex/default.vert",
                                 "shaders/fragment/blinn_phong.frag"
                             });
    AssetManager::add_shader("metallic-roughness", {
                                 "shaders/vertex/tangent.vert",
                                 "shaders/metallic-roughness/get_directions_tangent.frag",
                                 "shaders/metallic-roughness/metallic_roughness.frag",
                             });
    AssetManager::add_shader("metallic-roughness no tangent", {
                                 "shaders/vertex/default.vert",
                                 "shaders/metallic-roughness/get_directions_no_tangent.frag",
                                 "shaders/metallic-roughness/metallic_roughness.frag",
                             });
    AssetManager::add_shader("terrain", {
                                 "shaders/terrain/terrain.vert",
                                 "shaders/terrain/terrain.tesc",
                                 "shaders/terrain/terrain.tese",
                                 "shaders/terrain/terrain.frag"
                             });
    AssetManager::add_shader("post processing", {
                                 "shaders/vertex/position_only-no_mvp.vert",
                                 "shaders/fragment/post_processing.frag"
                             });

    /* Meshes */
    AssetManager::add_mesh("sphere 8 16", create_sphere_mesh, 8, 16);
    AssetManager::add_mesh("sphere 16 32", create_sphere_mesh, 16, 32);
    AssetManager::add_mesh("icosphere 0", create_icosphere_mesh, 0);
    AssetManager::add_mesh("icosphere 1", create_icosphere_mesh, 1);
    AssetManager::add_mesh("icosphere 2", create_icosphere_mesh, 2);
    AssetManager::add_mesh("cube", create_cube_mesh);
    AssetManager::add_mesh("wireframe cube", create_wireframe_cube_mesh);
    AssetManager::add_mesh("screen", create_screen_mesh);
    AssetManager::add_mesh("axes", create_axes_mesh, 0.5f);
    AssetManager::add_mesh("camera pyramid", create_pyramid_mesh,
                           vec3(1.0f, 1.0f, -1.0f), vec3(1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), 1.0f);

    /* Textures */
    AssetManager::add_texture("default", vec3(1.0f));
    AssetManager::add_texture("red", vec3(1.0f, 0.0f, 0.0f));
    AssetManager::add_texture("green", vec3(0.0f, 1.0f, 0.0f));
    AssetManager::add_texture("blue", vec3(0.0f, 0.0f, 1.0f));

    /* ---- Scene Graph */
    scene_graph.shaders.push_back(AssetManager::get_shader_ptr("flat"));
    scene_graph.flat_shader_index = scene_graph.shaders.size() - 1;

    /* ---- Other ---- */
    // glfwSwapInterval(0); // disable vsync
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run() {
    /* Light */
    unsigned int light = scene_graph.add_flat_shaded_mesh_node("Light",
                                                               0,
                                                               AssetManager::get_mesh_ptr("icosphere 1"),
                                                               vec4(1.0f));
    scene_graph.transforms[light].set_local_position(0.0f, 100.0f, 0.0f);

    /* Frustum Tests */ {
        unsigned int frustum_tests_root = scene_graph.add_simple_node("Frustum Tests Root", 0);
        unsigned int mesh_index = scene_graph.add_mesh(AssetManager::get_mesh_ptr("cube"));

        std::string name = "Frustum Test Mesh ";

        for(unsigned int i = 0 ; i < 10'000 ; ++i) {
            unsigned int index = scene_graph.add_flat_shaded_mesh_node(name + std::to_string(i),
                                                                       frustum_tests_root,
                                                                       mesh_index,
                                                                       vec4(1.0f));

            scene_graph.transforms[index].set_local_position(Random::get_vec3(-500.0f, 500.0f));
            scene_graph.transforms[index].set_local_scale(Random::get_vec3(1.0f, 5.0f));
            scene_graph.colors[scene_graph.nodes[index].color_index] = vec4(Random::get_vec3(-0.5f, 0.5f), 1.0f);
        }
    }

    /* Main Loop */
    while(!Window::should_close()) {
        EventHandler::poll_and_handle_events();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        frustum.update(camera);

        framebuffer.bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_background();
        scene_graph.draw(frustum);
        draw_post_processing();

        draw_imgui_debug_window();
        draw_imgui_object_ediot_window();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Window::swap_buffers();
    }
}

void Application::draw_post_processing() const {
    const Shader& shader = AssetManager::get_shader("post processing");
    shader.use();
    shader.set_uniform("u_texture", 0);
    shader.set_uniform("u_texture_resolution", framebuffer.get_resolution());
    shader.set_uniform_if_exists("u_resolution", Window::get_resolution());
    framebuffer.bind_texture(0);

    Framebuffer::bind_default();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    AssetManager::get_mesh("screen").draw();
    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
}

void Application::draw_background() const {
    const Shader& shader = AssetManager::get_shader("background");
    shader.use();

    shader.set_uniform("u_resolution", Window::get_resolution());
    shader.set_uniform("u_camera_direction", camera.get_direction());
    shader.set_uniform("u_camera_right", camera.get_right_vector());
    shader.set_uniform("u_camera_up", camera.get_up_vector());

    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    AssetManager::get_mesh("screen").draw();
    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
}

void Application::draw_imgui_debug_window() {
    static ImVec2 win_pos(0.0f, 0.0f);
    static ImVec2 win_size(0.0f, 0.0f);

    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    win_size.x = 0.2f * Window::get_width();
    ImGui::SetWindowPos(win_pos);
    ImGui::SetWindowSize(win_size);

    ImGui::Text("fps: %f f/s", 1.0f / EventHandler::get_delta());
    ImGui::Text("delta: %fs", EventHandler::get_delta());

    ImGui::NewLine();
    ImGui::Checkbox("Draw AABBs", &scene_graph.are_AABBs_drawn);
    ImGui::Text("Total Nodes Count: %lu", scene_graph.nodes.size());
    ImGui::Text("Total Drawn Objects: %d", scene_graph.total_drawn_objects);

    ImGui::NewLine();
    ImGui::Text("Camera:");
    ImGui::SliderFloat("Sensitivity", &camera.sensitivity, 0.05f, 1.0f);
    ImGui::SliderFloat("Movement Speed", &camera.movement_speed, 1.0f, 100.0f);

    ImGui::NewLine();
    scene_graph.add_imgui_node_tree();

    ImGui::End();
}

void Application::draw_imgui_object_ediot_window() {
    static ImVec2 win_pos(0.0f, 0.0f);
    static ImVec2 win_size(0.0f, 0.0f);

    ImGui::Begin("Object Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    win_pos.x = 0.7f * Window::get_width();
    ImGui::SetWindowPos(win_pos);
    win_size.x = Window::get_width() - win_pos.x;
    ImGui::SetWindowSize(win_size);

    scene_graph.add_object_editor_to_imgui_window();

    ImGui::End();
}
