#include <stdio.h>
#include <draw.h>

window_t window;

window_t* chip8win_init(char* name, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (sdl_window == NULL) {
		return NULL;
	}

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
	if (sdl_renderer == NULL) {
		return NULL;
	}

    window.renderer = sdl_renderer;
    window.window = sdl_window;
    return &window;
}

int chip8win_update(window_t* window)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 1;
        }
    }

    SDL_RenderPresent(window->renderer);
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
    return 0;
}

void chip8win_quit(window_t* window)
{
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	SDL_Quit();
}

void chip8win_point(window_t* window, int x, int y)
{
    SDL_RenderDrawPoint(window->renderer, x, y);
}