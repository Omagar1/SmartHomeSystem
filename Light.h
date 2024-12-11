#pragma once
#include <string>

#include "HomeDevice.h"
#include "HomeSystemFunctions.h"; 

struct LightParams : Params {
	float brightness; 
};

class Light : public HomeDevice
{
public: 
	Light(string name, float brightness);

	static LightParams* getParams();
private:
	float brightness; // percentage stored as value between 0 and 1.00
};

