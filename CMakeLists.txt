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
        # Classes
        src/engine/ApplicationBase.cpp
        src/engine/Camera.cpp
        src/engine/Image.cpp
        src/engine/Scene.cpp
        src/engine/Shader.cpp
        src/engine/Texture.cpp
        src/engine/Window.cpp

        src/maths/mat3.cpp
        src/maths/mat4.cpp
        src/maths/vec2.cpp
        src/maths/vec3.cpp
        src/maths/vec4.cpp
        src/maths/quaternion.cpp

        src/mesh/LineMesh.cpp
        src/mesh/Mesh.cpp
        src/mesh/PointMesh.cpp
        src/mesh/TriangleMesh.cpp

        src/utility/Random.cpp

        # Other Sources
        src/maths/geometry.cpp
        src/maths/transforms.cpp
        src/maths/trigonometry.cpp
        src/mesh/meshes.cpp

        # Libraries
        lib/glad/src/glad.c

        lib/imgui/imgui.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/backends/imgui_impl_glfw.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp

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