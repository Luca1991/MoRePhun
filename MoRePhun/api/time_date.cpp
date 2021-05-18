#include "..\mophun_os.h"
#include <chrono>

uint32_t MophunOS::vGetTickCount()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - osdata.timer;
}