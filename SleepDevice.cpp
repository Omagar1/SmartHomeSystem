#include "SleepDevice.h"
#include "HomeSystem.h"

SleepDevice::SleepDevice(string name, HomeSystem* homeSystem, bool onVal) : HomeDevice(name, homeSystem, onVal) {}
SleepDevice::SleepDevice(){}
 
bool SleepDevice::setSleepTimer() {
	// get input on time to sleep for
	int timeInMins;
	bool exit = false; 
	do {
		string temp; 
		cout << "How Many Minutes do you want to sleep for: ";
		cin >> temp; 
		temp = HomeSystemFunctions::trim(temp);
		if (temp != "") {
			timeInMins = stoi(temp); 
			exit = true; 
		}
		else {
			cout << "\n ### Invalid Input ### \n";
		}
	} while (!exit);
	

	// creates thread
	ThreadManager* threadManager = this->getHomeSystem()->getThreadManagerPtr(); 
	threadManager->createThread(&SleepDevice::sleepTimeAction, this, timeInMins, threadManager);

	return true;
}
void SleepDevice::sleepTimeAction(int timeInMins, ThreadManager* threadManager) {
	this->setOnVal(false);
	int i = 0;
	// checks every 30 seconds if the stop flag its true; 
	while (!threadManager->getStopFlag().load() && i < timeInMins * 2) {
		std::this_thread::sleep_for(std::chrono::seconds(30));
		i++; 
	}
	
	this->setOnVal(true);
	// test
	mutex& mutex = threadManager->getMutex(); 
	mutex.lock(); 
	cout << "\n  Interupt --- " + this->getName() + " Woke Up ---  \n "; 
	mutex.unlock(); 
}





