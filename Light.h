#pragma once
#include "HomeDevice.h"
#include "HomeSystem.h" 

struct LightParams : params {
	float brightness;
};


class Light : public HomeDevice
{
public: 
	Light(string name, float brightness);
	LightParams static askForParams();
private:
	float brightness; // percentage stored as value between 0 and 1.00
};

