
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

## Some Renders

<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen1.png" alt="Hyperbolic" width="500">
<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen2.png" alt="Disc" width="500">
<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen3.png" alt="Hyperbolic" width="500">



<!-- GETTING STARTED -->
## Example Usage

```cpp
    // Creating your own App instance
    class App : public conics::Harness{
      // override startup to initialize rendering data
      void startup() override{
        // Sets up data buffer for a hyperbolic shape
        R->setupSurface(1.0f, 1.0f, 10, 1.0f, surface::HYPERBOLIC);
      }
      // override render to call renderer routines
      void render() override{
        R->renderSurface();
      }
    }
  ```

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
