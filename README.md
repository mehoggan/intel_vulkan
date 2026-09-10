# vulkan_graphix

A collection of Vulkan API tutorials and examples, demonstrating progressive
concepts from device initialization through rendering.

### Generating .clangdb files for Development Environments

```sh
sudo apt install -y bear
mkdir build
cd build
bear -- ../configure
bear -- make
```

### Installing Ubuntu Dependencies
```sh
sudo apt install -y libvulkan-dev
sudo apt install -y vulkan-validationlayers spirv-tools
```
