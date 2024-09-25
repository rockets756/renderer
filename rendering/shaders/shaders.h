#ifndef RENDERER_SHADERS_H
#define RENDERER_SHADERS_H

struct Shader {
    unsigned int shader_id;
    const char* shader_source;
}typedef Shader;

struct ShaderProgram {
    unsigned int program_id;
}typedef ShaderProgram;

void compile_shader(Shader shader);
void destroy_shader(Shader shader);
void create_shader_program(ShaderProgram shaderProgram);
void destroy_shader_program(ShaderProgram shaderProgram);
void attach_shader(ShaderProgram shaderProgram, Shader shader);
void link_shader_program(ShaderProgram shaderProgram);

#endif //RENDERER_SHADERS_H
