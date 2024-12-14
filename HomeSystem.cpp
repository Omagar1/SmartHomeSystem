#include <map>
#include <iostream>
#include <functional>
#include "HomeSystem.h"

HomeSystem::HomeSystem(string name, string filePath,  vector<shared_ptr<HomeDevice>>* devices) : name(name), filePath(filePath+"/"+name+"HSS"), devices(devices) {}

HomeSystem::~HomeSystem() {

}

void HomeSystem::menu() {

	// numbers in headers are so they are displayed in correct order
	map<string, string> menuDispaly = {
		{"0header", "\n-----" + this->name + " Home Smart System Menu----- \n"},
		{"0intro", "Enter From the following:\n"},
		{"[device name]", ": Device Quick Display \n"},
		{"1", ": List devices \n"},
		{"2", ": Sort by name \n"},
		{"3", ": Sort by device type (by name as secondary order) \n"},
		{"4", ": Select device to interact with its full feature set \n"},
		{"5", ": Add device \n"},
		{"6", ": Rename Home System \n"},
	};


	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = [this]() {return this->listDevices(); };
	menuFunctions['2'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['4'] = [this]() {return this->selectDevice(); };
	menuFunctions['5'] = bind(&HomeSystem::addDevice, this);
	menuFunctions['6'] = [this]() {return this->rename();  };
	menuFunctions['['] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['Q'] = [this]() {return this->saveOnExit();  }; // 'overiding' default menu Q function
	

	vector<string> ignoreHeader = { "0header", "0intro" };

	HomeSystemFunctions::menuDisplay<HomeSystem*>(menuDispaly, menuFunctions, this, ignoreHeader);
}

shared_ptr<HomeDevice> HomeSystem::findDevice(string name) {
	if (this->devices != nullptr) {
		vector<shared_ptr<HomeDevice>>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ( (*it)->getName() == name) {
				return (*it);
			}
			++it; 
		}
	}
	return nullptr;
}

bool HomeSystem::isDevice(string name) {
	if (this->devices != nullptr) {
		vector<shared_ptr<HomeDevice>>::iterator it(this->devices[0].begin());
		while (it != this->devices[0].end()) {
			if ((*it)->getName() == name) {
				return true;
			}
			++it; 
		}
	}
	return false;
}

bool HomeSystem::addDevice() {

	map<string, string> display = this->typeNames;
	// numbers in headers are so they are displayed in correct order
	display["0intro"] = "Enter from the following numbers to create corisponding devices: \n"; // spell check
	vector<string> ignore = { "0intro"};

	HomeSystemFunctions::menuDisplay<HomeSystem*>(display, this->typeCreateFunctions, this,  ignore);

	return true; 
}
bool HomeSystem::selectDevice() {
	int devicesLength = this->devices->size();
	if (devicesLength != 0) {
		// get name of device they want to interact with 
		string input;
		cout << "\nDeveice Name: ";
		cin >> input;
		// validation
		input = HomeSystemFunctions::trim(input);

		// find device
		shared_ptr<HomeDevice>  device = findDevice(input);
		if (device == nullptr) {
			cout << "\n### Device with name" << input << " not found! ###\n";
		}
		else {
			// dipslay device menu 
			device->menu();
		}
	}
	return true; // this is about if to exit the menu system not the outcome of the function
}


