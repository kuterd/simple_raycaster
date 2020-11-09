cmake_minimum_required (VERSION 2.8.11)
project (ToyRaycaster)

add_executable(
  ToyRaycaster
  src/main.c
  src/vec.c
  src/bitmap.c
  src/material.c
  src/scene.c
  src/object.c
  src/utils.c
)
target_link_libraries(ToyRaycaster m)
