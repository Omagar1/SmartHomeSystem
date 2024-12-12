#pragma once
#include<iostream>
#include<vector>
#include "HomeSystemFunctions.h"
#include "Params.h"

using namespace std;

class HomeDevice
{
	public: 
		/*HomeDevice(string name);*/
		// --- getters ---
		string getName();
		// --- quick action stuff ---
		virtual void quickView();
		virtual string quickViewStr();
		virtual bool quickAction(); 
		// --- rest of functions --- 
		virtual void menu();
		virtual void load(); 
		static Params* getParams();
	protected:
		inline bool getOnVal();
		inline void switchOnVal();
		inline void setOnVal(bool val);
	private:
		string name;
		bool on = false; 
		
		
};

 bool HomeDevice::getOnVal() {return this->on;}
 void HomeDevice::switchOnVal() { this->on = !this->on;  }
 void HomeDevice::setOnVal(bool val) { this->on = val; }