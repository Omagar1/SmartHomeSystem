#pragma once
#include<iostream>
#include<vector>
#include <filesystem>
#include<map>
#include <type_traits>

#include "HomeDevice.h"
#include "Params.h"
#include "Light.h"
#include "HeatingThermostat.h"
#include "TempHumidSensor.h"
#include "HomeSystemFunctions.h"
#include "ThreadManager.h"
#include "Radiator.h"




using namespace std; 

//struct HomeDevices {
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
		inline shared_ptr<ThreadManager> getThreadManagerPtr();

		
		bool rename(); // for homeSystem

		// --- Device Creation functions ---
		/*bool standardCheckParams(Params* params); */
		template <
			typename DeviceType, 
			typename DeviceParams,
			typename = enable_if_t<is_base_of_v<HomeDevice, DeviceType>>, 
			typename = enable_if_t<is_base_of_v<Params, DeviceParams>>
		>
		bool createDevice(); 

		bool createLight(); 
		bool createTempHumidSensor(); 
		bool createHeatingThermostat();
		bool createRadiator(); 

	private:
		string name;
		string filePath;
		shared_ptr<ThreadManager> threadManager; 
		vector<shared_ptr<HomeDevice>> devices; // shared as I pass pointers in other functions so I can use that device

		const map<string, string> typeNames = { { "1", ": Light\n" } , { "2", ": Temperature and Humidity Sensor\n" }, { "3", ": HeatingThermostat\n" }, { "4", ": Radiator\n" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createDevice<Light, LightParams>(); } },{ '2' , [this]() {return this->createDevice<TempHumidSensor, Params>(); } },{ '3' , [this]() {return this->createDevice<HeatingThermostat, HeatingThermostatParams>(); } }, { '4' , [this]() {return this->createDevice<Radiator, RadiatorParams>(); } } };
}; 
shared_ptr<ThreadManager> HomeSystem::getThreadManagerPtr() {return this->threadManager;}

// using concepts from https://en.cppreference.com/w/cpp/types/is_base_of?form=MG0AV3 to check if Templated classs are in the correct inhertance structures
template <typename DeviceType, typename DeviceParams, typename , typename>
bool HomeSystem::createDevice() {
	// get params
	DeviceParams* params = nullptr;
	do {
		this->threadManager->getMutex().lock(); // to prevent confusing interupts 
		if (params != nullptr) {
			cout << "\n ### Invalid Input ### \n ";
			cout << params->errorMsg << "\n";
		}

		params = DeviceType::getParams();
		if (this->isDevice(params->name)) {
			params->paramsCorrect = false;
			params->errorMsg = "\n ### Name Already Taken ####  \n";
		}
		this->threadManager->getMutex().unlock();
	} while (!params->paramsCorrect);

	// Create new Device object 
	shared_ptr<DeviceType> newDevice = make_shared<DeviceType>(params, this);

	// Add Device to devices vector 
	this->devices.push_back(newDevice);

	cout << *newDevice << " has been added \n";
	
	

	return false; // as after creation we want to return to main menu 
}

