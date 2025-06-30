#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "./lib/SDL2.h"
#include "./lib/input.h"

void create_window() {
    if(!SDL2_create_window("[NOM]")) {
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

int main() {
    create_window();

    while(continuer) {
        input_update();
        SDL_GetWindowSize(window, &width, &height);

        SDL2_clear((palette_t){0, 0, 0, 255});

        SDL2_RenderPresent();

        SDL_Delay(16);
        continuer = false;
    }

    SDL2_cleanup();

    return 0;
}