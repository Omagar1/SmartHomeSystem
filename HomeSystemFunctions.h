#pragma once
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include<iostream>
#include <fstream>
#include<string>
#include <ctime>
#include <time.h>


using namespace std;

class ThreadManager;

static class HomeSystemFunctions
{
public:
	// --- display stuff --- 
	template <size_t N>
	inline static void displayOptions(string(&outArr)[N]);

	inline static void displayOptions(map<string, string>outArr, vector<string> dontDisplay = vector<string>());
	inline static bool notDevelopedYet();
	static bool menuDisplay(const map<string, string> dispaly, const map<char, function<bool()>> functions, shared_ptr<ThreadManager> threadManger, const vector<string> dontDisplay = vector<string>(), shared_ptr<string> input = make_shared<string>());
	// --- convertion stuff ---
	template<typename T>
	inline static bool canConvertStrToType(const string str);
	static string timeToStr(time_t time, string format = "%Y-%m-%d %H:%M:%S"); 
	// --- file stuff ---
	static bool storeData(string filePath, vector<string> data, string delimiter = ",", bool overWrite = false);
	static bool storeData(string filePath, string str, bool overWrite = false);
	static vector<string> loadData(string filePath);
	// --- helpful stuff --- 
	static string trim(string str); // removes whitespace from start and end of string
	static string trim(string str, char toRemoveFromStart, char toRemoveFromEnd); // removes any char start and end of string 
	static vector<string> split(string str, char delimiter = ','); 
	
};

template <size_t N> // iterator workaround found from https://stackoverflow.com/questions/28653967/range-based-for-loop-throws-a-compiler-error-with-array-parameter
inline void HomeSystemFunctions::displayOptions(string (&outArr)[N]) {
	for (string line : outArr) {
		cout << line;
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

template<>
inline bool HomeSystemFunctions::canConvertStrToType<float>(const string str) {
	try {
		stof(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<>
inline bool HomeSystemFunctions::canConvertStrToType<int>(const string str) {
	try {
		stoi(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

