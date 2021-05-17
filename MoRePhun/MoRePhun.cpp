#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "mophun_vm.h"


int main()
{
	MophunVM* mophunVM = new MophunVM();
	if (mophunVM->loadRom("load.mpn"))
	{
		std::cout << "Rom loaded!" << std::endl;
	}
	else {
		std::cout << "Rom not found or invalid magic no." << std::endl;
		std::getchar();
		return 0;
	}

	while (mophunVM->status)
	{
		mophunVM->emulate();		
	}
	
	delete mophunVM;

	std::cout << "Execution ended. Press enter to quit." << std::endl;
	std::getchar();
    return 0;
}

