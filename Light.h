#pragma once
#include "HomeDevice.h"
class Light : public HomeDevice
{
public: 
	Light(string name, float brightness);
private:
	float brightness; // percentage stored as value between 0 and 1.00
};

