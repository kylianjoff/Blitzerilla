#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2.h"

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
    return 0;
}