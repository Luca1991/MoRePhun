#include "../mophun_os.h"

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

void MophunOS::vSetForeColor(uint32_t color)
{	// FIXME: need test!
	osdata.currentFgColor = color;
}

uint32_t MophunOS::vSpriteInit(uint8_t count)
{
	osdata.spriteSlots.resize(count);
	return 1;
}

void MophunOS::vSpriteClear()
{
	for (int i=0; i<osdata.spriteSlots.size(); i++)
	{
		SDL_DestroyTexture(osdata.spriteSlots[i].spriteTexture);
	}
	int32_t size = osdata.spriteSlots.size();
	osdata.spriteSlots.clear();
	osdata.spriteSlots.resize(size);
}

void MophunOS::vSpriteSet(uint8_t slot, SPRITE* sprite, int16_t x, int16_t y)
{
	if (osdata.spriteSlots[slot].spriteTexture != nullptr)
	{
		SDL_DestroyTexture(osdata.spriteSlots[slot].spriteTexture);
	}
	osdata.spriteSlots[slot].spriteData = sprite;
	osdata.spriteSlots[slot].x = x;
	osdata.spriteSlots[slot].y = y;
	osdata.spriteSlots[slot].spriteTexture = SDL_CreateTexture(video->app.renderer,
		decodePixelFormat(sprite->format), SDL_TEXTUREACCESS_STATIC, sprite->width, sprite->height);

	SDL_UpdateTexture(osdata.spriteSlots[slot].spriteTexture, NULL, &sprite->data, 8);
	// FIXME set centerpoint??
}

void MophunOS::vUpdateSprite()
{
	for (const SpriteSlot spriteSlot : osdata.spriteSlots)
	{
		if (spriteSlot.spriteData == nullptr)
			continue;

		SDL_Rect dstrect = { spriteSlot.x, spriteSlot.y,  spriteSlot.spriteData->width, spriteSlot.spriteData->height };
		SDL_RenderCopy(video->app.renderer, spriteSlot.spriteTexture, NULL, &dstrect);
	}
}