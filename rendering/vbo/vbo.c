#include "vbo.h"

void create_vbo(VBO vbo, VAO vao) {
    glGenBuffers(1, &vbo.id);
    glBindVertexArray(vao.id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
    glBufferData(GL_ARRAY_BUFFER, vbo.vertices_size, vbo.vertices, GL_STATIC_DRAW);

    int attributes_total_size;
    for (int i = 0; i < vbo.attributes; i++) {
        attributes_total_size += vbo.attribute_sizes[i];
    }
    int attributes_current_size;
    for (int i = 0; i < vbo.attributes; i++) {
        glVertexAttribPointer(i, vbo.attribute_sizes[i], GL_FLOAT, GL_FALSE, attributes_total_size * sizeof(float), (void *) (attributes_current_size * sizeof(float)));
        glEnableVertexAttribArray(i);
        attributes_current_size += vbo.attribute_sizes[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Now that we are done we can unbind the buffer
}
