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
		HomeSystem(string name, vector<HomeDevice*>* devices = new vector<HomeDevice*>());
		void menu();
		HomeDevice* findDevice(string name);
		bool isDevice(string name);
		bool addDevice();
		bool selectDevice();

		//void quickDisplayDevice();
		bool listDevices(int startIndex = 0);
		/*void sortByName();
		void sortByDevice();*/
		bool SaveOnExit();
		bool Load(); 

		
		bool rename(); // for homeSystem

		// --- Device Creation functions ---
		/*bool standardCheckParams(Params* params); */
		bool createLight(); 
		bool createTempHumidSensor(); 

	private:
		string name;
		vector<HomeDevice*>* devices;

		const map<string, string> typeNames = { { "1", ": Light\n" } , { "2", ": Temperature and Humidity Sensor\n" } };
		const map<char, function<bool()>> typeCreateFunctions = { { '1' , [this]() {return this->createLight(); } },{ '2' , [this]() {return this->createTempHumidSensor(); } } };
}; 




