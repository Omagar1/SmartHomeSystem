#pragma once
#include <ctime>
#include <filesystem>
#include <time.h>
#include "HomeDevice.h"

// time code developed using:
//  https://www.w3schools.com/cpp/cpp_date.asp?form=MG0AV3
//  https://cplusplus.com/reference/ctime/strftime/
class TempHumidSensor : public HomeDevice
{
public:
	TempHumidSensor(string Name);
	// --- getters ---
	inline string getLastHumidReading(); 
	inline string getLastTempReading();
	// --- quick action stuff ---
	/*void quickView() override;
	string quickViewStr() override;
	bool quickAction() override;*/
	// --- Sensor Stuff --- 
	/*bool displayCurrentData();
	bool displayHistoricData(); */
	void setCurrentHumidReading();
	void setCurrentTempReading();
	

private:
	string humidDataFilePath;
	string tempDataFilePath;
	float lastHumidReading; // num between 0 and 1 to represent %
	float lastTempReading; // in Celcius
};

string TempHumidSensor::getLastHumidReading() {
	return to_string(this->lastHumidReading * 100) + "%"; 
}
string TempHumidSensor::getLastTempReading() {
	return to_string(this->lastTempReading ) + "C";
}