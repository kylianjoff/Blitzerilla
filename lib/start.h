#ifndef START_H
#define START_H

#include "game_states.h"

// Option à l'écran de démarrage
typedef enum {
    START_PLAY,
    START_OPTION,
    START_QUIT
} StartOption;

// Fonctions du démarrage

void start_init();
void start_update();
void start_render();
void start_cleanup();

#endif