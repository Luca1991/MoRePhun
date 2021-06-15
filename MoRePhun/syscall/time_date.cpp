#include "../mophun_os.h"
#include "../registers.h"
#include <chrono>

void MophunOS::vGetTickCount()
{
	 uint32_t cnt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - osdata.timer;
	 mophunVM->writeReg(r0, cnt);
}