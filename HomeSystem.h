#include<iostream>
#include<vector>
#include<map>
#include"HomeDevice.h"
using namespace std; 

struct DeviceTypes {
	map<string, string> names;
	map<char, function<bool()>> createFunctions; 
};



#pragma once
class HomeSystem
{
	public:
		HomeSystem(string name, vector<HomeDevice*>* devices = nullptr);
		void menu();
		HomeDevice* findDevice(string name);
		bool isDevice(string name);
		bool addDevice();
		/*void selectDevice();
		void quickDisplayDevice();
		void listDevice(); 
		void sortByName();
		void sortByDevice();
		bool SaveOnExit();
		bool Load(); */
		// --- Device Creation functions --- 
		bool createLight(); 

	private:
		string name;
		vector<HomeDevice*>* devices;

		const map<string, string> typeNames = { { "1", "Light" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createLight(); } } };

}; 

