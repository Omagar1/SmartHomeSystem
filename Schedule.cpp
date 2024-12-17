#include "Schedule.h"
#include "HomeSystem.h"

Schedule::Schedule(string name, HomeSystem* homeSystem, bool onVal) : HomeDevice(name, homeSystem, onVal) {
	this->onFrom = nullptr;
	this->onUntil = nullptr;
	this->userTurnedOn = false; 
	homeSystem->getThreadManagerPtr()->createThread(&Schedule::shouldBeOnThread, this); // creates a thread that checks if the device should be switched on
}
Schedule::~Schedule() {

	if (this->onFrom != nullptr)
		delete onFrom;
	if(this->onUntil != nullptr)
		delete onUntil;
}


void Schedule::setSchedule(time_t start, time_t end) {
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

bool Schedule::shouldBeOn() {
	// checks if 
	time_t timeNow = time(NULL);
	if(this->userTurnedOn){
		return true; 
	}
	else if (mktime(this->onFrom) < timeNow && mktime(this->onUntil) > timeNow) { // ie is within the two times
		this->setOnVal(true);
		return true; 
	}
	else {
		this->setOnVal(false);
		return false; 
	}
}
void Schedule::shouldBeOnThread() {
	while (!this->getHomeSystem()->getThreadManagerPtr()->getStopFlag().load()) {
		this->shouldBeOn(); 
		this_thread::sleep_for(chrono::seconds(10));
	}
}