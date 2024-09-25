cmake_minimum_required(VERSION 3.20)
project(renderer)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(cglm)

include_directories(glfw/include cglm/include)

add_executable(${PROJECT_NAME}
        main.c
        glad/glad.c glad/glad.h
        window/window.c window/window.h
        rendering/rendering.c rendering/rendering.h
        rendering/shaders/shaders.c rendering/shaders/shaders.h
        rendering/vao/vao.c rendering/vao/vao.h
        rendering/vbo/vbo.c rendering/vbo/vbo.h
        camera/camera.c camera/camera.h window/gui.c window/gui.h)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES})

add_compile_options(-fpermissive)
