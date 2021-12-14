cmake_minimum_required(VERSION 3.8)
project(stb)

include_directories(
    include
)

add_library(stb_image STATIC src/stb_image.c include/stb/stb_image.h)
