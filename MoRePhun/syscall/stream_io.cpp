#include "../mophun_os.h"
#include "../registers.h"
#include "stream_io.h"


void MophunOS::vStreamOpen()
{
	char* name = reinterpret_cast<char*>(mophunVM->getRamAddress(mophunVM->readReg(p0)));
	int32_t mode = static_cast<int32_t>(mophunVM->readReg(p1));
	char fMode[4] = { 0 };
	int modeIndex = 0;

	if (mode & STREAM_READ)
	{
		fMode[modeIndex] = 'r';
		modeIndex += 1;
	}
	else if (mode & STREAM_WRITE)
	{
		fMode[modeIndex] = 'w';
		modeIndex += 1;
	}

	if (mode & STREAM_BINARY)
	{
		fMode[modeIndex] = 'b';
		modeIndex += 1;
	}

	FILE* fd = fopen(name, fMode);
	StreamSlot streamSlot;
	streamSlot.fd = fd;
	osdata.streamSlots[osdata.streamCounter] = streamSlot;
	mophunVM->writeReg(r0, osdata.streamCounter);
	osdata.streamCounter += 1;
}

void MophunOS::vStreamClose()
{
	uint32_t slot = static_cast<uint32_t>(mophunVM->readReg(p0));
	FILE* fd = osdata.streamSlots[slot].fd;
	fclose(fd);
	osdata.streamSlots.erase(slot);

}

void MophunOS::vStreamRead()
{
	FILE* fd = osdata.streamSlots[static_cast<uint32_t>(mophunVM->readReg(p0))].fd;
	void* buff = static_cast<void*>(mophunVM->getRamAddress(mophunVM->readReg(p1)));
	int32_t count = static_cast<int32_t>(mophunVM->readReg(p2));
	int read = fread(buff, 1, count, fd);
	mophunVM->writeReg(r0, read);
}

void MophunOS::vStreamWrite()
{
	FILE* fd = osdata.streamSlots[static_cast<uint32_t>(mophunVM->readReg(p0))].fd;
	void* buff = static_cast<void*>(mophunVM->getRamAddress(mophunVM->readReg(p1)));
	int32_t count = static_cast<int32_t>(mophunVM->readReg(p2));
	int32_t written = fwrite(buff, 1, count, fd);
	mophunVM->writeReg(r0, written);
}