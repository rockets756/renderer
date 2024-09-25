#ifndef RENDERER_VBO_H
#define RENDERER_VBO_H
#include "../../glad/glad.h"
#include "../vao/vao.h"

struct VBO {
    GLuint id;
    float* vertices;
    int vertices_size; // sizeof(vertices)
    GLint attributes;
    GLint* attribute_sizes;
}typedef VBO;

void create_vbo(VBO vbo, VAO vao);

#endif //RENDERER_VBO_H
