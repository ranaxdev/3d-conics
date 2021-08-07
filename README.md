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
    <a href="https://github.com/ranaxdev/3d-conics">Video Demos</a>
    ·
    <a href="https://github.com/ranaxdev/3d-conics/issues">Report Bug</a>
  </p>
</p>


<!-- ABOUT THE PROJECT -->
## Some Renders
<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen1.png" alt="Hyperbolic" width="500">
<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen2.png" alt="Disc" width="500">
<img src="https://github.com/ranaxdev/3d-conics/blob/main/Res/screen3.png" alt="Hyperbolic" width="500">


### Future Releases

Eventually, the plan is to create an interactive application where you can view the surfaces and conics live and have interaction with their properties i.e. adjusting level of details on the surface, applying transformations to them, plotting custom functions etc.

<!-- GETTING STARTED -->
### Example Usage

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

<!-- LICENSE -->
## License

Distributed under the Apache 2.0 License. See `LICENSE` for more information.


<!-- CONTACT -->
## Contact

S.R. Qaiser - [@pitu_dev](https://twitter.com/pitu_dev) - sc21srq@leeds.ac.uk

Project Link: [https://github.com/ranaxdev/3d-conics](https://github.com/ranaxdev/3d-conics)
