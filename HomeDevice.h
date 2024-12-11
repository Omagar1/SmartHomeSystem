#include<iostream>
#include<vector>
#include <ctime>


using namespace std;
struct Params {
	string name;
	bool paramsCorrect;
	string errorMsg;
};


#pragma once
 class HomeDevice
{
	public: 
		/*HomeDevice(string name);*/
		string getName();
		virtual void quickView(); 
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