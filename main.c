#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "./lib/SDL2.h"
#include "./lib/input.h"
#include "./lib/game_states.h"
#include "./lib/start.h"

void create_window() {
    if(!SDL2_create_window("Blitzerilla")) {
        SDL2_handle_error("Erreur de création de la fenêtre");
        // ajouter_log("logs.txt", "-- ERREUR -- Erreur de création de la fenêtre.");
        return;
    }
    
    if (!SDL2_create_renderer()) {
        SDL2_handle_error("Erreur de création du renderer");
        // ajouter_log("logs.tx", "-- ERREUR -- Erreur de création de la fenêtre.");
        return;
    }
    
    SDL2_set_window_resizable(false);
    SDL2_set_window_fullscreen(true);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_GetWindowSize(window, &width, &height);
    // ajouter_log("logs.txt", "Fenêtre créé");
}

void cleanup_current_state() {
    switch (g_context.current_state) {
        case STATE_START:
            start_cleanup();
            break;
        case STATE_MAIN_MENU:
            //menu_cleanup();
            break;
        case STATE_GAME_OPTION:
            //options_cleanup();
            break;
        case STATE_CHARACTER_SELECT:
            //character_select_cleanup();
            break;
        case STATE_LEVEL_SELECT:
            //level_select_cleanup();
            break;
        case STATE_SETTINGS:
            //settings_cleanup();
            break;
        case STATE_GAME:
            //game_cleanup();
            break;
        default:
            break;
    }
}

void init_new_state() {
    switch (g_context.current_state) {
        case STATE_START:
            start_init();
            break;
        case STATE_MAIN_MENU:
            //menu_init();
            break;
        case STATE_GAME_OPTION:
            //game_option_init();
            break;
        case STATE_CHARACTER_SELECT:
            //character_select_init();
            break;
        case STATE_LEVEL_SELECT:
            //level_select_init();
            break;
        case STATE_SETTINGS:
            //settings_init();
            break;
        case STATE_GAME:
            //game_init();
            break;
        default:
            break;
    }
}

int main() {
    // 1. D'ABORD initialiser SDL2 et TTF
    if (!SDL2_init()) {
        printf("Erreur d'initialisation SDL2.\n");
        // ajouter_log("logs.txt", "--- ERREUR --- Erreur d'initialisation SDL2. Passage en mode texte.");
        return -1;
    }
    
    // 2. Initialiser le contexte de jeu
    init_game_context(true);
    
    // 3. Créer la fenêtre UNE SEULE FOIS (maintenant que SDL2 est initialisé)
    create_window();
    
    // 4. Initialiser l'état de départ et l'input
    init_new_state();
    input_init();
    
    // 5. Boucle principale
    while(continuer) {
        input_update();
        SDL_GetWindowSize(window, &width, &height);
        SDL2_clear((palette_t){0, 0, 0, 255});
        
        if(g_context.state_changed) {
            cleanup_current_state();
            g_context.current_state = g_context.next_state;
            g_context.state_changed = false;
            init_new_state();
        }
        
        if(g_input.quit_requested == true) {
            continuer = false;
            g_context.running = false;
        }
        
        switch(g_context.current_state) {
            case STATE_START:
                start_update();
                start_render();
                break;
            case STATE_MAIN_MENU:
                break;
            case STATE_GAME_OPTION:
                break;
            case STATE_CHARACTER_SELECT:
                break;
            case STATE_LEVEL_SELECT:
                break;
            case STATE_SETTINGS:
                break;
            case STATE_GAME:
                break;
            case STATE_QUIT:
                g_input.quit_requested = true;
                break;
        }
        
        SDL2_RenderPresent();
        SDL_Delay(16);
    }
    
    cleanup_current_state();
    SDL2_cleanup();
    return 0;
}