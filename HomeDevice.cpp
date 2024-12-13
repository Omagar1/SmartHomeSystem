#include "HomeDevice.h"
#include "HomeSystem.h"
HomeDevice::HomeDevice(string name, HomeSystem* homeSystem): name(name),  homeSystem(homeSystem) {}



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
void HomeDevice::quickView() { 
	cout << this->quickViewStr(); 
}

// --- rest of functions --- 
bool HomeDevice::quickAction() {
	this->switchOnVal(); 
	return true; 
}

void HomeDevice::menu() {
	// numbers in headers are so they are displayed in correct order
	map<string, string> menuDispaly = {
		{"0header", "\n-----" + this->name + " Home Device Menu----- \n"}, /// then this 
		{"0Status", "Status: "+ getOnValStr() + " \n"}, // this displays first - need to fix 
		{"0intro", "Enter From the following:\n"},
		{"1", ": Toggle On Switch\n"},
		{"2", ": Rename Device  \n"},
		{"D", ": Delete \n"},
	};


	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = [this]() {cout << "\n Switching " << this->getOpositeOnValStr()<<"\n"; this->switchOnVal(); return true;   };
	menuFunctions['2'] = [this]() {return this->rename(this->homeSystem); };
	menuFunctions['D'] = HomeSystemFunctions::notDevelopedYet;
	
	vector<string> ignoreHeader = { "0header", "0intro" , "0Status" };

	HomeSystemFunctions::menuDisplay<HomeDevice*>(menuDispaly, menuFunctions, this, ignoreHeader);
}

void HomeDevice::load() {
	// get data from file
}

bool HomeDevice::rename(HomeSystem* homeSystem) { // for device 
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
		return rename(homeSystem);
	}
	else if (homeSystem->isDevice(input)) {
		cout << "\n ### Name Already Taken #### \n ";
		return rename(homeSystem);
	}
	else {
		this->name = input;
		cout << "\n Name Set \n";
		return true;
	}
}






