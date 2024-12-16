#pragma once
#include<thread>
#include<chrono>
#include <mutex>
#include "HomeDevice.h"

class ThreadManager; 

class SleepDevice : public HomeDevice 
{
public:
	SleepDevice(string name, HomeSystem* homeSystem, bool onVal = false);
	bool setSleepTimer(); // use threads works untill program close
	void sleepTimeAction(int timeInMins, ThreadManager* threadManager);
private:
	
};

