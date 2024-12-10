#include "HomeSystemFunctions.h"
template<typename Class>
void HomeSystemFunctions::menu(map<string, string> dispaly, map<char, function<bool()>> functions, Class object, vector<string> dontDisplay ) {
	bool exit = false;
	do {
		string input;

		HomeSystemFunctions::displayOptions(dispaly, dontDisplay);

		cin >> input;

		// runs related funcution if input is a key of functions
		if (functions.find(input[0]) != functions.end()) {
			char key = input[0];
			
			exit = !object->functions[key]();
		}
		else {
			cout << "Invalid input Try again: \n";
		}
	} while (!exit);	
}

// devolped with help form MS co pilate  
bool HomeSystemFunctions::canConvertToFloat(const string& str) {
	try { 
		stof(str); return true; 
	} 
	catch (const invalid_argument&) 
	{ 
		return false;

	} 
	catch (const out_of_range&) { 
		return false; 
	} 
}