#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

// Type of chip8 window. Abstraction from SDL_Window and SDl_Renderer.
// Used for drawing single lines and pixels.
typedef struct window_t {
    SDL_Window* window;
    SDL_Renderer* renderer;
} window_t;

// Initialize SDL window and renderer, returns pointer to window object.
// On error, pointer is NULL and error is fetched with SDL_GetError().
window_t* chip8win_init(char* name, int width, int height);

// Updates renderer and then clears it. Returns 1 if the
// window quit event was polled.
int chip8win_update(window_t* window);

// Graceful window and renderer destruction and sdl exit
void chip8win_quit(window_t* window);

// Draw single pixel at (x, y)
void chip8win_point(window_t* window, int x, int y);

#endif