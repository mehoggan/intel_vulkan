#!/bin/bash

folder=$1/Data

function convert {
  if [ -f "./$folder/$1.$2" ]; then
    echo "Converting $1.$2 shader..."
    glslangValidator -V -H -o $folder/$1.$2.spv $folder/$1.$2 > $folder/$1.$2.spv.txt
  fi
}

if [ "$1" == "" ]; then
  echo "No arguments provided! Please specify folder and shader file name without extension."
  echo "Example usage: source compile_shaders.sh Tutorials/03 shader"
elif [ "$2" == "" ]; then
  echo "Shader name not provided! Please specify folder name and shader file name without extension."
  echo "Example usage: source compile_shaders.sh Tutorials/03 shader"
else
  echo "Converting GLSL shaders into SPIR-V assembly in the '$folder' folder."
  convert $2 vert
  convert $2 frag
fi
