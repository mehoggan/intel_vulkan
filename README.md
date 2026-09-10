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
sudo apt install -y glslc
```

### Generating Shader Files

Each tutorial's GLSL sources live in `resources/NN/Data/shader.NN.{vert,frag}`
and are compiled to two committed artifacts alongside them:

- `shader.{vert,frag}.NN.spv` — the compiled SPIR-V binary the tutorial
  binary loads at runtime.
- `shader.{vert,frag}.NN.spv.txt` — a human-readable SPIR-V disassembly of
  that binary, committed for review/diffing; not read by any tutorial.

Both are generated with `glslc` (package `glslc`, from the `shaderc`
project):

```sh
cd resources/NN/Data
glslc shader.NN.vert -o shader.vert.NN.spv       # binary
glslc -S shader.NN.vert -o shader.vert.NN.spv.txt  # disassembly
glslc shader.NN.frag -o shader.frag.NN.spv
glslc -S shader.NN.frag -o shader.frag.NN.spv.txt
```

(replace `NN` with the tutorial number, e.g. `07`). The `spirv-tools`
package installed above provides `spirv-dis`/`spirv-val` if you'd rather
disassemble or validate an existing `.spv` directly instead of
recompiling from source — `spirv-dis` produces the same disassembly
style `glslc -S` does, since `glslc` uses it internally.
