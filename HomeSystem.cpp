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
	// --- menu setup ---  
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
	vector<string> dontDisplay = { "0header", "0intro", "inputPrompt" };

	

	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['2'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['4'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['5'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['['] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['9'] = HomeSystemFunctions::exit;


	// --- menue exicution ---
	bool exit = false;
	do {
		string input;

		HomeSystemFunctions::displayOptions(menuDispaly, dontDisplay);

		cin >> input;

		// runs related funcution if input is a key of functions
		if (menufunctions.find(input[0]) != menufunctions.end()) {

			char key = input[0];
			if (menufunctions[key].type == NO_PARAMS) {
				exit = !menufunctions[key].function.funcWithoutParams();
			}
			else {
				vector<string>* parameters = { CommonFunctions::split(input.erase(0,1), ',') };
				exit = !menufunctions[key].function.funcWithParams(parameters);

			}
		}
		else {
			cout << "\n ### Invalid input Try again: \n";
		}
	} while (!exit);
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
	// add relivent menu system
	
}

Light* HomeSystem::createLight() {
	/*LightParams params = Light::askForParams();*/
	Light* newLight = new Light(params.name, params.brightness);
	return newLight;
}
