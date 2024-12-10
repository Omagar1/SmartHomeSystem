#pragma once
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include<iostream>


#include<string>
#include "HomeSystem.h"

using namespace std;

struct Params {
	string name;
	bool paramsCorrect;
	string errorMsg; 
};

static class HomeSystemFunctions
{
public:
	template <size_t N>
	inline static void displayOptions(string(&outArr)[N], vector<string> dontDisplay = vector<string>());

	inline static void displayOptions(map<string, string>outArr, vector<string> dontDisplay = vector<string>());
	inline static bool notDevelopedYet();
	template<typename Class> 
	static void menuDisplay(const map<string, string> dispaly, const map<char, function<bool()>> functions, const Class object, const vector<string> dontDisplay = vector<string>());
	static bool canConvertToFloat(const string& str);
};

template <size_t N> // iterator workaround found from https://stackoverflow.com/questions/28653967/range-based-for-loop-throws-a-compiler-error-with-array-parameter
inline void HomeSystemFunctions::displayOptions(string (&outArr)[N], vector<string> dontDisplay) {
	for (string line : outArr) {
		if (find(dontDisplay.begin(), dontDisplay.end(), line.first) != dontDisplay.end()) {
			cout << line.second;
		}
		else {
			cout << line.first << line.second;
		}
	}
}

inline void HomeSystemFunctions::displayOptions(map<string, string>outArr , vector<string> dontDisplay) {
	for (const auto& line : outArr) {
		if (find(dontDisplay.begin(), dontDisplay.end(), line.first) != dontDisplay.end()) {
			cout << line.second;
		}
		else {
			cout << line.first << line.second;
		}
	}
}
inline bool HomeSystemFunctions::notDevelopedYet() { cout << "Feature still in devlopment"; return true; }

template<typename Class>
void HomeSystemFunctions::menuDisplay(map<string, string> dispaly, map<char, function<bool()>> functions, Class object, vector<string> dontDisplay) {
	bool exit = false;
	do {
		string input;
		functions['Q'] = []() { return false; };

		HomeSystemFunctions::displayOptions(dispaly, dontDisplay);
		cout << "Q: Exit \n"; 
		cout << "Input: "; 
		cin >> input;

		// runs related funcution if input is a key of functions
		if (functions.find(input[0]) != functions.end()) {
			char key = input[0];

			exit = !functions[key]();
		}
		else {
			cout << "\n ### Invalid input Try again: ### \n";
		}
	} while (!exit);
}