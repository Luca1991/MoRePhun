#include "../mophun_os.h"
#include "../registers.h"


void MophunOS::vSpriteCollision()
{
	uint8_t slot = mophunVM->readReg(p0);
	uint8_t slotFrom = mophunVM->readReg(p1);
	uint8_t slotTo = mophunVM->readReg(p2);
	for (uint8_t i = slotFrom; i <= slotTo; i++)
	{
		
		if (!(osdata.spriteSlots[i].x > (osdata.spriteSlots[slot].x + osdata.spriteSlots[slot].spriteData->width) ||
			(osdata.spriteSlots[i].x + osdata.spriteSlots[i].spriteData->width) < osdata.spriteSlots[slot].x ||
			osdata.spriteSlots[i].y > (osdata.spriteSlots[slot].y + osdata.spriteSlots[slot].spriteData->height) ||
			(osdata.spriteSlots[i].y + osdata.spriteSlots[i].spriteData->height) < osdata.spriteSlots[slot].y))
		{
			mophunVM->writeReg(r0, i);
			return;
		}
	}
	mophunVM->writeReg(r0, -1);
}