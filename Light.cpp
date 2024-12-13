#include "Light.h"
Light::Light(string name, HomeSystem* homeSystem, float brightness = 1.00f): Schedule(name, homeSystem),  brightness(brightness) {}

bool Light::quickAction() {
	this->switchOnVal(); 
	return true; 
}


LightParams* Light::getParams() {
	LightParams* params = new LightParams();
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

	cout << "\nBrightness (between 0 and 1.00): ";
	cin >> temp;
	if (temp != "" || HomeSystemFunctions::canConvertToFloat(temp)) {
		float floatTemp = stof(temp);
		if (floatTemp >= 0 && floatTemp <= 1) {
			params->brightness = floatTemp;
		}
		else {
			params->paramsCorrect = false;
			params->errorMsg = "enter a number between 0 and 1.00!";
		}
	}
	else {
		params->paramsCorrect = false;
		params->errorMsg = "enter a number between 0 and 1.00!";
	}

	return params;
}