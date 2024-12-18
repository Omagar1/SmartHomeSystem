#include "HomeDevice.h"
#include "HomeSystem.h"
HomeDevice::HomeDevice(string name, HomeSystem* homeSystem, bool onVal): name(name), homeSystem(homeSystem), on(onVal) {}
HomeDevice::~HomeDevice(){
	this->homeSystem = nullptr; // removing pointer but not cleaning up memorary becuse we are not deleting home system 
}


Params* HomeDevice::getParams() {
	Params* params = new Params();
	params->paramsCorrect = true;
	string temp;
	cout << "\nDevice name: ";
	cin >> temp;
	temp = HomeSystemFunctions::trim(temp); 
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
	map<string, string> menuDispaly;
	map<char, function<bool()>> menuFunctions;
	vector<string> ignoreHeader;
	do {
		// numbers in headers are so they are displayed in correct order
		menuDispaly = {
			{"0header", "\n-----" + this->name + " Home Device Menu----- \n"}, /// then this 
			{"0Status", "Status: " + getOnValStr() + " \n"}, // this displays first - need to fix 
			{"0intro", "Enter From the following:\n"},
			{"1", ": Toggle On Switch\n"},
			{"2", ": Rename Device  \n"},
			{"D", ": Delete \n"},
		};

		ignoreHeader = { "0header", "0intro" , "0Status" };
		
		menuFunctions['1'] = [this]() {cout << "\n Switching " << this->getOpositeOnValStr() << "\n"; this->switchOnVal(); return true;   };
		menuFunctions['2'] = [this]() {return this->rename(this->homeSystem); };
		menuFunctions['D'] = [this]() {return this->getHomeSystem()->deleteDevice(this); };

	} while (HomeSystemFunctions::menuDisplay(menuDispaly, menuFunctions, this->homeSystem->getThreadManagerPtr(), ignoreHeader));
}

void HomeDevice::saveOnExit(string filePath) {
	// will be in format:  type,name,*other atributes*
	string data = getTypeStr() + "," + this->getName() + "," + to_string(getOnVal());
	HomeSystemFunctions::storeData(filePath, data);
}

ostream& operator<<(ostream& os, const HomeDevice& outDevice) {
	os << outDevice.getTypeStr() << outDevice.name; 
	return os; 
}

bool HomeDevice::compareByType(const shared_ptr<HomeDevice> lhs, const shared_ptr<HomeDevice> rhs) {
	if (lhs->getTypeStr() == rhs->getTypeStr()) {
		return lhs < rhs; 
	}
	else if (lhs->getTypeStr() < rhs->getTypeStr()) {
		return true; 
	}
	else {
		return false; 
	}
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

bool HomeDevice::operator>(const HomeDevice& rhs) const { 
	// im doing this manualy as I want numeric values in the string to count differnatly to count as well so test9 < test10 == true but aaaaaaaaaaa < b == true 
	string::const_iterator lhsIt = (this->name).begin();
	string::const_iterator rhsIt = (rhs.name).begin();
	while (lhsIt != this->name.end() || rhsIt != rhs.name.end()) {
		// making numeric values as I want them 
		// lhs 
		int lhsItAsciiVal = 0;
		if (isdigit(*lhsIt)) {
			int i = 0; 
			// finding the whole number
			while (lhsIt != this->name.end() && isdigit(*lhsIt)) {
				i++;
				lhsIt++; 
			}
			// calculating value
			while (i > 0) {
				lhsItAsciiVal += (static_cast<int>(*(lhsIt - i))) * (pow(10, i - 1)); // gets the asci value of the first numeric value encountered then multiplies that by a power of 10 based on if its a tens hundreds ects
				i--; // then does the next number
			}		
		}
		else {
			lhsItAsciiVal = static_cast<int>(*lhsIt);
		}
		//rhs
		int rhsItAsciiVal = 0;
		if (isdigit(*rhsIt)) {
			int i = 0;
			// finding the whole number
			while (rhsIt != rhs.name.end() &&isdigit(*rhsIt)) {
				i++;
				rhsIt++;
			}
			// calculating value
			while (i > 0) {
				rhsItAsciiVal += (static_cast<int>(*(rhsIt - i))) * (pow(10, i - 1)); // gets the asci value of the first numeric value encountered then multiplies that by a power of 10 based on if its a tens hundreds ects
				i--; // then does the next number
			}
		}
		else {
			rhsItAsciiVal = static_cast<int>(*rhsIt);
		}
		// comparison
		if (lhsItAsciiVal > rhsItAsciiVal) {
			return true;
		}
		else if (lhsItAsciiVal < rhsItAsciiVal) {
			return false;
		}
		else {
			// case the charecters or numeric value is identical - not the enntire string
			lhsIt++;
			rhsIt++; 
		}
		
	}
	return false; // Case: the names are identical so the lhs !> rhs
}







