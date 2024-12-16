#include "Light.h"
Light::Light(string name, HomeSystem* homeSystem, float brightness, bool onVal): SleepDevice(name, homeSystem, onVal),  brightness(brightness) {}

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



bool Light::quickAction() {
	this->switchOnVal(); 
	return true; 
}

void Light::menu() {
	cout << "\n"; // so the input line doesnt get mixed up with the output
	// numbers and leters in headers are so they are displayed in correct order
	map<string, string> menuDispaly = {
		{"0Adataheader", "\n-----" + this->getName() + "Data ----- \n"},
		{"0data", this->quickViewStr("\n")},
		{"0header", "\n-----" + this->getName() + " Home Device Menu----- \n"},
		{"0intro", "Enter From the following:\n"},
		{"1", ": Toggle On Switch\n"},
		{"2", ": Rename Device  \n"},
		{"3", ": Change Brigntness  \n"},
		{"4", ": Send to Sleep \n"},
		{"D", ": Delete \n"},
	};


	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = [this]() {cout << "\n Switching " << this->getOpositeOnValStr() << "\n"; this->switchOnVal(); return true;   };
	menuFunctions['2'] = [this]() {return this->rename(this->getHomeSystem()); };
	menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet;
	menuFunctions['4'] = [this]() {return this->setSleepTimer(); };
	menuFunctions['D'] = HomeSystemFunctions::notDevelopedYet;

	vector<string> ignoreHeader = { "0header", "0intro" , "0data" , "0Adataheader" };

	HomeSystemFunctions::menuDisplay<HomeDevice*>(menuDispaly, menuFunctions, this, ignoreHeader);
}

void Light::saveOnExit(string filePath) {
	// will be in format:  type,name,brightness;
	string data = getTypeStr() + "," + this->getName() + "," + to_string(getOnVal()) + "," + to_string(this->brightness);
	HomeSystemFunctions::storeData(filePath, data);
}


