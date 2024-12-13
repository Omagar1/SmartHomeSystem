#include "Schedule.h"
Schedule::Schedule(string name, HomeSystem* homeSystem) : HomeDevice(name, homeSystem) {
	this->onFrom = nullptr;
	this->onUntil = nullptr;
}
Schedule::~Schedule() {

	if (this->onFrom != nullptr)
		delete onFrom;
	if(this->onUntil != nullptr)
		delete onUntil;
}


void Schedule::setSchedule(time_t start, time_t end) {
	// add error handerling?
	this->onFrom = new tm;
	this->onUntil = new tm;
	gmtime_s(this->onFrom, &start);
	gmtime_s(this->onUntil, &end);
}
void Schedule::setSchedule(time_t end) {
	time_t start = time(NULL);
	setSchedule(start, end);
	this->setOnVal(false); // as start is set to current time
}