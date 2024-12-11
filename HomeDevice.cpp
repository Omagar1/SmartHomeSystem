#include "HomeDevice.h"
//HomeDevice::HomeDevice(string name): name(name) {}

string HomeDevice::getName() {
	return this->name; 
}
void  HomeDevice::quickView() {
	string output[] = {
		this->name + ((this->on) ? "On" : "off") + " \n",
	};
}
void HomeDevice::menu() {
	cout << "Feature still in devlopment";
}
void HomeDevice::load() {
	// get data from file
}

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


