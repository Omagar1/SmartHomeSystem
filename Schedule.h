#pragma once
#include "HomeDevice.h"
class Schedule : public HomeDevice
{
public: // virtual class hence no quick actions
	Schedule(string name, HomeSystem* homeSystem, bool onVal = false) ;
	~Schedule();
	// --- sleep Functions ---
	void setSchedule(time_t start, time_t  end); // change to in 30mine ect
	void setSchedule(time_t end);// change to in 30mine ect
private:
	struct tm* onFrom;
	struct tm* onUntil;

};

