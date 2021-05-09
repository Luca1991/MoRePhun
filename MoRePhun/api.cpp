#include "mophun_vm.h"
#include "registers.h"
#include "system.h"
#include <sstream>


void MophunVM::apiHandler(const std::string &api)
{
	if (api == "DbgPrintf")
	{
		// FIXME: this should be changed with something safer
		if (registers[sp] != RAM_SIZE) { // THI IS WRONG!!
			mPrint(reinterpret_cast<char*>(std::addressof(memory.ram[registers[p0]])));
		}
	}
	else if (api == "vClearScreen")
	{
		printf("vClearScreen: %x\n", registers[p0]);
		uint8_t color[3];
		color[0] = (registers[p0] & 0x7C00) >> 7;
		color[1] = (registers[p0] & 0x3E0) >> 2;
		color[2] = (registers[p0] & 0x1f) << 3;
		SDL_SetRenderDrawColor(video->app.renderer, color[0], color[1], color[2], 255);
		SDL_RenderClear(video->app.renderer);
	}
	else if (api == "vFlipScreen")
	{
		printf("vFlipScreen %x\n", registers[p0]);
		SDL_RenderPresent(video->app.renderer);
	}
	else if (api == "vTerminateVMGP") {
		status = vTerminateVMGP();
	}
	else if (api == "vGetRandom") {
		registers[r0] = vGetRandom();
	}
	else {
		std::cout << "Unknown api: " << api.c_str() << std::endl;
	}
}

void MophunVM::mPrint(const std::string& str)
{
	std::stringstream ss;
	uint32_t stackTmpPnt = registers[sp];
	for (int i = 0; i < str.size();)
	{
		if (str[i]=='%')
		{
			i++;
			if (i >= str.size())
				break;
			switch(str[i])
			{
			case 's':
				ss << getStringFromMemory(stackTmpPnt);
				stackTmpPnt += sizeof(uint32_t);
				break;
			case '%':
				ss << '%';
				break;
			case 'd':
			case 'l':
				ss << *reinterpret_cast<int32_t*>(std::addressof(memory.ram[stackTmpPnt]));
				stackTmpPnt += sizeof(uint32_t);
				break;
			case 'f':
				ss << static_cast<float>(*reinterpret_cast<uint32_t*>(std::addressof(memory.ram[stackTmpPnt])));
				stackTmpPnt += sizeof(uint32_t);
				break;
			default:
				ss << "%" << str[i];
				break;
			}
			i++;
		} 
		else
		{
			ss << str[i];
			i++;
		}
	}

	std::cout << ss.str() << std::endl;

}

std::string MophunVM::getStringFromMemory(uint32_t addr)
{
	uint32_t ref = *reinterpret_cast<uint32_t*>(std::addressof(memory.ram[addr]));
	return reinterpret_cast<char*>(std::addressof(memory.ram[ref]));
}