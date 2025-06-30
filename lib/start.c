#include "start.h"
#include "SDL2.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

static int selected_option = START_PLAY;

void start_init() {
    selected_option = START_PLAY;
    printf("=== Ecran de démarrage du jeu ===\n");
}

void start_update() {
    if(input_is_key_just_pressed(SDL_SCANCODE_SPACE)) {
        change_state(STATE_GAME_OPTION);
    }
}

void start_render() {
    SDL2_draw_rect(0, 0, 200, 200, (palette_t){255, 0, 0, 255});

    SDL2_set_font("assets/fonts/damage_plan.ttf", 100);
    SDL2_draw_text_centered_at("BLITZERILLA", width/2, height/10, (palette_t){255, 255, 255, 255});
}

void start_cleanup() {
    printf("écran de démarrage nettoyé.\n");
}