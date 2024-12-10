#include "HomeDevice.h"
//HomeDevice::HomeDevice(string name): name(name) {}

string HomeDevice::getName() {
	return this->name; 
}
void HomeDevice::menu() {
	cout << "Feature still in devlopment";
}
void HomeDevice::load() {
	// get data from file
}

void  HomeDevice::quickView() {
	string output[] = {
		this->name + ((this->on) ? "On" : "off") + " \n",
	};
}
