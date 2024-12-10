#include <map>
#include <iostream>
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
	};
	

	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['2'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['4'] = HomeSystemFunctions::notDevelopedYet; 
	menuFunctions['5'] = bind(&HomeSystem::addDevice,this);
	menuFunctions['['] = HomeSystemFunctions::notDevelopedYet; 
	

	vector<string> ignoreHeader = { "0header", "0intro" };

	HomeSystemFunctions::menuDisplay<HomeSystem*>(menuDispaly, menuFunctions, this, ignoreHeader);
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
	display["0intro"] = "Enter from the following numbers to create corisponding devices: \n "; // spell check
	vector<string> ignoreHeader = { "0intro"};

	HomeSystemFunctions::menuDisplay<HomeSystem*>(display, this->typeCreateFunctions, this,  ignoreHeader );

	return true; 
}

bool HomeSystem::createLight() {
	// get params
	LightParams* params = nullptr;
	do {
		if (params != nullptr) { 
			cout << "\n ### Invalid Input ### \n ";  
			cout << params->errorMsg<< "\n";
		}

		params = Light::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "Name already exist please chose a diffrent name \n"; 
		}
	} while (!params->paramsCorrect);

	// Create new light object 
	Light* newLight = new Light(params->name, params->brightness);

	// Add object to devices vector 
	this->devices->push_back(newLight); 
	
	cout << "Device " << params->name << " has been added \n"; 
	// cleaning up memory
	delete(params); 

	return false; // as after creation we want to return to main menue 
	
}