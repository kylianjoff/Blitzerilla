#ifndef SDL2_H
#define SDL2_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct {
    Uint8 r, g, b, a; // Couleur du pixel
} palette_t;

extern bool SDL2_interface; // Booléen qui indique si on est en mode graphique

// char NOM_JEU[100] = "[NOM]";
// char AUTEUR_JEU[100] = "Groupe 10";

extern bool SDL2_initialized; // Statue de l'initialisation de SDL2
extern bool continuer; // Variable de contrôle de la boucle principale
extern SDL_Window *window; // Fenêtre SDL
extern SDL_Renderer *renderer; // Rendu SDL
extern SDL_Event event; // Événements SDL
extern int width; // Largeur de la fenêtre
extern int height; // Hauteur de la fenêtre
extern int window_x; // Position X de la fenêtre
extern int window_y; // Position Y de la fenêtre
extern int mouse_x; // Position X de la souris
extern int mouse_y; // Position Y de la souris
extern TTF_Font * font; // Police TTF pour le texte
extern int font_size; // Taille de la police
bool SDL2_init();
void SDL2_cleanup();
bool SDL2_is_initialized();
void SDL2_handle_error(const char * message);
bool SDL2_create_window(const char * title);
bool SDL2_create_renderer();
void SDL2_set_window_size(int width, int height);
void SDL2_set_window_title(const char * title);
void SDL2_set_window_icon(const char * icon_path);
void SDL2_set_window_position(int x, int y);
void SDL2_set_window_fullscreen(bool fullscreen);
void SDL2_set_window_borderless(bool borderless);
void SDL2_set_window_resizable(bool resizable);
bool SDL2_is_fullscreen();
void SDL2_RenderPresent();
void SDL2_draw_rect(int x, int y, int width, int height, palette_t color);
void SDL2_draw_line(int x1, int y1, int x2, int y2, palette_t color);
void SDL2_draw_line_ep(int x1, int y1, int x2, int y2, int ep, palette_t color);
void SDL2_draw_circle(int x, int y, int radius, palette_t color);
void SDL2_draw_text(const char * text, int x, int y, palette_t color);
void SDL2_draw_text_centered_at(const char *text, int center_x, int center_y, palette_t color);
void SDL2_set_font(const char * font_path, int font_size);
void SDL2_clear(palette_t color);

#endif