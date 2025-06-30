#include "game_states.h"

// Variable globale du contexte
GameContext g_context;

void change_state(GameState new_state) {
    g_context.next_state = new_state;
    g_context.state_changed = true;
}

void init_game_context(bool use_sdl) {
    g_context.current_state = STATE_START;
    g_context.next_state = STATE_START;
    g_context.state_changed = false;
    g_context.selected_level = 1;
    g_context.score = 0;
    g_context.running = true;
    g_context.SDL2_interface = use_sdl;
}