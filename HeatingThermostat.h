#pragma once
#include "SleepDevice.h"
#include "Schedule.h"
struct HeatingThermostatParams : Params {
	int temprature; 
};

class HeatingThermostat : public Schedule
{
public:
	/*HeatingThermostat(string name, HomeSystem* homeSystem, int temprature, bool onVal = false);*/
	HeatingThermostat(string name, HomeSystem* homeSystem, int temprature, bool onVal = false);
	// --- getters --
	static HeatingThermostatParams* getParams();
	// --- quick action stuff ---
	inline string quickViewStr(string delimiter = " ") override;
	bool quickAction() override;
	inline string getTypeStr() const override; 
	// --- other stuff --- 
	void menu() override;
	void saveOnExit(string filePath) override;
private:
	int temprature;
};

string HeatingThermostat::quickViewStr(string delimiter) {
	return "Type: " + (string)typeid(*this).name() + delimiter + "Name: " + this->getName() + delimiter + "Status: " + this->getOnValStr() + delimiter + "temprature: " + to_string(this->temprature) + "C" + delimiter + "Quick Action: Heating Boost \n";
}
string HeatingThermostat::getTypeStr() const {
	return "Heating Thermostat";
}
