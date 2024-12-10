#include<iostream>
#include<vector>
#include"HomeDevice.h"
#include"Light.h"
#include "HomeSystemFunctions.h"
#include "CommonFunctions.h"
using namespace std; 

template<typename ReturnType>
struct DeviceTypes {
	map<string, string> display;
	map<char, functionData<ReturnType>> functions;
};

#pragma once
class HomeSystem
{
	public:
		HomeSystem(string name, vector<HomeDevice>* devices = nullptr, int numDevices = 0);
		void menu();
		HomeDevice findDevice(string name);
		bool isDevice(string name);
		void addDevice();
		
		/*void selectDevice();
		void quickDisplayDevice();
		void listDevice(); 
		void sortByName();
		void sortByDevice();
		bool SaveOnExit();
		bool Load(); */

		// device create functions:
		Light* createLight();
	private:
		string name;
		DeviceTypes deviceTypes; 
		vector<HomeDevice>* devices;
		int numDevices; 

};

 