bool HomeSystem::listDevices(int startIndex) {
	int devicesLength = this->devices->size();
	if (devicesLength != 0) {

		// creating menue system
		map<string, string> menuDispaly;
		map<char, function<bool()>> menuFunctions;
		vector<string> ignore = { "0intro", "0Page" };
		

		// numbers in headers are so they are displayed in correct order
		menuDispaly["0intro"] = "Select from the following to do that device's Quick Action: \n";
		if (devicesLength % 10 > 1) {
			menuDispaly["0Page"] = "Page " + to_string(devicesLength % (startIndex + 1) + 1) + " of " + to_string(devicesLength % 10) + " \n";
		}
		int i;
		for (i = startIndex; i < devicesLength && i < (startIndex + 10); i++) {
			// geting Devices
			string indexStr = to_string(i + 1 - startIndex); // +1 so it's 1 to 9 and not 0 to 8; - startIndex so its consitently 1 to 9 and not 9 - 17 ect for diffent startIndex other than 0
			char indexChar = indexStr[0];
			const std::type_info& typeInfo = typeid((*(*devices)[i]));
			shared_ptr<HomeDevice>  device = (*devices)[i];

			// setting up display 
			menuDispaly[indexStr] = ": " + device->quickViewStr() + "\n";
			menuFunctions[indexChar] = [device]() {return device->quickAction(); };
		}
		// adding next page function
		if (i < devicesLength) {
			menuDispaly["N"] = ": Next Page \n";
			menuFunctions['N'] = [this, i]() {return this->listDevices(i); }; // using i here as i will inciment then exit the for loop so will be thge next index for display
		}
		// adding previous page function
		else if (i > 9) {
			menuDispaly["P"] = ": Previous Page \n" ;
			int previousStartIndex = i - 10; // as im goingfrom 0 to 10 (not 9 as i will inciment then exit the for loop) 
			menuFunctions['P'] = [this, previousStartIndex]() {return this->listDevices(previousStartIndex); };
		}

		HomeSystemFunctions::menuDisplay<HomeSystem*>(menuDispaly, menuFunctions, this, ignore);
	}
	else {
		cout << "\n --- No Devices to Dsiaply --- \n"; 
	}
	return true; 
}


bool HomeSystem::rename() { // for home system
	string input;
	cout << "Rename " + this->name + " \n";
	cout << "Enter new name or  Q to cancel \n";
	cout << "Input: ";
	cin >> input;
	input = HomeSystemFunctions::trim(input);
	if (input == "Q") {
		return true; // the return val is to do with the exiting the menue system that this function might be called in not the result of the function
	}
	else if (input == "") {
		cout << "\n ### Name Cannot Be Blank! #### \n ";
		return rename();
	}
	else {
		this->name = input;
		cout << "\n Name Set Reset To see name change \n";
		return true;
	}
}


// --- Device Creation functions --- 


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
			params->errorMsg = "\n ### Name Already Taken ####  \n"; 
		}
	} while (!params->paramsCorrect);

	// Create new light object 
	shared_ptr<Light> newLight = make_shared<Light>(params->name, this, params->brightness);

	// Add object to devices vector 
	this->devices->push_back(newLight); 
	
	cout << "Light " << params->name << " has been added \n"; 
	// cleaning up memory
	delete(params); 

	return false; // as after creation we want to return to main menu 
	
}
bool HomeSystem::createTempHumidSensor() {
	// get params
	Params* params = nullptr;
	do {
		if (params != nullptr) { 
			cout << "\n ### Invalid Input ### \n ";  
			cout << params->errorMsg<< "\n";
		}

		params = TempHumidSensor::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "\n ### Name Already Taken ####  \n"; 
		}
	} while (!params->paramsCorrect);

	// Create new TempHumidSensor object 
	shared_ptr<TempHumidSensor> newTempHumidSensor = make_shared<TempHumidSensor>(params->name, this);

	// Add object to devices vector 
	this->devices->push_back(newTempHumidSensor);
	
	cout << "Temperature and Humidity Sensor:  " << params->name << " has been added \n"; 
	// cleaning up memory
	delete(params); 

	return false; // as after creation we want to return to main menu 
	
}

bool HomeSystem::saveOnExit() {
	HomeSystemFunctions::storeData(this->filePath, "", true); // will overwrite exiting file so only most upto date version is stored
	// stroring devices
	for (shared_ptr<HomeDevice> device : *(this->devices)) {
		device->saveOnExit(filePath);
	}
	return false;

}
bool HomeSystem::load() {
	// open file
	vector<string> deviceDataVector = HomeSystemFunctions::loadData(filePath);// each enty is a string of a devices's data
	for (string deviceData : deviceDataVector) {
		
	}
	// ceated devicess
	return true;
}

