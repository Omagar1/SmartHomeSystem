#include "TempHumidSensor.h"
TempHumidSensor::TempHumidSensor(string Name): HomeDevice(Name) {
	// set file paths - if i get a chance i wil create a strandard file path that can be chanaged
	

	this->humidDataFilePath = "C:/Users/josia/Documents/UNI Stuff/CS/24 25/Advanced Programing/SmartHomeSystem/RuntimeFiles/"+ this->getName() +"HumidData";
	this->tempDataFilePath = "C:/Users/josia/Documents/UNI Stuff/CS/24 25/Advanced Programing/SmartHomeSystem/RuntimeFiles/"+ this->getName() +"TempData";
	// --- genarate last data ---
	this->lastHumidReading = (rand() % 100) / 100;
	this->lastTempReading = rand() % 30; 
	// --- store last data --- 
	// getting current time
	time_t timeNow = std::time(nullptr); // Get current time std::string timeStr = timeToString
	string timeNowStr = HomeSystemFunctions::timeToStr(timeNow);
	// setting up dats strings
	vector<string> humidData = { timeNowStr, this->getLastHumidReading()};
	vector<string> tempData = { timeNowStr, this->getLastTempReading()};
	// storing data 
	HomeSystemFunctions::storeData(this->humidDataFilePath, humidData, ":"); 
	HomeSystemFunctions::storeData(this->tempDataFilePath, humidData, ":"); 

}


void TempHumidSensor::setCurrentHumidReading() {
	if (rand() % 2 == 0) { this->lastHumidReading += rand() % 5; }
	else { this->lastHumidReading -= rand() % 5; }
	// store in historic temp

}
void TempHumidSensor::setCurrentTempReading() {
	if (rand() % 2 == 0) { this->lastTempReading += rand() % 5; }
	else { this->lastTempReading -= rand() % 5; }
	// store in historic temp
}
