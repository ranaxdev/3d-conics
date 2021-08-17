
<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/ranaxdev/3d-conics">
    <img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">3d-conics</h3>

  <p align="center">
    A 3D surface and conics visualizer made using OpenGL and C++
    <br />
    <br />
    <a href="https://www.youtube.com/watch?v=Im53k-E3cvE&list=PLhiYhW5wXPMGojFRwhahrtsvO-ng5asoc">Video Demos</a>
    ·
    <a href="https://github.com/ranaxdev/3d-conics/issues">Report Bug</a>
  </p>
</p>

<hr>

| [Preview](#preview) - [Future Releases](#future-releases) - [Example Usage](#example-usage) - [Some Renders](#some-renders) - [Installation](#installation) |
:----------------------------------------------------------: |
| [Libraries Used](#libraries-used) - [License](#license) - [Contact](#contact) |


<!-- ABOUT THE PROJECT -->
## Preview
https://user-images.githubusercontent.com/44033302/129494506-d0533c17-6057-4c43-9b3d-f69dc9af4e8b.mp4

<br>

As of `15/08/2021`, **3d-conics** features mesh generation based on multivaraible functions and live interaction with their properties (such as controlling the domain/range & applying transformations) with a handful of 3D surfaces and conics. 

The mesh properties can be adjusted via a GUI overlay (Dear Imgui integration) and viewed through a controllable 3D perspective projection camera, which are implemented as separate modes (edit and normal respectively). 

A mesh generating menu allows you to select a handful of prefabricated functions (such as `PARABOLOID`, `HYPERBOLIC PARABOLOID`, `SINGLE CONE`, `DOUBLE CONE`, `CYLINDER`, `SPHERE` and a couple more) and their initialization properties.

### Future Releases

Features that I would like to work towards implementing
- Live delaunay triangulation
- Rendering multiple meshes in the same application instance
- Live mesh vertex editor
- Live mesh painting
- Custom transformations

Feel free to suggest some features in the issues tab!


## Example Usage 
### Developers
Creating your own App instance using the conics harness
```cpp
class App : public conics::Harness{
  Camera* camera = new Camera();
  Spawner* spawner = new Spawner();
  // override startup to initialize rendering data
  void startup() override{
    // Sets up data buffer for a cone shape (starting mesh)
    R->default_mesh = new Mesh(surface::CONE...);
  }
  // override render to call renderer routines
  void render() override{
    VP = camera->calc_VP(delta);
    // GUI
    R->renderGUI(*spawner);
    // MESH
    R->renderMesh(*R->default_mesh);
  }
}
  ```

Creating your own GUI overlay window
```cpp
// Creating your own GUI
class MyGUI : public GUI {
  void update() override;
  ...
}
MyGUI::MyGUI(){
  MyGUI::flag_list {/* your ImGUI flags here */};
  MyGUI::updateFlags();
  
  // If you want to change GUI with events attach to the KL
  KeyListener::listeners.push_back(this);
}

```

## Some Renders

`HYPERBOLIC PARABOLOID` (saddle) generated with &nbsp;&nbsp;&nbsp;<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/saddle_eq.png">

![saddle_o](https://user-images.githubusercontent.com/44033302/129497075-bfba1328-ddee-4e38-ac19-85d7c490b616.gif)


`PARABOLOID` generated with &nbsp;&nbsp;&nbsp;<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/paraboloid_eq.png">

![paraboloid_o](https://user-images.githubusercontent.com/44033302/129495259-617b4158-8033-49df-82d9-bbc076f3166c.gif)


`SINGLE CONE` generated parametrically with

<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/cone_eq.png">

The cone is stretching because I was live-editing the t-factor

![cone_o](https://user-images.githubusercontent.com/44033302/129498766-9edafc7f-f19d-4b2b-8eb5-85dfb6cf1424.gif)


`TORUS` generated parametrically with

<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/torus_eq.png">

The torus "wraps" in the render because I was live-editing the value of theta

![torus_o](https://user-images.githubusercontent.com/44033302/129497589-9c5079a4-beb4-4615-a89b-052a5d32a301.gif)

## Installation
### Linux

Dependencies include `OpenGL 4.50`, `libdl`, `glfw3`, `pthread`, `sqlite3`, `glm`

```bash
git clone https://github.com/ranaxdev/3d-conics
cd 3d-conics
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../
make
```

<!-- GETTING STARTED -->

## Libraries Used

- [GLAD](https://github.com/Dav1dde/glad)
: OpenGL Loading Library

- [GLM](https://github.com/g-truc/glm)
: OpenGL Mathematics

- [GLFW](https://www.glfw.org/)
: A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input 

- [Dear ImGui](https://github.com/ocornut/imgui)
: Bloat-free Graphical User interface for C++ with minimal dependencies 

<!-- LICENSE -->
## License

Distributed under the Apache 2.0 License. See `LICENSE` for more information.


<!-- CONTACT -->
## Contact

S.R. Qaiser - [@pitu_dev](https://twitter.com/pitu_dev) - sc21srq@leeds.ac.uk

Project Link: [https://github.com/ranaxdev/3d-conics](https://github.com/ranaxdev/3d-conics)
