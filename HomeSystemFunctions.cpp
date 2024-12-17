#include "HomeSystemFunctions.h"

bool HomeSystemFunctions::menuDisplay(map<string, string> dispaly, map<char, function<bool()>> functions, vector<string> dontDisplay) {
	// returns ture if menu neds to be called again, returns false if it donest
	// done this way so display can update with new data that might have channged from functions called in the menu system running
	string input;
	functions.insert({ 'Q', []() { return false; } });// so if a caller already has a function for exit they can call that instead do this default

	HomeSystemFunctions::displayOptions(dispaly, dontDisplay);
	cout << "Q: Exit \n";
	cout << "Input: ";
	cin >> input;

	// runs related funcution if input is a key of functions
	if (functions.find(input[0]) != functions.end()) {
		char key = input[0];

		 return functions[key]();
	}
	else {
		cout << "\n ### Invalid input Try again: ### \n";
		return true;
	}
}

  
bool HomeSystemFunctions::canConvertToFloat(const string& str) {
	try { 
		stof(str); 
		return true; 
	} 
	catch (const invalid_argument&) 
	{ 
		return false;
	} 
	catch (const out_of_range&) { 
		return false; 
	} 
}
string HomeSystemFunctions::timeToStr(time_t time, string format) {
	char str[80]; // 80 comes form example in https://cplusplus.com/reference/ctime/strftime/
	std::tm timeInfo;
	localtime_s(&timeInfo, &time);
	strftime(str, 80, format.c_str(), &timeInfo);
	return str;
}



bool HomeSystemFunctions::storeData(string filePath, vector<string> data, string delimiter, bool overWrite) {
	ofstream file; 
	if (overWrite) {
		file.open(filePath);
	}
	else {
		file.open(filePath, ios::app);
	}

	if (file.is_open()) {
		file << "\n"; 
		for (string str : data) {
			file << str << delimiter;
		}
		file.close();
		return true;
	}
	else {
		cerr << "\n Error opening file: " << filePath << "\n";
		return false; 
	}
	
}

bool HomeSystemFunctions::storeData(string filePath, string str, bool overWrite) {
	ofstream file;
	if (overWrite) {
		file.open(filePath);
	}
	else {
		file.open(filePath, ios::app);
	}

	if (file.is_open()) {
		file << "\n" << str;
		file.close();
		return true;
	}
	else {
		cerr << "\n Error opening file: " << filePath << "\n";
		return false;
	}
}

vector<string> HomeSystemFunctions::loadData(string filePath) {
	ifstream file(filePath);

	if (file.is_open()) {
		vector<string>output = vector<string>();
		string line;
		while (getline(file, line)) {
			output.push_back(line); 
		}
		return output; 
	}
	else {
		cerr << "\n Error opening file: " << filePath << "\n";
		return vector<string>();
	}
}

string HomeSystemFunctions::trim(string str) {
	// find first non whitespace
	if (str != "") {
		string::iterator startIt = str.begin();
		string::iterator endIt = str.end() - 1;
		while (startIt != endIt && isspace(*startIt)) {
			startIt++;
		}
		// find last
		while (endIt != startIt && isspace(*endIt)) {
			endIt--;
		}
		return string(startIt, endIt + 1);
	}
	else {
		return str; 
	}
 
}

vector<string> HomeSystemFunctions::split(string str, char delimiter) {
	vector<string> splitStr;
	str += delimiter; // so last item is counted without having to add any exta logic
	string::iterator startSubStrIt = str.begin();
	string::iterator endSubStrIt = str.begin();
	while (endSubStrIt != str.end()) {
		if (*endSubStrIt == delimiter) {
			splitStr.push_back(string(startSubStrIt, endSubStrIt));
			startSubStrIt = ++endSubStrIt; //jumping over the delimiter char in the string
		}
		else if (endSubStrIt != str.end()) {
			endSubStrIt++; // so it dosent overflow
		}
		
	}
	return splitStr;
}



