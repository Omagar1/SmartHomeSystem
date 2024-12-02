#pragma once
#include "HomeDevice.h"
class SleepDevice : public HomeDevice 
{
public:
	virtual void quickView();
	void setSleepTimer(time_t start, time_t  end); // change to in 30mine ect
	void setSleepTimer(time_t end);// change to in 30mine ect
private:
	struct tm* sleepFrom;
	struct tm* sleepUntil;
};

