#include <iostream>
#include <fstream>
#include "mophun_vm.h"
#include "vmgp_header.h"


bool MophunVM::loadRom(const std::string& romPath)
{
	std::ifstream romFile(romPath, std::ios::in | std::ios::binary | std::ios::ate);
	if (romFile.is_open())
	{
		uint32_t romSize = romFile.tellg();
		romFile.seekg(0, std::ios::beg);
		romFile.read(reinterpret_cast<char*>(memory.ram.data()), romSize);
		romFile.close();

		pRomHeader = reinterpret_cast<VMGPHeader*>(memory.ram.data());

		if (std::string(pRomHeader->magicNo) != "VMGP")
			return false;

		memory.codeSegStartAddr = sizeof(VMGPHeader);
		memory.dataSegStartAddr = memory.codeSegStartAddr + pRomHeader->codeSize;
		memory.bssSegStartAddr = memory.dataSegStartAddr + pRomHeader->dataSize;
		memory.resSegStartAddr = memory.bssSegStartAddr + pRomHeader->bssSize;
		memory.poolSegStartAddr = memory.resSegStartAddr + pRomHeader->resSize;
		memory.stringSegStartAddr = memory.poolSegStartAddr + (pRomHeader->poolSize * sizeof(PoolItem));
		memory.heapStartAddr = memory.stringSegStartAddr + pRomHeader->stringSize;
		memory.stackStartAddr = memory.ram.size() - pRomHeader->stackSize * 4;
		return true;
	}
	return false;
}