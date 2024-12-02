#include "HomeSystemFunctions.h"
void HomeSystemFunctions::menu(map<string, string> dispaly, map<char, function<bool()>> functions, vector<string> dontDisplay) {
	bool exit = false;
	do {
		string input;

		HomeSystemFunctions::displayOptions(dispaly, dontDisplay);

		cin >> input;

		// runs related funcution if input is a key of functions
		if (functions.find(input[0]) != functions.end()) {
			char key = input[0];
			/*string parameters = input.erase(0, 1);
			exit = ! (parameters != NULL)? functions[key](parameters): functions[key]();*/
		}
		else {
			cout << "Invalid input Try again: \n";
		}
	} while (!exit);
	

	
}