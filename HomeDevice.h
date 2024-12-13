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
		HomeDevice(string name, HomeSystem* homeSystem);
		// --- getters ---
		inline string getName();
		static Params* getParams();
		// --- setters ---
		inline void setName(string newName);
		// --- quick action stuff ---
		virtual void quickView();
		virtual string quickViewStr();
		virtual bool quickAction(); 
		// --- rest of functions --- 
		virtual void menu();
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
		bool on = false; 
		
		
};
string HomeDevice::getName() { return this->name; }
void HomeDevice::setName(string newName) { this->name = newName; }

bool HomeDevice::getOnVal() {return this->on;}
string HomeDevice::getOnValStr() { return ((this->on) ? "On" : "Off");  }
string HomeDevice::getOpositeOnValStr() { return ((!this->on) ? "On" : "Off");  }
void HomeDevice::switchOnVal() { this->on = !this->on;  }
void HomeDevice::setOnVal(bool val) { this->on = val; }
 