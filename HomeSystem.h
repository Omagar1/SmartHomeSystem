#pragma once
#include<iostream>
#include<vector>
#include<map>
#include "HomeDevice.h"
#include "Light.h"
#include "HomeSystemFunctions.h"




using namespace std; 

struct DeviceTypes {
	map<string, string> names;
	map<char, function<bool()>> createFunctions; 
};


class HomeSystem
{
	public:
		HomeSystem(string name, vector<HomeDevice*>* devices = new vector<HomeDevice*>());
		void menu();
		HomeDevice* findDevice(string name);
		bool isDevice(string name);
		bool addDevice();
		bool selectDevice();  // skippng as requires rework of menu system

		//void quickDisplayDevice();
		bool listDevices(int startIndex = 0);
		/*void sortByName();
		void sortByDevice();
		bool SaveOnExit();
		bool Load(); */

		bool rename(HomeDevice* device);
		bool rename(); // for homeSystem

		// --- Device Creation functions --- 
		bool createLight(); 

	private:
		string name;
		vector<HomeDevice*>* devices;

		const map<string, string> typeNames = { { "1", ": Light\n" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createLight(); } } };
}; 




