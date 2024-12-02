#include<iostream>
#include<vector>
#include"HomeDevice.h"
using namespace std; 

#pragma once
class HomeSystem
{
	public:
		HomeSystem(string name, vector<HomeDevice>* devices = nullptr, int numDevices = 0);
		void menu();
		HomeDevice findDevice(string name);
		bool isDevice(string name);
		/*void addDevice();
		void selectDevice();
		void quickDisplayDevice();
		void listDevice(); 
		void sortByName();
		void sortByDevice();
		bool SaveOnExit();
		bool Load(); */
	private:
		string name; 
		vector<HomeDevice>* devices;
		int numDevices; 

};

