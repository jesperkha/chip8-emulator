#include <stdio.h>
#include "draw.h"

int main(int argc, char** argv)
{
	chip8_window* window = chip8win_init("My Window", 640, 480);
	if (window == NULL)
	{
		printf("Failed to init, %s", SDL_GetError());
		return 1;
	}

	while (!chip8win_update(window))
	{
		;
	}
	
	chip8win_quit(window);
	return 0;
}
