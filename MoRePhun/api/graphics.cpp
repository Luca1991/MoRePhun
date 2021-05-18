#include "..\mophun_os.h"

void MophunOS::vClearScreen(uint32_t color)
{
	
	uint8_t rgb[3];
	rgb[0] = (color & 0x7C00) >> 7;
	rgb[1] = (color & 0x3E0) >> 2;
	rgb[2] = (color & 0x1f) << 3;
	SDL_SetRenderDrawColor(video->app.renderer, rgb[0], rgb[1], rgb[2], 255);
	SDL_RenderClear(video->app.renderer);
}


void MophunOS::vFlipScreen(uint32_t block)
{
	// FIXME TODO: check vblank
	SDL_RenderPresent(video->app.renderer);
}