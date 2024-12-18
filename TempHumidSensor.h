#pragma once
#include <ctime>
#include<thread>
#include<chrono>
#include <filesystem>
#include <time.h>
#include "HomeDevice.h"

// time code developed using:
//  https://www.w3schools.com/cpp/cpp_date.asp?form=MG0AV3
//  https://cplusplus.com/reference/ctime/strftime/

class ThreadManager;

class TempHumidSensor : public HomeDevice
{
public:
	TempHumidSensor(string Name, HomeSystem* homeSystem, bool onVal = false);
	TempHumidSensor(Params* params, HomeSystem* homeSystem);
	// --- getters ---
	inline string getLastHumidReadingStr(); 
	inline string getLastTempReadingStr();
	inline string getTypeStr() const override;
	// --- quick action stuff ---
	inline string quickViewStr(string delimiter = " ") override;
	bool quickAction() override;
	// --- Sensor Stuff --- 
	bool displayCurrentData();
	bool displayHistoricData(); 
	void setCurrentReading();
	void generateHistoricData(shared_ptr<ThreadManager> threadManager, int readEvery = 5); // readEvery: sets the time between readings in minutes
	// --- other funtcion Stuff --- 
	void menu() override;
	// dosent need a saveOnExit as it's stored functions are the same as HomeDevice


private:
	string FilePath;
	float lastHumidReading; // num between 0 and 1 to represent %
	float lastTempReading; // in Celcius
};


string TempHumidSensor::getLastHumidReadingStr() {
	return to_string(this->lastHumidReading * 100) + "%"; 
}
string TempHumidSensor::getLastTempReadingStr() {
	return to_string(this->lastTempReading ) + "C";
}
string TempHumidSensor::getTypeStr() const{
	return "Temperature and Humidity Sensor";
}
string TempHumidSensor::quickViewStr(string delimiter) {
	return "Type: " + this->getTypeStr() + delimiter +"Name: " + this->getName() + delimiter + "Humidity: "+ this->getLastHumidReadingStr() + delimiter + "tempriture: " + this->getLastTempReadingStr() + " \n";
}