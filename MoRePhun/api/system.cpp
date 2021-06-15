#include <iostream>
#include "system.h"
#include "../mophun_os.h"
#include "../registers.h"


void MophunOS::vGetRandom()
{
	uint32_t rnd = rand() % (VRAND_MAX + 1);
	mophunVM->writeReg(r0, rnd);
}

void MophunOS::vTerminateVMGP(void)
{
	std::cout << "vTerminateVMGP -> Program ended!" << std::endl;
	status = false;
}
