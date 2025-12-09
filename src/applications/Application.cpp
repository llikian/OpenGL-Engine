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
      are_axes_drawn(false),
      sky_color_low(0.671f, 0.851f, 1.0f),
      sky_color_high(0.239f, 0.29f, 0.761f) {
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

    /* ---- Other ---- */
    // glfwSwapInterval(0); // disable vsync
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run() {
    // scene_graph.add_gltf_scene_node("Duck", 0, "data/models/duck.glb");
    // scene_graph.add_gltf_scene_node("Buggy", 0, "data/models/buggy.glb");
    // unsigned int sponza = scene_graph.add_gltf_scene_node("Sponza", 0, "data/models/sponza/Sponza.gltf");
    // scene_graph.transforms[sponza].set_local_scale(10.0f);

    for(unsigned int i = 0 ; i < MAX_ICO_LEVEL ; ++i) {
        std::string mesh_name = "icosphere " + std::to_string(i);

        icospheres[i] = scene_graph.add_mesh(
            AssetManager::has_mesh(mesh_name)
                ? AssetManager::get_mesh_ptr(mesh_name)
                : &AssetManager::add_mesh(mesh_name, create_icosphere_mesh, i)
        );
    }
    ico_level = 0;

    ico_node = scene_graph.add_mesh_node("icosphere", 0, icospheres[0], SHADER_LAMBERT);
    scene_graph.transforms[ico_node].set_local_scale(5.0f);
    scene_graph.transforms[ico_node].set_local_position(0.0f, 10.0f, -10.0f);
    scene_graph.add_color_to_node(ico_node, vec4(1.0f, 0.0f, 0.0f, 1.0f));

    /* Main Loop */
    while(!Window::should_close()) {
        EventHandler::poll_and_handle_events();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        frustum.update(camera);

        draw();

        draw_imgui_debug_window();
        draw_imgui_object_editor_window();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Window::swap_buffers();
    }
}

void Application::draw() {
    framebuffer.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ---- Background ---- */
    const Shader& background_shader = AssetManager::get_shader(SHADER_BACKGROUND);
    background_shader.use();
    background_shader.set_uniform("u_resolution", Window::get_resolution());
    background_shader.set_uniform("u_camera_direction", camera.get_direction());
    background_shader.set_uniform("u_camera_right", camera.get_right_vector());
    background_shader.set_uniform("u_camera_up", camera.get_up_vector());
    background_shader.set_uniform("u_sky_color_low", sky_color_low);
    background_shader.set_uniform("u_sky_color_high", sky_color_high);

    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    AssetManager::get_mesh("screen").draw();
    if(EventHandler::is_wireframe_enabled()) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    /* ---- Scene ---- */
    scene_graph.draw(frustum);

    /* ---- Post Processing ---- */
    const Shader& post_processing_shader = AssetManager::get_shader(SHADER_POST_PROCESSING);
    post_processing_shader.use();
    post_processing_shader.set_uniform("u_texture", 0);
    post_processing_shader.set_uniform("u_texture_resolution", framebuffer.get_resolution());
    post_processing_shader.set_uniform_if_exists("u_resolution", Window::get_resolution());
    framebuffer.bind_texture(0);

    Framebuffer::bind_default();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    ImGui::ColorEdit3("Low Sky Color", &sky_color_low.x);
    ImGui::ColorEdit3("High Sky Color", &sky_color_high.x);

    ImGui::NewLine();
    ImGui::Text("Camera:");
    ImGui::SliderFloat("Sensitivity", &camera.sensitivity, 0.05f, 1.0f);
    ImGui::SliderFloat("Movement Speed", &camera.movement_speed, 1.0f, 100.0f);

    ImGui::SliderInt("Icosphere Level", &ico_level, 0, MAX_ICO_LEVEL - 1);
    scene_graph.nodes[ico_node].drawable_index = icospheres[ico_level];

    ImGui::NewLine();
    scene_graph.add_imgui_node_tree();

    ImGui::End();
}

void Application::draw_imgui_object_editor_window() {
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
