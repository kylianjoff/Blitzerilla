#ifndef GAME_STATES_H
#define GAME_STATES_H

#include <stdbool.h>

// États du jeu
typedef enum {
    STATE_START,
    STATE_MAIN_MENU,
    STATE_GAME_OPTION,
    STATE_CHARACTER_SELECT,
    STATE_LEVEL_SELECT,
    STATE_SETTINGS,
    STATE_GAME
} GameState;

// Structure principale du contexte de jeu
typedef struct {
    GameState current_state;
    GameState next_state;
    bool state_changed;
    int selected_level;
    int score;
    bool running;
    bool SDL2_interface;
} GameContext;

// Variables globales
extern GameContext g_context;

// Fonctions utilitaires
void change_state(GameState new_state);
void init_game_context(bool use_sdl);

#endif