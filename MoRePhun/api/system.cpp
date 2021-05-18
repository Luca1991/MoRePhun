#include <iostream>
#include "system.h"
#include "..\mophun_os.h"


uint32_t MophunOS::vGetRandom()
{
	return rand() % (VRAND_MAX + 1);
}

void MophunOS::vTerminateVMGP()
{
	std::cout << "vTerminateVMGP -> Program ended!" << std::endl;
}
