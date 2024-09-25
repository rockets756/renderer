#include "glad/glad.h"
#include <stdio.h>

#include "window/window.h"
#include "window/gui.h"
#include "rendering/shaders/shaders.h"
#include "rendering/vbo/vbo.h"
#include "camera/camera.h"

#define WIREFRAME 0x00

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

double timeI, timeF, delta_time;
const char *vertexShaderSource =    "#version 330 core\n"
                                    "\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "\n"
                                    "uniform mat4 proj;\n"
                                    "uniform mat4 view;\n"
                                    "\n"
                                    "void main() {\n"
                                    "    gl_Position = proj * view * vec4(aPos, 1.0);\n"
                                    "}\n\0";
const char *fragmentShaderSource =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main() {\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n\0";

int main()
{
    GLFWwindow* window = create_main_window();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD.\n");
        return -1;
    }

    // Init gui
    init_gui(window);

    // Create and compile shaders
    Shader vertex_shader = {glCreateShader(GL_VERTEX_SHADER), vertexShaderSource};
    compile_shader(vertex_shader);
    Shader fragment_shader = {glCreateShader(GL_FRAGMENT_SHADER), fragmentShaderSource};
    compile_shader(fragment_shader);

    // link shaders
    ShaderProgram shaderProgram = { glCreateProgram() };
    attach_shader(shaderProgram, vertex_shader);
    attach_shader(shaderProgram, fragment_shader);
    link_shader_program(shaderProgram);

    destroy_shader(vertex_shader);
    destroy_shader(fragment_shader);

    // Vertices needed to make a cube
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    int attributes[] = {
            3
    };
    VAO vao = {0x00};
    glGenVertexArrays(1, &vao.id);
    VBO vbo = {0x00, vertices, sizeof(vertices), (sizeof(attributes) / sizeof(int)), attributes};

    create_vbo(vbo, vao);

    // Set the background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

#if WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Get the time this frame started (used to calculate delta_time at the end)
        timeI = glfwGetTime();

        // Update gui
        update_gui();

        // Update Camera
        update_camera(shaderProgram, delta_time);

        // Clear frame
        glClear(GL_COLOR_BUFFER_BIT);

        // Render frame
        glUseProgram(shaderProgram.program_id);
        glBindVertexArray(vao.id);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
        glBindVertexArray(0);

        // Render gui
        render_gui();

        // Display frame
        glfwSwapBuffers(window);
        // Read window events that happened during this frame
        glfwPollEvents();

        // Calculate delta_time
        timeF = glfwGetTime();
        delta_time = timeF - timeI;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vao.id);
    glDeleteBuffers(1, &vbo.id);

    glDeleteProgram(shaderProgram.program_id);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
