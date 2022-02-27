#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

// Type of chip8 window. Abstraction from SDL_Window and SDl_Renderer.
// Used for drawing single lines and pixels.
typedef struct chip8_window {
    SDL_Window* window;
    SDL_Renderer* renderer;
} chip8_window;

// Initialize SDL window and renderer, returns pointer to window object.
// On error, pointer is NULL and error is fetched with SDL_GetError().
chip8_window* chip8win_init(char* name, int width, int height);

// Updates renderer and then clears it. Returns 1 if the
// window quit event was polled.
int chip8win_update(chip8_window* window);

// Graceful window and renderer destruction and sdl exit
void chip8win_quit(chip8_window* window);

#endif