cmake_minimum_required(VERSION 3.8)

set(
    SOURCES

    core/assert.h
    core/assert.c
    core/defs.h
    core/error.h
    core/error.c
    core/input.h
    core/input.c
    core/log.h
    core/log.c
    core/memory.h
    core/memory.c
    core/state.h
    core/threads.h
    core/threads.c

    allocators/stack_allocator.h
    allocators/stack_allocator.c

    graphics/gl.h
    graphics/gl.c
    graphics/shader.h
    graphics/shader.c

    states/main_state.h
    states/main_state.c

    game.h
    game.c
    main.c
)

set(
    INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/vendors/glad/include"
    "${PROJECT_SOURCE_DIR}/vendors/glfw/include"
)

set(
    LIBRARIES
    glad
    glfw
)

set(
    DEBUG_MACROS
    RGE_DEBUG
    RGE_ENABLE_ASSERT
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    C_STANDARD                          11
    C_STANDARD_REQUIRED                 11
    RUNTIME_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/bin"
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${LIBRARIES}
)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    ${DEBUG_MACROS}
)
