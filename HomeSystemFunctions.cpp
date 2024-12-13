#include "HomeSystemFunctions.h"


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
string HomeSystemFunctions::timeToStr(time_t time, string format) {
	char str[80]; // 80 comes form example in https://cplusplus.com/reference/ctime/strftime/
	std::tm timeInfo;
	localtime_s(&timeInfo, &time);
	strftime(str, 80, format.c_str(), &timeInfo);
	return str;
}



bool HomeSystemFunctions::storeData(string filePath, vector<string> data, string delimiter ) {
	ofstream file(filePath, ios::app);

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

bool HomeSystemFunctions::storeData(string filePath, string str) {
	ofstream file(filePath, ios::app);

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



