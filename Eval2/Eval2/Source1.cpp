#include <stdio.h>
#include"SDL.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	printf("Hello World")
		return 0;

    int initialize_window(void) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            fprintf(stderr, "Error initializing SDL.\n");
            return false;
        }
        window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
        );

}