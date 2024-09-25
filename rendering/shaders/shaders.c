#include "shaders.h"
#include <stdio.h>
#include "../../glad/glad.h"

void compile_shader(Shader shader) {
    glShaderSource(shader.shader_id, 1, &shader.shader_source, NULL);
    glCompileShader(shader.shader_id);
    int success;
    char infoLog[512];
    glGetShaderiv(shader.shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader.shader_id, 512, NULL, infoLog);
        fprintf(stderr, "Shader compilation failed.\n%s\n", infoLog);
    }
}

void destroy_shader(Shader shader) {
    glDeleteShader(shader.shader_id);
}

void attach_shader(ShaderProgram shaderProgram, Shader shader) {
    glAttachShader(shaderProgram.program_id, shader.shader_id);
}

void link_shader_program(ShaderProgram shaderProgram) {
    glLinkProgram(shaderProgram.program_id);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram.program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram.program_id, 512, NULL, infoLog);
        fprintf(stderr, "Shader program linking failed.\n%s\n", infoLog);
    }
}
