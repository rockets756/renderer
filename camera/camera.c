#include "camera.h"
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include "../../glad/glad.h"

#define MAX_SPEED   5.0f
#define SENSITIVITY 0.06f

#define mat4s(x) (mat4s) {{x, x, x, x}, {x, x, x, x}, {x, x, x, x}, {x, x, x, x}}
#define vec3s(x) (vec3s) {x, x, x}

double pitch = 0.0;
double yaw = -90.0;
float  movx, movy, movz;
// Initializing to 1 to prevent dividing by zero
int screen_width = 1;
int screen_height = 1;

#define up (vec3s) {0.0f, 1.0f, 0.0f}
vec3s cameraPos = {0.0f, 0.0f, 3.0f};

int upinit = 0;

// TODO: Setup 3d world
void update_camera(ShaderProgram shaderProgram, double delta_time) {
    // Calculate cameraDirection from pitch and yaw
    vec3s cameraDirection = {
        cosf(glm_rad(yaw)) * cosf(glm_rad(pitch)),
        sinf(glm_rad(pitch)),
        sinf(glm_rad(yaw) * cosf(glm_rad(pitch)))
    };
    vec3s cameraFront = glms_normalize(cameraDirection);
    vec3s cameraRight = glms_normalize(glms_cross(up, cameraDirection));
    vec3s cameraUp = glms_cross(cameraDirection, cameraRight);
    // Calculate camera movement from movx, movy, and movz
    cameraPos = glms_vec3_add(cameraPos, glms_vec3_mul(glms_normalize(glms_cross(cameraFront, cameraUp)), vec3s(movx * MAX_SPEED * delta_time)));
    cameraPos = glms_vec3_add(cameraPos, glms_vec3_mul(cameraFront, vec3s(movy * MAX_SPEED * delta_time)));
    cameraPos = glms_vec3_add(cameraPos, (vec3s){0x00, movz * MAX_SPEED * delta_time, 0x00});

    mat4s proj;
    mat4s view;
    proj = glms_mat4_identity();
    view = glms_mat4_identity();
    proj = glms_perspective(glm_rad(45.0f), screen_width / screen_height, 0.01f, 1000.0f);
    view = glms_lookat(cameraPos, glms_vec3_add(cameraPos, cameraFront), cameraUp);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program_id, "proj"), 1, GL_FALSE, (const GLfloat *) &proj);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.program_id, "view"), 1, GL_FALSE, (const GLfloat *) &view);
}

double lastX = 400;
double lastY = 400;

void change_look(double xPos, double yPos) {
    double XOffset = xPos - lastX;
    double YOffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
    lastX = xPos;
    lastY = yPos;

    XOffset *= SENSITIVITY;
    YOffset *= SENSITIVITY;

    yaw   += XOffset;
    pitch += YOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}

void change_camera_screen_size(int width, int height) {
    screen_width = width;
    screen_height = height;
}

void change_directional_input(double _movx, double _movy, double _movz) {
    movx = _movx;
    movy = _movy;
    movz = _movz;
}

void change_camera_pos(float x, float y, float z) {
    cameraPos = (vec3s) {x, y, z};
}
