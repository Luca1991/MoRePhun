#pragma once
#include <cstdint>
#include "../video.h"

inline Uint32 decodePixelFormat(uint8_t format) { 
	switch (format)
	{
	case 0x7:
		return SDL_PIXELFORMAT_RGB332;
	default:
		std::cout << "Unknown sprite pixel format: " << format << std::endl;
		return SDL_PIXELFORMAT_UNKNOWN;

	}
}

#pragma pack(push, 1)
struct SPRITE {
	uint8_t palindex;
	uint8_t format;
	int16_t centerx;  
	int16_t centery;
	uint16_t width;
	uint16_t height;
	uint8_t* data;
};
#pragma pack(pop)

struct SpriteSlot {
	SPRITE* spriteData;
	SDL_Texture* spriteTexture;
	int32_t x;
	int32_t y;
};