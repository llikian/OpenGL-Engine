# OpenGL Engine
![Screenshot from 2025-01-19 14-47-40.png](screenshots/Screenshot%20from%202025-01-19%2014-47-40.png)

## Project Description
This project is an implementation of a graphics engine using OpenGL with the GLAD implementation.
It uses GLFW for window and event handling and stb_image for loading textures and other images.

This project is for learning purposes. For OpenGL I am using [Joey de Vries's tutorials](https://learnopengl.com/)
as a reference and for more general graphics programming concepts I am also using the [Real-Time Rendering 4th Edition](https://www.realtimerendering.com/)
book.

### Structure
```
./
├─ bin/         # Binary Files
├─ data/        # Assets (textures, etc...)
├─ include/     # Header files (.hpp and .tpp files)
├─ lib/         # Source code of libraries
├─ screenshots/ # Screenshots of the application
├─ shaders/     # Shader code files (.vert, .frag, etc...)
└─ src/         # Source code files (.cpp files)
   ├─ applications/ # Code for the different applications
   ├─ engine/       # Code concerning the engine itself
   ├─ maths/        # Code regarding maths operations and structures (vectors, matrices, etc...)
   └─ mesh/         # Code regarding the definition and creation of meshes
```

### Functionalities
The engine currently supports a few functionalities, separated in multiple classes. First and most
important, the ApplicationBase is a virtual class that is meant to provide the skeleton for any application
using this engine. It initializes the window using the Window class which I'll ellaborate on further,
defines virtual static methods used for handling the GLFW callbacks (which are used to handle events such
as mouth movement, window resizing, key presses and such).

Another thing ApplicationBase handles is how key events are handled. The manner in which they are is
different regarding if the key is meant to be repeatable (if the key is held, the associated action
is repeated) or not. The `std::unordered_map<int, bool> repeatableKeys` member of the class contains all the
keys that are repeatable, it is the responsibility of the application implementing the ApplicationBase
class to fill the map. It associates an integer (corresponding to the GLFW code of a specific key) to
a boolean, when the boolean is true, it means the key is currently being held and so the associated
action should be called. For non repeatable keys it is way more simple, there is simply a queue of the
keys that were pressed that is handled each frame.

So in short, when there's a key callback, we first check if the pressed key is repeatable, if it is,
then we set the associated boolean in the `repeatableKeys` map to true if it was a key press, and to
false if it was a key release (conveniently GLFW_PRESS is equal to 1 and GLFW_RELEASE is equal to 0).
If the pressed key wasn't repeatable we simply add its code to the queue.

Window

Shader

Camera

Image

Texture

Light


This project also contains the basis for another, in order to test the functionality of application
classes inheritting from ApplicationBase. This other application is an attempt at an implementation
of 3D cellular automata. It is currently very basic with no optimization whatsoever.

### Controls
```
Close Application: Escape
Toggle Wireframe Mesh: W
Toggle Cullface: C
Toggle Cursor (Allows to move the camera): TAB
Toggle Drawing Axes: A
Toggle Drawing Grid: G
Toggle Drawing Ground: H
Toggle Global Lighting: J
Move: Z Q S D
Move Upwards: Space
Move Downwards: Left Shift
```

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make libglfw3-dev libxxf86vm-dev libxi-dev -y
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

Image loading is done with [stb_image](https://github.com/nothings/stb).