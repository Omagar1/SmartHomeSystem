#pragma once
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include<iostream>
using namespace std;
// --- common data types ---

enum funcType { NO_PARAMS, WITH_PARAMS };

// structer so any params can be passed to any function 
// note each smartDevice has a derived struct to pass their creeation params into 
struct params {
	string name;
};

// multi signature pointer
template<typename ReturnType>
union funcPointer {
	ReturnType(*funcWithoutParams)();
	ReturnType(*funcWithParams)(const params);
};
// struct to hold the function pointer and its type 
template<typename ReturnType>
struct functionData {
	funcPointer<ReturnType> function;
	funcType type;
};

static class HomeSystemFunctions
{
public:
	

	template <size_t N>
	inline static void displayOptions(string(&outArr)[N], vector<string> dontDisplay = vector<string>() );

	inline static void displayOptions(map<string, string>outArr, vector<string> dontDisplay = vector<string>());
	inline static bool notDevelopedYet();
	inline static bool exit();
	template<typename ReturnType>
	static void menu(map<string,string> dispaly, map<char, functionData<ReturnType>> functions, vector<string> dontDisplay = vector<string>());
	
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
inline bool HomeSystemFunctions::exit() { cout << "exiting"; return false; }

