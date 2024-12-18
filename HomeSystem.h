#pragma once
#include<iostream>
#include<vector>
#include <filesystem>
#include<map>
#include "HomeDevice.h"
#include "Params.h"
#include "Light.h"
#include "HeatingThermostat.h"
#include "TempHumidSensor.h"
#include "HomeSystemFunctions.h"
#include "ThreadManager.h"




using namespace std; 

//struct DeviceTypes {
//	map<string, string> names;
//	map<char, function<bool()>> createFunctions; 
//};

enum SortByType{
	AS_IS,
	NAME,
	TYPE
};



class HomeSystem
{
	public:
		HomeSystem(string name, string filePath, bool loadFromFile = false);
		~HomeSystem();
		void menu();
		shared_ptr<HomeDevice> findDevice(string name);
		bool isDevice(string name);
		bool addDevice();
		bool selectDevice();

		//void quickDisplayDevice();
		bool listDevices(int startIndex = 0, SortByType sortBy = AS_IS);
		bool saveOnExit();
		bool load(); 
		bool deleteDevice(HomeDevice* deviceToDelete);
		inline ThreadManager* getThreadManagerPtr();

		
		bool rename(); // for homeSystem

		// --- Device Creation functions ---
		/*bool standardCheckParams(Params* params); */
		bool createLight(); 
		bool createTempHumidSensor(); 
		bool createHeatingThermostat();

	private:
		string name;
		string filePath;
		ThreadManager* threadManager; 
		vector<shared_ptr<HomeDevice>> devices; // shared as I pass pointers in other functions so I can use that device

		const map<string, string> typeNames = { { "1", ": Light\n" } , { "2", ": Temperature and Humidity Sensor\n" }, { "3", ": HeatingThermostat\n" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createLight(); } },{ '2' , [this]() {return this->createTempHumidSensor(); } },{ '3' , [this]() {return this->createHeatingThermostat(); } } };
}; 
ThreadManager* HomeSystem::getThreadManagerPtr() {return this->threadManager;}




