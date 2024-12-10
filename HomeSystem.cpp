#include <map>
#include <functional>
#include "HomeSystem.h"
#include "HomeDevice.h"
#include "HomeSystemFunctions.h"
#include "Light.h"

HomeSystem::HomeSystem(string name, vector<HomeDevice*>* devices) : name(name), devices(devices) {}

void HomeSystem::menu() {
	
	// numbers in headers are so they are displayed in correct order
	map<string,string> menuDispaly = { 
		{"0header", "\n-----" + this->name + " Home Smart System Menu----- \n"}, 
		{"0intro", "Enter From the following:\n"}, 
		{"[device name]", ": Device Quick Display \n"}, 
		{"1", ": List devices \n"}, 
		{"2", ": Sort by name \n"}, 
		{"3", ": Sort by device type (by name as secondary order) \n"}, 
		{"4", "[device name] : Select device to interact with its full feature set \n"}, 
		{"5", ": Add device \n"}, 
		{"9", " : Exit \n"}, 
		{"inputPrompt", "Input: "}
	};
	

	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['2'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['4'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['5'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['['] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['9'] = []() { return false; };

	vector<string> ignoreHeader = { "0header", "0intro", "inputPrompt" };

	HomeSystemFunctions::menu(menuDispaly, menuFunctions, this, ignoreHeader);
}

HomeDevice* HomeSystem::findDevice(string name) {
	if (this->devices != nullptr) {
		vector<HomeDevice*>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ( (*it)->getName() == name) {
				return (*it);
			}
		}
	}
	return nullptr;
}

bool HomeSystem::isDevice(string name) {
	if (this->devices != nullptr) {
		vector<HomeDevice*>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ((*it)->getName() == name) {
				return true;
			}
		}
	}
	return false;
}

bool HomeSystem::addDevice() {

	map<string, string> display = this->typeNames;
	// numbers in headers are so they are displayed in correct order
	display["0intro"] = "Enter from the following numbers to create corisponding devices:"; // spell check
	display["inputPrompt"] = "Input: ";

	vector<string> ignoreHeader = { "0intro", "inputPrompt" };

	HomeSystemFunctions::menu(display, this->typeCreateFunctions, this,  ignoreHeader  );

	return true; 
}

bool HomeSystem::createLight() {
	// get params
	LightParams* params = nullptr;
	do {
		if (params != nullptr) { cout << "\n ### Invalid Input ### \n ";  }

		params = Light::getParams();
	} while (!params->paramsCorrect || this->isDevice(params->name));

	// Create new light object 
	Light* newLight = new Light(params->name, params->brightness);

	// Add object to devices vector 
	this->devices->push_back(newLight); 
	
	// cleaning up memory
	delete(params); 

	return true; 
	
}