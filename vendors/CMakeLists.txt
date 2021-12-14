cmake_minimum_required(VERSION 3.8)

# CGLM
set(CGLM_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(cglm)

# Glad
add_subdirectory(glad)

# GLFW
add_subdirectory(glfw)

# stb
add_subdirectory(stb)
