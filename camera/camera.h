#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H
#include <../../rendering/shaders/shaders.h>

void update_camera(ShaderProgram shaderProgram, double delta_time);
void change_look(double xPos, double yPos);
void change_camera_screen_size(int width, int height);
void change_directional_input(double _movx, double _movy, double _movz);
void change_camera_pos(float x, float y, float z);

#endif //RENDERER_CAMERA_H
