#pragma once
#include<iostream>
#include<vector>
#include "HomeSystemFunctions.h"
#include "Params.h"

using namespace std;

class HomeSystem;

class HomeDevice
{
	public: 
		HomeDevice(string name, HomeSystem* homeSystem, bool onVal = false);
		// --- getters ---
		inline string getName();
		static Params* getParams();
		inline HomeSystem* getHomeSystem();
		inline virtual string getTypeStr();
		// --- setters ---
		inline void setName(string newName);
		// --- quick action stuff ---
		virtual void quickView();
		inline virtual string quickViewStr(string delimiter = " ");
		virtual bool quickAction(); 
		// --- rest of functions --- 
		virtual void menu();
		virtual void saveOnExit(string filePath); 
		virtual void load();
		

	protected:
		bool rename(HomeSystem* homeSystem);
		inline bool getOnVal();
		inline string getOnValStr(); 
		inline string getOpositeOnValStr(); 
		inline void switchOnVal();
		inline void setOnVal(bool val);
	private:
		string name;
		HomeSystem* homeSystem;
		bool on; 
		
		
};
string HomeDevice::getName() { return this->name; }
HomeSystem* HomeDevice::getHomeSystem() { return this->homeSystem; }
string HomeDevice::getTypeStr() { 
	string type = (string)typeid(*this).name();
	type.erase(type.begin(), type.begin() + 6); // removing "class"
	return type;
}
void HomeDevice::setName(string newName) { this->name = newName; }

string HomeDevice::quickViewStr(string delimiter) {
	return "Type: " + getTypeStr() + delimiter + "Name: " + this->name + delimiter + "Status:" + getOnValStr() + delimiter +" Quick Action: Switch " + getOpositeOnValStr() + " \n";
}


bool HomeDevice::getOnVal() {return this->on;}
string HomeDevice::getOnValStr() { return ((this->on) ? "On" : "Off");  }
string HomeDevice::getOpositeOnValStr() { return ((!this->on) ? "On" : "Off");  }
void HomeDevice::switchOnVal() { this->on = !this->on;  }
void HomeDevice::setOnVal(bool val) { this->on = val; }
 