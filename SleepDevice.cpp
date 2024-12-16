#include "SleepDevice.h"
#include "HomeSystem.h"

SleepDevice::SleepDevice(string name, HomeSystem* homeSystem, bool onVal) : HomeDevice(name, homeSystem, onVal) {}

bool SleepDevice::setSleepTimer() {
	// get input on time to sleep for
	int timeInMins = 1; // val as test for now

	// creates thread
	ThreadManager* threadManager = this->getHomeSystem()->getThreadManagerPtr(); 
	threadManager->createThread(&SleepDevice::sleepTimeAction, this, timeInMins);

	return true;
}
void SleepDevice::sleepTimeAction(int timeInMins) {
	this->setOnVal(false);
	std::this_thread::sleep_for(std::chrono::minutes(timeInMins)); 
	this->setOnVal(true);
	// test
	cout << "\n --- device Woke up ---  \n "; 
}





