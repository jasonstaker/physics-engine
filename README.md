<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<br />
<div align="center">
  <a href="https://github.com/jasonstaker/physics-engine">
    <img src="assets/images/wip.png" alt="Logo">
  </a>

  <h3 align="center">3D Physics Engine</h3>

  <p align="center">
    A modular, real-time 3D physics engine — design is underway.
    <br />
    <a href="https://github.com/jasonstaker/physics-engine"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/jasonstaker/physics-engine">Demo (TBD)</a>
    &middot;
    <a href="https://github.com/jasonstaker/physics-engine/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    &middot;
    <a href="https://github.com/jasonstaker/physics-engine/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#introduction">Introduction</a></li>
    <li><a href="#planned-tools">Planned Tools</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## Introduction

This is the foundation for a fully‑featured **3D physics engine**.  
While no code exists yet, the aim is to support rigid body dynamics, collision detection, constraint solving, and real-time rendering.
It’s intended as:
- An educational resource for understanding physics simulation internals  
- A base for games, simulations, or interactive applications  

My two favorite areas in my studies have been both physics and computer science, and I am beyond thrilled to combine them into something that could have a use.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Planned Tools

- **C++** (or future language choice)  
- **Math libraries** for vectors, matrices, and quaternions  
- **Spatial acceleration**: BVH, grids, or octrees  
- **Collision detection**: GJK + EPA, AABB, sphere-tree  
- **Constraint solvers**: sequential impulse or LCP  
- **Rendering**: TBD (OpenGL, Vulkan, or others)  
- **Build system**: CMake

Note that these were simply found based on preliminary research, and are highly subject to change as the project evolves.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Getting Started

### Prerequisites

- Install a C++17+ toolchain  
- Set up your build system (e.g. CMake, Meson, or your IDE)  
- Prepare math and rendering dependencies

### Installation

```bash
git clone https://github.com/jasonstaker/physics-engine.git
cd physics-engine
# initialize build system, add dependencies, and scaffold structure
````

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

This repo, at the time of writing this, currently contains nothing. Here’s what it may support:

* `Vec3`, `Mat3`, `Quaternion` base math types
* Collision detection steps: broadphase → narrow phase → resolution
* Simulation loop with time stepping and constraint resolution

Example usage (future):

```cpp
Scene scene;
auto box = scene.createRigidBodyBox(/* size, mass, initial_pos */);
scene.stepSimulation(deltaTime);
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Roadmap

* [ ] Create repo scaffolding & interface definitions
* [ ] Implement Vec3, Mat3, Quaternion math
* [ ] Rigid body dynamics with integration
* [ ] Broadphase & narrowphase collision detection
* [ ] Constraint resolution & joint support
* [ ] Spatial partition for performance
* [ ] Real-time visual debugger / renderer
* [ ] Unit tests & CI
* [ ] Comprehensive documentation

See the [open issues](https://github.com/jasonstaker/physics-engine/issues) for full details.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contributing

Contributions are welcome—design ideas, code, docs, etc.

1. Fork the repo
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit (`git commit -m "Add AmazingFeature"`)
4. Push (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License

[MIT License](LICENSE)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

**Jason Staker** – [jason.staker@example.com](mailto:jason.staker@example.com)  
Project: [github.com/jasonstaker/physics-engine](https://github.com/jasonstaker/physics-engine)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/jasonstaker/physics-engine.svg?style=for-the-badge
[contributors-url]: https://github.com/jasonstaker/physics-engine/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/jasonstaker/physics-engine.svg?style=for-the-badge
[forks-url]: https://github.com/jasonstaker/physics-engine/network/members
[stars-shield]: https://img.shields.io/github/stars/jasonstaker/physics-engine.svg?style=for-the-badge
[stars-url]: https://github.com/jasonstaker/physics-engine/stargazers
[issues-shield]: https://img.shields.io/github/issues/jasonstaker/physics-engine.svg?style=for-the-badge
[issues-url]: https://github.com/jasonstaker/physics-engine/issues
[license-shield]: https://img.shields.io/github/license/jasonstaker/physics-engine.svg?style=for-the-badge
[license-url]: https://github.com/jasonstaker/physics-engine/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/jason-staker-53b8a9280/