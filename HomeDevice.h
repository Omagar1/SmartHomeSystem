#pragma once
#include<iostream>
#include<vector>
#include <cctype>
#include <cmath>
#include "HomeSystemFunctions.h"
#include "Params.h"


using namespace std;

class HomeSystem;

class HomeDevice
{
	public: 
		HomeDevice(string name, HomeSystem* homeSystem, bool onVal = false);
		
		~HomeDevice(); 
		// --- getters ---
		inline string getName() const;
		static Params* getParams();
		inline HomeSystem* getHomeSystem()const;
		inline virtual string getTypeStr() const;
		// --- setters ---
		inline void setName(string newName);
		// --- quick action stuff ---
		virtual void quickView();
		inline virtual string quickViewStr(string delimiter = " ");
		virtual bool quickAction(); 
		// --- rest of functions --- 
		virtual void menu();
		virtual void saveOnExit(string filePath);
		static bool compareByType(const shared_ptr<HomeDevice> lhs, const shared_ptr<HomeDevice> rhs);
		// --- operator overlaods --- 
		friend ostream& operator<<(ostream &os, const HomeDevice& outDevice); 
		bool operator>(const HomeDevice &rhs) const; // compares the names of this and another HomeDevice
		inline bool operator<(const HomeDevice &rhs) const; // just the not of >
		

	protected:
		HomeDevice();
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
string HomeDevice::getName() const { return this->name; }
HomeSystem* HomeDevice::getHomeSystem() const { return this->homeSystem; }
string HomeDevice::getTypeStr() const {
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

bool HomeDevice::operator<(const HomeDevice &rhs) const { return !((*this) > rhs);}
 