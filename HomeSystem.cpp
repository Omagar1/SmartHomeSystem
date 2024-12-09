#include <map>
#include <functional>
#include "HomeSystem.h"
#include "HomeDevice.h"
#include "HomeSystemFunctions.h"
#include "string"; 

HomeSystem::HomeSystem(string name, vector<HomeDevice>* devices, int numDevices) : name(name), devices(devices), numDevices(numDevices) {
	// test will put in better format 
	this->deviceTypes.display["1"] = "Light"; 
	this->deviceTypes.functions['1'] = { HomeSystem::createLight, NO_PARAMS};
}

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
	
	functionData test; 

	map<char, functionData> menuFunctions;
	menuFunctions['1'] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['2'] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['3'] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['4'] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['5'] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['['] = { HomeSystemFunctions::notDevelopedYet, NO_PARAMS };
	menuFunctions['9'] = { HomeSystemFunctions::exit, NO_PARAMS };

	vector<string> ignoreHeader = { "0header", "0intro", "inputPrompt" };

	HomeSystemFunctions::menu(menuDispaly, menuFunctions, ignoreHeader);
}

HomeDevice HomeSystem::findDevice(string name) {
	if (this->devices != nullptr) {
		vector<HomeDevice>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ((*it).getName() == name) {
				return (*it);
			}
		}
	}
	return HomeDevice();
}

bool HomeSystem::isDevice(string name) {
	if (this->devices != nullptr) {
		vector<HomeDevice>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ((*it).getName() == name) {
				return true;
			}
		}
	}
	return false;

}
void HomeSystem::addDevice() {
	
	HomeSystemFunctions::menu(deviceTypes.display, deviceTypes.functions);
}
