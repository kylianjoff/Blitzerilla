#ifndef INPUT_H
#define INPUT_H

#include "SDL2.h"
#include <stdbool.h>

typedef struct {
    bool keys[SDL_NUM_SCANCODES];
    bool mouse_buttons[8];
    int mouse_x, mouse_y;
    bool quit_requested;
} InputState;

extern InputState g_input;

void input_init();
void input_update();
bool input_is_key_pressed(SDL_Scancode key);
bool input_is_key_just_pressed(SDL_Scancode key);
bool input_is_mouse_button_pressed(int button);

#endif