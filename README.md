# RenderingFramework
This is an OpenGL real-time rendering framework built as a personal project. The motivation behind the project is to serve as a practical exercise on the funtamental topics in real-time graphics. The goal of the framework is to abstract away low-level math and graphics operations and to provide a tool for easy scene creation and editing. The project is still under development. 

After getting refined, the framework is planned to be used as the building foundation of a more complicated research-oriented simulator. 

# Requirements
Since the current purpose of the framework is educational (i.e. mostly for pursonal use), wide software and hardware support is not a priority. Thus, the framework does not provide cross-platform support and relies mostly on modern features of C++ and OpenGL.

That being said, cross-platform compatibility is planned to be introduced in the first refinement of the framework.

Specifically, the framework requirements are as follows:
- Windows OS;
- C++ 17 compiler support;
- OpenGL 4.5 Core Profile hardware support.

# Libraries used
The framework makes use of the following libraries:
- [GLFW](https://www.glfw.org/) - window management and setting up the OpenGL context;
- [GLAD](https://github.com/Dav1dde/glad) - loading OpenGL functions;
- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) - importing textures from files;
- [Assimp](http://www.assimp.org/) - importing 3D models.

# Components
Currently, the framework is divided in two layers - *Math* and *Graphics*. 

The Math layer provides basic functionality for performing calculations with vectors, matrices, and quaternions. Additionally, it contains some Bounding Volume classes and a set of useful math functions.

The Graphics layer is responsible for managing geometry, transformations, and lighting and for preparing the scene for rendering. It includes a camera class that handles mouse-and-keyboard I/O. The first version of the framework was written to support Blinn-Phong reflectance. More advanced lighting techniques are planned for future versions of the framework.

Full documentation to be added once the project is complete.

# Preparaton Resources
Many resources were used during the development of the project. A non-exhaustive list is presented:
- *Mathematics for 3D Game Programming and Computer Graphics, Third edition*, E.Lengyel;
- *OpenGL Superbible: Comprehensive Tutorial and Reference (7th Edition)*, G.Sellers et al.;
- *Graphics Shaders: Theory and Practice, Second Edition*, M.Bailey;
- *Game Engine Architecture, 2nd Edition*, J.Gregory;
- [https://learnopengl.com/](https://learnopengl.com/);
- [http://ogldev.atspace.co.uk/index.html](http://ogldev.atspace.co.uk/index.html).

# Future development
The following features are to be introduced:
- A scenegraph that makes use of parent-child relations;
- Frustum culling;
- Physically-based rendering.
- More effective resource management;
- Cross-platform compatibility;

The intention is that once its design is refined, the framework will be used to build a real-time 3D fluid simulator with a GUI.

# Screenshots
![Screenshot 1](Docs/Screenshots/cottage0.png)
![Screenshot 2](Docs/Screenshots/cottage1.png)
![Screenshot 3](Docs/Screenshots/cottage2.png)

