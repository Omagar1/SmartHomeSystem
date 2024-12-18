#pragma once
#include "SleepDevice.h"
#include "Schedule.h"

struct RadiatorParams : Params {
	int temprature;
};


class Radiator : public SleepDevice, public Schedule
{
public:
	/*HeatingThermostat(string name, HomeSystem* homeSystem, int temprature, bool onVal = false);*/
	Radiator(string name, HomeSystem* homeSystem, int temprature, bool onVal = false);
	Radiator(RadiatorParams* params, HomeSystem* homeSystem);
	
	// --- getters --
	static RadiatorParams* getParams();
	// --- quick action stuff ---
	inline string quickViewStr(string delimiter = " ") override;
	// --- other stuff --- 
	void menu() override;
	void saveOnExit(string filePath) override;
private:
	int temprature;
};

string Radiator::quickViewStr(string delimiter) {
	return "Type: " +  getTypeStr() + delimiter + "Name: " + this->getName() + delimiter + "Status: " + this->getOnValStr() + delimiter + "temprature: " + to_string(this->temprature) + "C" + delimiter + "Quick Action: Heating Boost \n";
}
