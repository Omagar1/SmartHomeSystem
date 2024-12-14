#pragma once
#include<iostream>
#include<vector>
#include <filesystem>
#include<map>
#include "HomeDevice.h"
#include "Params.h"
#include "Light.h"
#include "TempHumidSensor.h"
#include "HomeSystemFunctions.h"




using namespace std; 

struct DeviceTypes {
	map<string, string> names;
	map<char, function<bool()>> createFunctions; 
};


class HomeSystem
{
	public:
		HomeSystem(string name, string filePath, vector<shared_ptr<HomeDevice>>* devices = new vector<shared_ptr<HomeDevice>>());
		~HomeSystem();
		void menu();
		shared_ptr<HomeDevice> findDevice(string name);
		bool isDevice(string name);
		bool addDevice();
		bool selectDevice();

		//void quickDisplayDevice();
		bool listDevices(int startIndex = 0);
		/*void sortByName();
		void sortByDevice();*/
		bool saveOnExit();
		bool load(); 

		
		bool rename(); // for homeSystem

		// --- Device Creation functions ---
		/*bool standardCheckParams(Params* params); */
		bool createLight(); 
		bool createTempHumidSensor(); 

	private:
		string name;
		string filePath; 
		vector<shared_ptr<HomeDevice>>* devices; // shared as I pass pointers in other functions so I can use that device

		const map<string, string> typeNames = { { "1", ": Light\n" } , { "2", ": Temperature and Humidity Sensor\n" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createLight(); } },{ '2' , [this]() {return this->createTempHumidSensor(); } } };
}; 




