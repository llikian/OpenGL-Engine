# Global Project Configuration
cmake_minimum_required(VERSION 3.26)
project(OpenGL-Engine)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Compiler options
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ffast-math")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

# Set sources and includes
set(SOURCES
        # Assets Module
        src/assets/AssetManager.cpp
        src/assets/Camera.cpp
        src/assets/Cubemap.cpp
        src/assets/Image.cpp
        src/assets/Shader.cpp
        src/assets/Texture.cpp

        # Culling Module
        src/culling/AABB.cpp
        src/culling/Frustum.cpp

        # Engine Module
        src/engine/callbacks.cpp
        src/engine/EventHandler.cpp
        src/engine/Framebuffer.cpp
        src/engine/Node.cpp
        src/engine/SceneGraph.cpp
        src/engine/Window.cpp

        # Maths Module
        src/maths/functions.cpp
        src/maths/geometry.cpp
        src/maths/mat3.cpp
        src/maths/mat4.cpp
        src/maths/quaternion.cpp
        src/maths/Transform.cpp
        src/maths/transforms.cpp
        src/maths/trigonometry.cpp

        # Mesh Module
        src/mesh/Attribute.cpp
        src/mesh/Mesh.cpp
        src/mesh/primitives.cpp

        # Utility Module
        src/utility/hash.cpp
        src/utility/LifetimeLogger.cpp
        src/utility/Random.cpp

        # Libraries
        lib/glad/src/glad.c

        lib/imgui/imgui.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/backends/imgui_impl_glfw.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp
        lib/imgui/misc/cpp/imgui_stdlib.cpp

        lib/stb/stb_image.cpp
)

set(INCLUDES
        include

        # Libraries
        lib/glad/include
        lib/imgui
        lib/imgui/backends
        lib/stb
)

set(LIBRARIES
        glfw
        dl
        pthread
        X11
        Xxf86vm
        Xrandr
        Xi
)

# Add executables
add_executable(${PROJECT_NAME} src/main.cpp
        ${SOURCES}
        src/applications/Application.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})