#include "input.h"
#include <string.h>

InputState g_input = {0};
static InputState previous_input = {0};

void input_init() {
    memset(&g_input, 0, sizeof(InputState));
    memset(&previous_input, 0, sizeof(InputState));
}

void input_update() {
    previous_input = g_input;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                g_input.quit_requested = true;
                puts("Arrêt demandé");
                break;
            case SDL_KEYDOWN:
                g_input.keys[event.key.keysym.scancode] = true;
                break;
            case SDL_KEYUP:
                g_input.keys[event.key.keysym.scancode] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                g_input.mouse_buttons[event.button.button] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                g_input.mouse_buttons[event.button.button] = false;
                break;
            case SDL_MOUSEMOTION:
                g_input.mouse_x = event.motion.x;
                g_input.mouse_y = event.motion.y;
                break;
        }
    }
}

bool input_is_key_just_pressed(SDL_Scancode key) {
    return g_input.keys[key] && !previous_input.keys[key];
}

bool input_is_key_pressed(SDL_Scancode key) {
    return g_input.keys[key];
}

bool input_is_mouse_button_pressed(int button) {
    return g_input.mouse_buttons[button];
}