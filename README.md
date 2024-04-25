# OpenGL Engine
## Project Description
This project is an implementation of a graphics engine using OpenGL with the GLAD implementation.
It uses GLFW for window and event handling and GLM for maths utilities.

This project is a way to learn OpenGL, I am following [Joey de Vries's tutorial](https://learnopengl.com/).

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make libglfw3-dev libxxf86vm-dev libxi-dev libglm-dev -y
```

### Clone Repository
```shell
git clone https://github.com/llikian/OpenGL-Engine.git
cd OpenGL-Engine
```

### Build
To build you can simply run the `release.sh` script at the root of the project using:
```shell
bash release.sh
```

You can also manually build it using:
```shell
cmake -B build && \
cmake --build build -j
```

Then you can run it using:
```shell
bin/OpenGL-Engine
```

## Credits
Graphics are handled with [OpenGL](https://www.opengl.org/), using the [GLAD](https://github.com/Dav1dde/glad) implementation.

Window management and event handling are done with [GLFW](https://www.glfw.org/).

Maths functionalities like matrices and vectors are handled with [GLM](https://github.com/g-truc/glm).

Image loading is done with [stb_image](https://github.com/nothings/stb).