#pragma once
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct Renderer{
	SDL_Renderer *renderer;
	SDL_Window *window;
};


class Video {
	public:
		Video();
		~Video();
		Renderer app;
};