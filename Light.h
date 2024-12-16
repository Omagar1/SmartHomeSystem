#pragma once
#include <string>
#include "Params.h"
#include "HomeSystemFunctions.h"
#include "SleepDevice.h"

struct LightParams : Params {
	float brightness; 
};

class Light : public SleepDevice
{
public: 
	Light(string name, HomeSystem* homeSystem, float brightness, bool onVal = false);
	// --- getters --
	static LightParams* getParams();
	// --- quick action stuff ---
	inline string quickViewStr(string delimiter = " ") override;
	bool quickAction() override;
	// --- other stuff --- 
	void menu() override;
	void saveOnExit(string filePath) override;
	/*virtual void load();*/
	

private:
	float brightness; // percentage stored as value between 0 and 1.00
};

string Light::quickViewStr(string delimiter) {
	return "Type: " + (string)typeid(*this).name() + delimiter + "Name: " + this->getName() + delimiter + "Status: " + this->getOnValStr() + delimiter + "Brightness: "+ to_string(this->brightness*100)+"%" + delimiter + "Quick Action: Switch " + this->getOpositeOnValStr() + " \n";
}