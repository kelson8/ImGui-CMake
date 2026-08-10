 
# ImGui CMake

This will be a test with ImGui and CMake using custom fonts, and has only been tested on PopOS 24.04 but should
run on just about any Debian based distro.

I will be making a Windows build for this project later on, and setting up a Docker image in the future for easier building.

This is using OpenGL3, and GLFW.

Required packages for Linux, there are probably more that are required, I am just not sure.
* build-essential
* cmake
* gcc
* g++
* libglew-dev
* libglfw3-dev
* libglfw3
* libc6-dev

# Building
To build this project:

1. Setup the CMake files
```bash
cmake -B build
```

2. Build the project
```bash
cmake --build build --parallel
```

3. Copy the `fonts` folder into the same directory as ImGui, I will automate this with CMake later. 

## Credits
Originally from this Gist
* https://gist.github.com/OlegSirenko/d754372886a32afc82e02f517f8b275a


Another gist here that might work for this
* https://gist.github.com/rokups/f771217b2d530d170db5cb1e08e9a8f4

Credit to user-grinch on GitHub for the ImGui menu style and fonts
* https://github.com/user-grinch/Cheat-Menu


# License
This project is licensed under the MIT license.