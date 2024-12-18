#include <map>
#include <iostream>
#include <functional>
#include "HomeSystem.h"

HomeSystem::HomeSystem(string name, string filePath, bool loadFromFile) : name(name), filePath(filePath+"/"+name+"HSS") {

	this->devices = vector<shared_ptr<HomeDevice>>();
	this->threadManager = new ThreadManager();
	if (loadFromFile)
		load(); 
}

HomeSystem::~HomeSystem() {
	delete(this->threadManager);
	this->threadManager = nullptr; 
}

void HomeSystem::menu() {
	// initailising
	map<string, string> menuDispaly;
	map<char, function<bool()>> menuFunctions;
	vector<string> ignoreHeader;
	shared_ptr<string> input = make_shared<string>(); // to be defined in menuDisplay()
	do {
		// numbers in headers are so they are displayed in correct order
		menuDispaly = {
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

		ignoreHeader = { "0header", "0intro" };
		
		
		menuFunctions['1'] = [this]() {return this->listDevices(); };
		menuFunctions['2'] = [this]() {return this->listDevices(0,NAME); };
		menuFunctions['3'] = [this]() {return this->listDevices(0,TYPE); };
		menuFunctions['4'] = [this]() {return this->selectDevice(); };
		menuFunctions['5'] = bind(&HomeSystem::addDevice, this);
		menuFunctions['6'] = [this]() {return this->rename();  };
		menuFunctions['['] = [this, input]() {
			shared_ptr<HomeDevice> device = this->findDevice(HomeSystemFunctions::trim(*input, '[', ']')); 
			if (device == nullptr) {
				cout << "\n ### Requested device Dosent exist ### \n "; 
			}
			else {
				device->quickView();
			}
			
			return true; 
		};
		menuFunctions['Q'] = [this]() {return this->saveOnExit();  }; // 'overiding' default menu Q function

	} while (HomeSystemFunctions::menuDisplay(menuDispaly, menuFunctions, this->threadManager, ignoreHeader, input)); 
}

shared_ptr<HomeDevice> HomeSystem::findDevice(string name) {
	if (this->devices.size() != 0) {
		vector<shared_ptr<HomeDevice>>::iterator it(this->devices.begin());
		while (it != this->devices.end()) {
			if ( (*it)->getName() == name) {
				return (*it);
			}
			++it; 
		}
	}
	return nullptr;
}

bool HomeSystem::isDevice(string name) {
	if (this->devices.size() != 0) {
		vector<shared_ptr<HomeDevice>>::iterator it(this->devices.begin());
		while (it != this->devices.end()) {
			if ((*it)->getName() == name) {
				return true;
			}
			++it; 
		}
	}
	return false;
}

bool HomeSystem::addDevice() {
	map<string, string> display;
	vector<string> ignore;
	do {
		display = this->typeNames;
		// numbers in headers are so they are displayed in correct order
		display["0intro"] = "Enter from the following numbers to create corisponding devices: \n"; // spell check
		ignore = { "0intro" };

	} while(HomeSystemFunctions::menuDisplay(display, this->typeCreateFunctions, this->threadManager, ignore));

	return true; 
}
bool HomeSystem::selectDevice() {
	int devicesLength = this->devices.size();
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


bool HomeSystem::listDevices(int startIndex, SortByType sortBy){
	// sorting
	if (sortBy == NAME) {
		sort(this->devices.begin(), this->devices.end(), [](const shared_ptr<HomeDevice> &lhs, const shared_ptr<HomeDevice> &rhs) { 
			return *lhs < *rhs; 
			}); 
	}
	else if (sortBy == TYPE){
		sort(this->devices.begin(), this->devices.end(), HomeDevice::compareByType);
	}

	int devicesLength = this->devices.size();
	if (devicesLength > 0) {

		// creating menue system
		map<string, string> menuDispaly;
		map<char, function<bool()>> menuFunctions;
		vector<string> ignore = { "0intro", "0Page" };
		
		do {
			// numbers in headers are so they are displayed in correct order
			menuDispaly["0intro"] = "Select from the following to do that device's Quick Action: \n";
			if (devicesLength % 9 > 1) {
				menuDispaly["0Page"] = "Page " + to_string(devicesLength % (startIndex + 1) + 1) + " of " + to_string(devicesLength % 9) + " \n";
			}
			int i;
			for (i = startIndex; i < devicesLength && i < (startIndex + 9); i++) {
				// geting Devices
				string indexStr = to_string(i + 1 - startIndex); // +1 so it's 1 to 9 and not 0 to 8; - startIndex so its consitently 1 to 9 and not 9 - 17 ect for diffent startIndex other than 0
				char indexChar = indexStr[0];
				const std::type_info& typeInfo = typeid((*(devices)[i]));
				shared_ptr<HomeDevice>  device = (devices)[i];

				// setting up display 
				menuDispaly[indexStr] = ": " + device->quickViewStr() + "\n";
				menuFunctions[indexChar] = [device]() {return device->quickAction(); };
			}
			// adding next page function
			if (i < devicesLength) {
				menuDispaly["N"] = ": Next Page \n";
				menuFunctions['N'] = [this, i]() { this->listDevices(i); return false; }; // using i here as i will inciment then exit the for loop so will be thge next index for display | false is returned so we dont get in a recurtion chain
			}
			// adding previous page function
			else if (i > 9 && devicesLength > 9) {
				menuDispaly["P"] = ": Previous Page \n";
				int previousStartIndex = i - 10; // as im goingfrom 0 to 10 (not 9 as i will inciment then exit the for loop) 
				menuFunctions['P'] = [this, previousStartIndex]() {this->listDevices(previousStartIndex); return false; }; // false is returned so we dont get in a recurtion chain
			}

		} while (HomeSystemFunctions::menuDisplay(menuDispaly, menuFunctions, this->threadManager, ignore));
	}
	else {
		cout << "\n --- No Devices to Dsiaply --- \n"; 
	}
	return true; 
}


bool HomeSystem::rename() { // for home system
	string input;
	this->threadManager->getMutex().lock(); // to prevent confusing interupts 
	cout << "Rename " + this->name + " \n";
	cout << "Enter new name or  Q to cancel \n";
	cout << "Input: ";
	cin >> input;
	input = HomeSystemFunctions::trim(input);
	if (input == "Q") {
		this->threadManager->getMutex().unlock();
		return true; // the return val is to do with the exiting the menue system that this function might be called in not the result of the function
	}
	else if (input == "") {
		cout << "\n ### Name Cannot Be Blank! #### \n ";
		this->threadManager->getMutex().unlock();
		return rename();
	}
	else {
		this->name = input;
		cout << "\n Name Set \n";
		this->threadManager->getMutex().unlock();
		return true;
	}
}


// --- Device Creation functions --- 


bool HomeSystem::createLight() {
	// get params
	LightParams* params = nullptr;
	do {
		this->threadManager->getMutex().lock(); // to prevent confusing interupts 
		if (params != nullptr) { 
			cout << "\n ### Invalid Input ### \n ";  
			cout << params->errorMsg<< "\n";
		}

		params = Light::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "\n ### Name Already Taken ####  \n"; 
		}
		this->threadManager->getMutex().unlock();
	} while (!params->paramsCorrect);

	// Create new light object 
	shared_ptr<Light> newLight = make_shared<Light>(params->name, this, params->brightness);

	// Add object to devices vector 
	this->devices.push_back(newLight); 
	
	cout << *newLight << " has been added \n";
	// cleaning up memory
	delete(params); 

	return false; // as after creation we want to return to main menu 
	
}
bool HomeSystem::createTempHumidSensor() {
	// get params
	Params* params = nullptr;
	do {
		this->threadManager->getMutex().lock(); // to prevent confusing interupts 
		if (params != nullptr) { 
			cout << "\n ### Invalid Input ### \n ";  
			cout << params->errorMsg<< "\n";
		}

		params = TempHumidSensor::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "\n ### Name Already Taken ####  \n"; 
		}
		this->threadManager->getMutex().unlock();
	} while (!params->paramsCorrect);

	// Create new TempHumidSensor object 
	shared_ptr<TempHumidSensor> newTempHumidSensor = make_shared<TempHumidSensor>(params->name, this);

	// Add object to devices vector 
	this->devices.push_back(newTempHumidSensor);
	
	cout << *newTempHumidSensor << " has been added \n";
	// cleaning up memory
	delete(params); 

	return false; // as after creation we want to return to main menu 
	
}

