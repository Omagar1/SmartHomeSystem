#include "HomeDevice.h"
HomeDevice::HomeDevice(string name): name(name) {}



Params* HomeDevice::getParams() {
	Params* params = new Params();
	params->paramsCorrect = true;
	string temp;
	cout << "\nDevice name: ";
	cin >> temp;
	if (temp != "") {
		params->name = temp;
	}
	else {
		params->paramsCorrect = false;
		params->errorMsg = "Name cannot be blank!";
	}
	return params;
}

// --- quick action stuff ---
void HomeDevice::quickView() { // change
	string output[] = {
		this->name + ((this->on) ? "On" : "Off") + " \n",
	};
	HomeSystemFunctions::displayOptions(output); 
}
string  HomeDevice::quickViewStr() {
	return "Type: "+ (string)typeid(*this).name() + " Name: " + this->name + " Status: " + ((this->on) ? "On" : "Off") + " Quick Action: Switch " + ((!this->on) ? "On" : "Off") + " \n";
}

// --- rest of functions --- 
bool HomeDevice::quickAction() {
	this->switchOnVal(); 
	return true; 
}

void HomeDevice::menu() {
	// numbers in headers are so they are displayed in correct order
	map<string, string> menuDispaly = {
		{"0header", "\n-----" + this->name + "Home Device Menu----- \n"},
		{"0intro", "Enter From the following:\n"},
		{"1", ": rename \n"},
		{"2", ": Sort by name \n"},
		{"3", ": Sort by device type (by name as secondary order) \n"},
		{"4", "[device name] : Select device to interact with its full feature set \n"},
		{"6", ": Rename device  \n"},
		{"D", ": Delete \n"},
	};


	map<char, function<bool()>> menuFunctions;
	/*menuFunctions['1'] = [this]() {return this->listDevices(); };
	menuFunctions['2'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['4'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['5'] = bind(&HomeSystem::addDevice, this);
	menuFunctions['6'] = [this]() {return this->rename();  };
	menuFunctions['['] = HomeSystemFunctions::notDevelopedYet;*/


	vector<string> ignoreHeader = { "0header", "0intro" };

	HomeSystemFunctions::menuDisplay<HomeDevice*>(menuDispaly, menuFunctions, this, ignoreHeader);
}
void HomeDevice::load() {
	// get data from file
}






