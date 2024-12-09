#include "Light.h"
Light::Light(string name, float brightness): brightness(brightness) {}

LightParams Light::askForParams() {
	LightParams params; 
	cout << "\n Name: "; 
	// add valadation
	cin >> params.name; 
	cout << "\n brightness: ";
	// add valadation
	cin >> params.brightness;
	return params; 
}