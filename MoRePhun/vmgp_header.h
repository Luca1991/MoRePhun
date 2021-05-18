#pragma once

#pragma pack(push, 1)
struct VMGPHeader
{
	char magicNo[4];
	uint16_t unknown1;
	uint16_t unknown2;
	uint16_t stackSize;
	uint8_t unknown3;
	uint8_t unknown4;
	uint32_t codeSize;
	uint32_t dataSize;
	uint32_t bssSize;
	uint32_t resSize;
	uint32_t unknown5;
	uint32_t poolSize;
	uint32_t stringSize;
};
#pragma pack(pop)