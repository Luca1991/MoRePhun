#include <iostream>
#include "mophun_vm.h"
#include "system.h"


uint32_t vGetRandom()
{
	return rand() % (VRAND_MAX + 1);
}

bool vTerminateVMGP()
{
	std::cout << "vTerminateVMGP -> Program ended!" << std::endl;
	return false;
}
