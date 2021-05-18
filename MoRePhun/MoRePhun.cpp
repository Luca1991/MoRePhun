#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "mophun_os.h"


int main()
{
	MophunOS* mophunOS = new MophunOS();
	if (!mophunOS->loadRom())
	{
		return 0;
	}
	mophunOS->emulate();

	delete mophunOS;

	std::cout << "Execution ended. Press enter to quit." << std::endl;
	std::getchar();
    return 0;
}

