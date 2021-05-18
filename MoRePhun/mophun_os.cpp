#include "mophun_os.h"
#include <chrono>

MophunOS::MophunOS()
{
	status = true;
	osdata.timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	mophunVM->setApiCallback([this](const std::string& api) { return apiHandler(api); });
}


MophunOS::~MophunOS()
{
	delete mophunVM;
	delete video;
}

bool MophunOS::loadRom()
{
	if (mophunVM->loadRom("load.mpn"))
	{
		std::cout << "Rom loaded!" << std::endl;
	}
	else {
		std::cout << "Rom not found or invalid magic no." << std::endl;
		std::getchar();
		return false;
	}
	return true;
}

void MophunOS::emulate()
{
	while (status)
	{
		mophunVM->emulate();
	}
}