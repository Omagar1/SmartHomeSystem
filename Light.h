#pragma once
#include <string>
#include "Params.h"
#include "HomeSystemFunctions.h"
#include "Schedule.h"

struct LightParams : Params {
	float brightness; 
};

class Light : public Schedule
{
public: 
	Light(string name, float brightness);
	// --- quick action stuff ---
	void quickView() override;
	string quickViewStr() override;
	bool quickAction() override;
	//
	static LightParams* getParams();

private:
	float brightness; // percentage stored as value between 0 and 1.00
};

