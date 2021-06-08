#include "../mophun_os.h"


int16_t MophunOS::vSpriteCollision(uint8_t slot, uint8_t slotfrom, uint8_t slotto)
{
	for (uint8_t i = slotfrom; i <= slotto; i++)
	{
		
		if (!(osdata.spriteSlots[i].x > (osdata.spriteSlots[slot].x + osdata.spriteSlots[slot].spriteData->width) ||
			(osdata.spriteSlots[i].x + osdata.spriteSlots[i].spriteData->width) < osdata.spriteSlots[slot].x ||
			osdata.spriteSlots[i].y > (osdata.spriteSlots[slot].y + osdata.spriteSlots[slot].spriteData->height) ||
			(osdata.spriteSlots[i].y + osdata.spriteSlots[i].spriteData->height) < osdata.spriteSlots[slot].y))
			return i;
	}
	return -1;
}