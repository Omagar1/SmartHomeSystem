#include "Radiator.h"
#include "HomeSystem.h"

Radiator::Radiator(string name, HomeSystem* homeSystem, int temprature, bool onVal) : HomeDevice(name, homeSystem, onVal), temprature(temprature) {}
Radiator::Radiator(RadiatorParams* params, HomeSystem* homeSystem) : HomeDevice(params->name, homeSystem), temprature(params->temprature) {
	delete(params);
	params = nullptr; 
}

RadiatorParams* Radiator::getParams() {
	RadiatorParams* params = new RadiatorParams();
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

	cout << "\n Temprature setting (in degrees C): ";
	cin >> temp;
	if (HomeSystemFunctions::canConvertStrToType<int>(temp) && temp != "") {
		float floatTemp = stof(temp);
		if (floatTemp >= 0 && floatTemp <= 50) { // 50 is abituary but world be very hot!
			params->temprature = floatTemp;
		}
		else {
			params->paramsCorrect = false;
			params->errorMsg = "enter a number between 0 and 50!";
		}
	}
	else {
		params->paramsCorrect = false;
		params->errorMsg = "enter a number!";
	}

	return params;
}


void Radiator::menu() {
	map<string, string> menuDispaly;
	map<char, function<bool()>> menuFunctions;
	vector<string> ignoreHeader;
	do {
		cout << "\n"; // so the input line doesnt get mixed up with the output
		// numbers and leters in headers are so they are displayed in correct order
		menuDispaly = {
			{"0Adataheader", "\n-----" + this->getName() + "Data ----- \n"},
			{"0data", this->quickViewStr("\n")},
			{"0header", "\n-----" + this->getName() + " Home Device Menu----- \n"},
			{"0intro", "Enter From the following:\n"},
			{"1", ": Toggle On Switch\n"},
			{"2", ": Rename Device  \n"},
			{"3", ": Change Temprature Setting  \n"},
			{"D", ": Delete \n"},
		};

		ignoreHeader = { "0header", "0intro" , "0data" , "0Adataheader" };

		menuFunctions['1'] = [this]() {cout << "\n Switching " << this->getOpositeOnValStr() << "\n"; this->switchOnVal(); return true;   };
		menuFunctions['2'] = [this]() {return this->rename(this->getHomeSystem()); };
		menuFunctions['3'] = HomeSystemFunctions::notDevelopedYet;
		menuFunctions['D'] = [this]() {return this->getHomeSystem()->deleteDevice(this); };

	} while (HomeSystemFunctions::menuDisplay(menuDispaly, menuFunctions, this->getHomeSystem()->getThreadManagerPtr(), ignoreHeader));
}

void Radiator::saveOnExit(string filePath) {
	// will be in format:  type,name,onVal,temp;
	string data = getTypeStr() + "," + this->getName() + "," + to_string(getOnVal()) + "," + to_string(this->temprature);
	HomeSystemFunctions::storeData(filePath, data);
}