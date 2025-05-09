/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "applications/Application.hpp"

#include <cmath>
#include <memory>
#include "maths/geometry.hpp"
#include "maths/mat3.hpp"
#include "maths/transforms.hpp"
#include "maths/trigonometry.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/meshes.hpp"
#include "utility/Random.hpp"

Application::Application()
    : ApplicationBase("OpenGL Engine"),
      wireframe(false), cullface(true), cursorVisible(false), areAxesDrawn(false),
      projection(perspective(M_PI_4f, window.getRatio(), 0.1f, 100.0f)),
      camera(vec3(0.0f, 2.0f, 5.0f)) {
    /* ---- Repeatable Keys ---- */
    repeatableKeys.emplace(GLFW_KEY_W, false);
    repeatableKeys.emplace(GLFW_KEY_S, false);
    repeatableKeys.emplace(GLFW_KEY_A, false);
    repeatableKeys.emplace(GLFW_KEY_D, false);
    repeatableKeys.emplace(GLFW_KEY_SPACE, false);
    repeatableKeys.emplace(GLFW_KEY_LEFT_SHIFT, false);

    /* ---- GLFW Callbacks ---- */
    setCallbacks<Application>(window, true, true, true, false, true, false);

    /* ---- ImGui ---- */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run() {
    Scene scene(camera, projection);

    /* Shaders */ {
        std::string paths[2]{ "shaders/default.vert", "shaders/default.frag" };
        scene.add(std::make_shared<Shader>(paths, 2, "default"));

        paths[0] = "shaders/line_mesh.vert";
        paths[1] = "shaders/line_mesh.frag";
        scene.add(std::make_shared<Shader>(paths, 2, "line mesh"));

        paths[0] = "shaders/point_mesh.vert";
        paths[1] = "shaders/point_mesh.frag";
        scene.add(std::make_shared<Shader>(paths, 2, "point mesh"));
    }

    scene.add("grid", std::make_shared<LineMesh>(Meshes::grid(10.0f, 10)));
    scene.add("sphere", std::make_shared<TriangleMesh>(Meshes::sphere(16, 32)));
    scene.add("axes", std::make_shared<LineMesh>(Meshes::axes(1.0f)));

    scene.add("line mesh", "grid", mat4(1.0f));

    float y = 0.0f;
    float r = 1.0f;
    for(uint i = 0 ; i < 10 ; ++i) { scene.add("default", "sphere", translateY(y += r).scale(r *= 0.75f)); }
    uint axesIndex = scene.add("line mesh", "axes", mat4(1.0f));

    /* Point Cloud */ {
        std::shared_ptr<PointMesh> pointCloud = std::make_shared<PointMesh>();
        for(uint i = 0 ; i < 100 ; ++i) {
            pointCloud->addVertex(Random::Vec3(-10.0f, 10.0f), Random::Vec3(0.0f, 1.0f), Random::Float(1.0f, 10.0f));
        }

        scene.add("point cloud", pointCloud);
        scene.add("point mesh", "point cloud", mat4(1.0f));
    }

    Element& axes = scene.getElement(axesIndex);

    /* ---- Main Loop ---- */
    while(!glfwWindowShouldClose(window)) {
        handleEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.1, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ImGui */ {
            ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse
                                           | ImGuiWindowFlags_NoResize
                                           | ImGuiWindowFlags_NoMove);

            ImGui::SetWindowPos("Scene", ImVec2(0.0f, 0.0f));
            ImGui::SetWindowSize("Scene", ImVec2(0.2f * window.getWidth(), window.getHeight()));

            ImGui::End();
        }

        axes.isActive = areAxesDrawn;
        if(areAxesDrawn) { axes.model = translate(camera.getPosition() + 2.0f * camera.getDirection()).scale(0.5f); }

        scene.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void Application::handleWindowSizeCallback(int width, int height) {
    ApplicationBase::handleWindowSizeCallback(width, height);

    projection(0, 0) = 1.0f / (tanf(M_PI_4f / 2.0f) * window.getRatio());
}

void Application::handleCursorPositionCallback(double xPos, double yPos) {
    if(!cursorVisible) { camera.look(vec2(xPos - mousePos.x, yPos - mousePos.y)); }

    ApplicationBase::handleCursorPositionCallback(xPos, yPos);
}

void Application::handleKeyEvent(int key) {
    switch(key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_Z:
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
            wireframe = !wireframe;
            break;
        case GLFW_KEY_C:
            (cullface ? glDisable : glEnable)(GL_CULL_FACE);
            cullface = !cullface;
            break;
        case GLFW_KEY_TAB:
            glfwSetInputMode(window, GLFW_CURSOR, cursorVisible ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            cursorVisible = !cursorVisible;
            break;
        case GLFW_KEY_Q:
            areAxesDrawn = !areAxesDrawn;
            break;
        case GLFW_KEY_W:
            camera.move(CameraControls::forward, delta);
            break;
        case GLFW_KEY_S:
            camera.move(CameraControls::backward, delta);
            break;
        case GLFW_KEY_A:
            camera.move(CameraControls::left, delta);
            break;
        case GLFW_KEY_D:
            camera.move(CameraControls::right, delta);
            break;
        case GLFW_KEY_SPACE:
            camera.move(CameraControls::upward, delta);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            camera.move(CameraControls::downward, delta);
            break;
        default: break;
    }
}
