#include "gui.h"
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "../nuklear/nuklear.h"
#include "../nuklear/demo/glfw_opengl3/nuklear_glfw_gl3.h"
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#include "../camera/camera.h"


struct nk_glfw glfw = {0};
struct nk_context *ctx;
struct nk_colorf bg;
struct nk_font_atlas *atlas;

void init_gui(GLFWwindow* window) {
    ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);
}

float camx, camy, camz;

void update_gui() {
    nk_glfw3_new_frame(&glfw);

    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nk_layout_row_static(ctx, 30, 200, 1);
        nk_slider_float(ctx, -10, &camx, 10, 0.5f);
        nk_slider_float(ctx, -10, &camy, 10, 0.5f);
        nk_slider_float(ctx, -10, &camz, 10, 0.5f);
    }

    nk_end(ctx);
    change_camera_pos(camx, camy, camz);
}

void render_gui() {
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_OFF, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}
