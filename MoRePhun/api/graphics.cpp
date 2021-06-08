#include "../mophun_os.h"
#include <bitset>

void MophunOS::vClearScreen(int32_t color)
{
	uint8_t rgb[3];
	if (color & (1 << 31))
	{
		rgb[0] = (color & 0x7C00) >> 7;
		rgb[1] = (color & 0x3E0) >> 2;
		rgb[2] = (color & 0x1f) << 3;
	}
	else
	{
		rgb[0] = ((color >> 5) & 0x7) << 5;
		rgb[1] = ((color >> 2) & 0x7) << 5;
		rgb[2] = ((color >> 0) & 0x3) << 6;
	}
	SDL_SetRenderDrawColor(video->app.renderer, rgb[0], rgb[1], rgb[2], 255);
	SDL_RenderClear(video->app.renderer);
}


void MophunOS::vFlipScreen(uint32_t block)
{
	// FIXME TODO: check vblank
	SDL_RenderPresent(video->app.renderer);
}

void MophunOS::vSetForeColor(int32_t color)
{	
	if (color & (1 << 31))
	{
		osdata.currentFgColor[0] = (color & 0x7C00) >> 7;
		osdata.currentFgColor[1] = (color & 0x3E0) >> 2;
		osdata.currentFgColor[2] = (color & 0x1f) << 3;
	}
	else
	{
		osdata.currentFgColor[0] = ((color >> 5) & 0x7) << 5;
		osdata.currentFgColor[1] = ((color >> 2) & 0x7) << 5;
		osdata.currentFgColor[2] = ((color >> 0) & 0x3) << 6;
	}
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
	
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(std::addressof(sprite->data), sprite->width, sprite->height, 0, sprite->height, decodePixelFormat(sprite->format));
	SDL_SetColorKey(surface, true, SDL_MapRGB(surface->format, 0, 0, 0));

	osdata.spriteSlots[slot].spriteTexture = SDL_CreateTextureFromSurface(video->app.renderer, surface);

	if (surface != NULL)
		SDL_FreeSurface(surface);

	SDL_UpdateTexture(osdata.spriteSlots[slot].spriteTexture, NULL, NULL, sprite->height);
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

VMGPFONT* MophunOS::vSetActiveFont(VMGPFONT* pFont)
{
	osdata.previousFont = osdata.currentFont;
	osdata.currentFont = pFont;
	return osdata.previousFont;
}


void MophunOS::vPrint(int32_t mode, int32_t x, int32_t y, const char* str)
{
	if (mode != MODE_TRANS || osdata.currentFont->bpp != 1)
	{
		std::cout << "unsupported vPrint mode: " << mode << "or bpp: " << osdata.currentFont->bpp << std::endl;
		return;
	}

	uint8_t* fnt = mophunVM->getRamAddress(osdata.currentFont->fontdata);
	uint8_t* charTbl = mophunVM->getRamAddress(osdata.currentFont->chartbl);

	int bitsPerChar = osdata.currentFont->width * osdata.currentFont->height * osdata.currentFont->bpp;
	int bytesPerChar = bitsPerChar / CHAR_BIT;
	std::vector<char> pixels;
	pixels.resize(bitsPerChar);


	uint8_t origRGBA[4];
	SDL_GetRenderDrawColor(video->app.renderer,
		&origRGBA[0], &origRGBA[1], &origRGBA[2],
		&origRGBA[3]);
	
	SDL_SetRenderDrawColor(video->app.renderer, osdata.currentFgColor[0], osdata.currentFgColor[1], osdata.currentFgColor[2], 255);
	
	while (*str != '\0')
	{
		uint8_t currChar = charTbl[*str];
		int pixelIndex = 0;

		for (int i = 0; i < bytesPerChar; ++i)
		{
			uint8_t cur = fnt[currChar * bytesPerChar + i];
			int offset = i * CHAR_BIT;

			for (int bit = 0; bit < CHAR_BIT; ++bit)
			{
				pixels[offset] = cur & 1;
				++offset;
				cur >>= 1;
			}
		}
		
		for (int yy = y; yy < y+osdata.currentFont->height; yy++)
		{
			for (int xx = x; xx < x+osdata.currentFont->width; xx++)
			{
				if (pixels[pixelIndex])
					SDL_RenderDrawPoint(video->app.renderer, xx, yy);
				pixelIndex += 1;
			}
		}

		x += osdata.currentFont->width + 1;
		str += 1;
	}

	SDL_SetRenderDrawColor(video->app.renderer, origRGBA[0], origRGBA[1], origRGBA[2], origRGBA[3]);
}