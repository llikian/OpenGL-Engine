# OpenGL Engine
## Project Description
This project is a 

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
Vulkan
GLFW
GLM