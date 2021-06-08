#include "../mophun_os.h"
#include "../registers.h"
#include "system.h"


void MophunOS::apiHandler(const std::string &api)
{
	if (api == "DbgPrintf")
	{
		// FIXME: this should be changed with something safer
		if (mophunVM->readReg(sp) != RAM_SIZE) { // THI IS WRONG!!
			DbgPrintf(reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p0))));
		}
	}
	else if (api == "vClearScreen")
	{
		vClearScreen(static_cast<int32_t>(mophunVM->readReg(p0)));
	}
	else if (api == "vFlipScreen")
	{
		vFlipScreen(mophunVM->readReg(p0));
	}
	else if (api == "vSpriteInit")
	{
		mophunVM->writeReg(r0, vSpriteInit(mophunVM->readReg(p0)));
	}
	else if (api == "vSpriteClear")
	{
		vSpriteClear();
	}
	else if (api == "vSpriteSet")
	{
		vSpriteSet(mophunVM->readReg(p0), reinterpret_cast<SPRITE*>(mophunVM->getRamAddress(mophunVM->readReg(p1))),
			mophunVM->readReg(p2), mophunVM->readReg(p3));
	}
	else if (api == "vUpdateSprite")
	{
		vUpdateSprite();
	}
	else if (api == "vSetForeColor")
	{
		vSetForeColor(static_cast<int32_t>(mophunVM->readReg(p0)));
	}
	else if (api == "vGetButtonData")
	{
		mophunVM->writeReg(r0, vGetButtonData());
	}
	else if (api == "vTerminateVMGP") {
		vTerminateVMGP();
		status = false;
	}
	else if (api == "vGetRandom") {
		mophunVM->writeReg(r0, vGetRandom());
	}
	else if (api == "vGetTickCount")
	{
		mophunVM->writeReg(r0, vGetTickCount());
	}
	else if (api == "vStrCpy")
	{
		vStrCpy(reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p0))),
			reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p1))));
	}
	else if (api == "vSpriteCollision") {
		mophunVM->writeReg(r0, vSpriteCollision(mophunVM->readReg(p0), mophunVM->readReg(p1), mophunVM->readReg(p2)));
	}
	else if (api == "vSetActiveFont")
	{
		vSetActiveFont(reinterpret_cast<VMGPFONT*>(mophunVM->getRamAddress(mophunVM->readReg(p0))));
	}
	else if (api == "vPrint") {
		vPrint(static_cast<int32_t>(mophunVM->readReg(p0)),
			static_cast<int32_t>(mophunVM->readReg(p1)),
				static_cast<int32_t>(mophunVM->readReg(p2)),
			reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p3))));
	}
	else {
		std::cout << "Unknown api: " << api.c_str() << std::endl;
	}
}