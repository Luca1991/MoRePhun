#include "video.h"
#include <iostream>

Video::Video()
{
	int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	int windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
		exit(1);
	}

	app.window = SDL_CreateWindow("MoRePhun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		std::cout << "Failed to open " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT <<" window: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

Video::~Video()
{
}