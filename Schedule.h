#pragma once
#include "HomeDevice.h"
class Schedule : public virtual HomeDevice
{
public: // virtual class hence no quick actions
	Schedule(string name, HomeSystem* homeSystem, bool onVal = false) ;
	
	~Schedule();
	// --- Schedule Functions ---
	void setSchedule(time_t start, time_t  end);
	void setSchedule(time_t end);
	bool shouldBeOn(); 
	void shouldBeOnThread();
protected:
	Schedule();
private:
	bool userTurnedOn; 
	struct tm* onFrom;
	struct tm* onUntil;

};

