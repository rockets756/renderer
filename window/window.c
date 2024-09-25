#include "window.h"
#include <stdio.h>
#include "../../camera/camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* create_main_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, "Renderer", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    return window;
}

// TODO: FIX A AND D
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_W:
            if (action == GLFW_PRESS) change_directional_input(0, 1, 0);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) change_directional_input(0, -1, 0);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_A:
            if (action == GLFW_PRESS) change_directional_input(-1, 0, 0);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS) change_directional_input(1, 0, 0);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) change_directional_input(0, 0, 1);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
        case GLFW_KEY_C:
            if (action == GLFW_PRESS) change_directional_input(0, 0, -1);
            else if (action == GLFW_RELEASE) change_directional_input(0, 0, 0);
            break;
    }
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) change_look(xPos, yPos);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    change_camera_screen_size(width, height);
}
