#include "Light.h"
Light::Light(string name, float brightness = 1.00f): brightness(brightness) {}

LightParams* Light::getParams() {
	LightParams* params = new LightParams();
	string temp;
	cout << "\nDevice name: ";
	cin >> temp;
	if (temp != "") {
		params->name = temp; 
	}
	else {
		params->paramsCorrect = false; 
	}

	cout << "\nBrightness (between 0 and 1.00): ";
	cin >> temp;
	if (temp != "" || HomeSystemFunctions::canConvertToFloat(temp)) {
		params->brightness = stof(temp);
	}
	else {
		params->paramsCorrect = false;
	}

	return params;
}