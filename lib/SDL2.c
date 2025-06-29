#include "SDL2.h"

bool SDL2_initialized = false;
bool continuer = true;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
int width = 1200; // Largeur par défaut de la fenêtre
int height = 800; // Hauteur par défaut de la fenêtre
int window_x = SDL_WINDOWPOS_CENTERED; // Position X de la fenêtre
int window_y = SDL_WINDOWPOS_CENTERED; // Position Y de la fenêtre
int mouse_x = 0; // Position X de la souris
int mouse_y = 0; // Position Y de la souris
TTF_Font *font = NULL; // Police TTF pour le texte
int font_size = 24; // Taille de la police par défaut

bool SDL2_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL2_handle_error("Erreur d'initialisation de la SDL");
        return false;
    }

    if (TTF_Init() == -1) {
        SDL2_handle_error("Erreur d'initialisation de TTF");
        SDL_Quit();
        return false;
    }

    SDL2_initialized = true;
    return true;
}

void SDL2_cleanup() {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    TTF_Quit();
    SDL_Quit();
    SDL2_initialized = false;
}

bool SDL2_is_initialized() {
    return SDL2_initialized;
}

void SDL2_handle_error(const char * message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
}

bool SDL2_create_window(const char * title) {
    window = SDL_CreateWindow(title, window_x, window_y, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL2_handle_error("Erreur de création de la fenêtre");
        return false;
    }
    return true;
}

bool SDL2_create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL2_handle_error("Erreur de création du renderer");
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return true;
}

void SDL2_set_window_size(int w, int h) {
    width = w;
    height = h;
    if (window) {
        SDL_SetWindowSize(window, width, height);
    }
}

void SDL2_set_window_title(const char * title) {
    if (window) {
        SDL_SetWindowTitle(window, title);
    }
}

void SDL2_set_window_icon(const char * icon_path) {
    SDL_Surface *icon = IMG_Load(icon_path);
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } else {
        SDL2_handle_error("Erreur de chargement de l'icône de la fenêtre");
    }
}

void SDL2_set_window_position(int x, int y) {
    window_x = x;
    window_y = y;
    if (window) {
        SDL_SetWindowPosition(window, window_x, window_y);
    }
}

void SDL2_set_window_fullscreen(bool fullscreen) {
    if (window) {
        SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }
}

void SDL2_set_window_borderless(bool borderless) {
    if (window) {
        SDL_SetWindowBordered(window, !borderless);
    }
}

void SDL2_set_window_resizable(bool resizable) {
    if (window) {
        SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);
    }
}

bool SDL2_is_fullscreen() {
    return (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) != 0;
}

void SDL2_RenderPresent() {
    if (renderer) {
        SDL_RenderPresent(renderer);
    }
}

void SDL2_draw_rect(int x, int y, int w, int h, palette_t color) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void SDL2_draw_line(int x1, int y1, int x2, int y2, palette_t color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SDL2_draw_line_ep(int x1, int y1, int x2, int y2, int ep, palette_t color) {
    for(int i=-ep/2;i<(ep+1)/2;i++) {
        SDL2_draw_line(x1+i, y1+i, x2+i, y2+i, color);
    }
}

void SDL2_draw_circle(int x, int y, int radius, palette_t color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Distance horizontale du centre
            int dy = radius - h; // Distance verticale du centre
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void SDL2_draw_text(const char * text, int x, int y, palette_t color) {
    if (!font) {
        fprintf(stderr, "Aucune police définie pour le texte\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, (SDL_Color){color.r, color.g, color.b, color.a});
    if (!surface) {
        SDL2_handle_error("Erreur de rendu du texte");
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        SDL2_handle_error("Erreur de création de la texture du texte");
        return;
    }

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void SDL2_draw_text_centered_at(const char *text, int center_x, int center_y, palette_t color) {
    int text_width, text_height;
    if (TTF_SizeText(font, text, &text_width, &text_height) != 0) {
        fprintf(stderr, "Erreur lors du calcul de la taille du texte : %s\n", TTF_GetError());
        return;
    }
    int x = center_x - text_width / 2;
    int y = center_y - text_height / 2;
    SDL2_draw_text(text, x, y, color);
}

void SDL2_set_font(const char * font_path, int size) {
    if (font) {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(font_path, size);
    if (!font) {
        SDL2_handle_error("Erreur de chargement de la police");
    } else {
        font_size = size;
    }
}

void SDL2_clear(palette_t color) {
    if (!renderer) return; // Ajoute ceci par sécurité
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}