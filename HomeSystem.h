#include<iostream>
#include<vector>
#include"HomeDevice.h"
#include"Light.h"
using namespace std; 

struct params {
	string name;
};
struct DeviceTypes {
	map<string, string> display;
	map<char, functionData> functions;
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
		inline Light* createLight(); 
	private:
		string name;
		DeviceTypes deviceTypes; 
		vector<HomeDevice>* devices;
		int numDevices; 

};

inline Light* Light::createLight() {
	LightParams params = Light::askForParams();
	Light* newLight = new Light(params.name, params.brightness);
}

