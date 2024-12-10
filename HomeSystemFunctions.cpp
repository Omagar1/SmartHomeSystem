#include "HomeSystemFunctions.h"
#include "CommonFunctions.h"
template<typename ReturnType>
void HomeSystemFunctions::menu(map<string, string> dispaly, map<char, functionData<ReturnType>> functions, vector<string> dontDisplay) {
	bool exit = false;
	do {
		string input;

		HomeSystemFunctions::displayOptions(dispaly, dontDisplay);

		cin >> input;

		// runs related funcution if input is a key of functions
		if (functions.find(input[0]) != functions.end()) {

			char key = input[0];
			if (functions[key].type == NO_PARAMS) {
				exit = !functions[key].function.funcWithoutParams();
			}
			else {
				vector<string>* parameters = { CommonFunctions::split(input.erase(0,1), ',') };
				exit = !functions[key].function.funcWithParams(parameters);

			}
		}
		else {
			cout << "\n ### Invalid input Try again: \n";
		}
	} while (!exit);
	

	
}