bool HomeSystem::createHeatingThermostat() {
	// get params
	HeatingThermostatParams* params = nullptr;
	do {
		this->threadManager->getMutex().lock(); // to prevent confusing interupts 
		if (params != nullptr) {
			cout << "\n ### Invalid Input ### \n ";
			cout << params->errorMsg << "\n";
		}

		params = HeatingThermostat::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "\n ### Name Already Taken ####  \n";
		}
		this->threadManager->getMutex().unlock();
	} while (!params->paramsCorrect);

	// Create new HeatingThermostat object 
	shared_ptr<HeatingThermostat> newHeatingThermostat = make_shared<HeatingThermostat>(params->name, this, params->temprature);

	// Add object to devices vector 
	this->devices.push_back(newHeatingThermostat);

	cout << *newHeatingThermostat << " has been added \n";
	// cleaning up memory
	delete(params);

	return false; // as after creation we want to return to main menu 

}

bool HomeSystem::saveOnExit() {
	HomeSystemFunctions::storeData(this->filePath, "", true); // will overwrite exiting file so only most upto date version is stored
	// stroring devices
	for (shared_ptr<HomeDevice> device : (this->devices)) {
		device->saveOnExit(filePath);
	}
	return false;

}
bool HomeSystem::load() {
	// open file
	vector<string> devicesVector = HomeSystemFunctions::loadData(filePath);// each enty is a string of a devices's data
	for (string deviceData : devicesVector) {
		if (deviceData != "") {
			vector<string> deviceDataVector = HomeSystemFunctions::split(deviceData);
			if (deviceDataVector[0] == "Light") {// will be in format:  type,name,onVal,brightness
				// format params
				bool onVal = stoi(deviceDataVector[2]);
				float brightness = stof(deviceDataVector[3]);
				// create object
				shared_ptr<Light> device = make_shared<Light>(deviceDataVector[1], this, brightness, onVal);
				// add to devices vector
				this->devices.push_back(device);
			}
			else if (deviceDataVector[0] == "Temperature and Humidity Sensor") {// will be in format:  type,name,onVal
				// format params
				bool onVal = stoi(deviceDataVector[2]);
				// create object
				shared_ptr<TempHumidSensor> device = make_shared<TempHumidSensor>(deviceDataVector[1], this, onVal);
				// add to devices vector
				this->devices.push_back(device);
			} 
			else if (deviceDataVector[0] == "Heating Thermostat") {// will be in format:  type,name,onVal,temp;
				// format params
				bool onVal = stoi(deviceDataVector[2]);
				int temprature = stoi(deviceDataVector[3]); 
				// create object
				shared_ptr<HeatingThermostat> device = make_shared<HeatingThermostat>(deviceDataVector[1], this, onVal, temprature);
				// add to devices vector
				this->devices.push_back(device);
			}
			
			
			
			// add devies as they are developed
		}
		
	}
	// ceated devicess
	return true;
}

bool HomeSystem::deleteDevice(HomeDevice* deviceToDelete) {
	string input; 
	cout << "Delete " + deviceToDelete->getName() + "?\n";
	cout << "Enter Y for yes and N for No: "; 
	cin >> input; 
	input = HomeSystemFunctions::trim(input);
	if (input == "Y") {
		// find device to remove
		// cannot compare share pointers to raw pointers and cannot convert without creating a new object so 
		// using findDevice that returns the shared pointer to the device
		this->devices.erase(remove(this->devices.begin(), this->devices.end(), this->findDevice(deviceToDelete->getName())), this->devices.end());
		return false; // as We want to exit the menue system after deletion 
	}
	else if (input == "N") {
		return true; 
	}
	else {
		cout << "\n ### Invalid Input ### \n ";
		deleteDevice(deviceToDelete);
	}

	
	// no need for pointer clean up as im using smart pointers 
}

