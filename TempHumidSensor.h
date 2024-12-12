#pragma once
#include "HomeDevice.h"
class TempHumidSensor : public HomeDevice
{
public:
	// --- quick action stuff ---
	/*void quickView() override;
	string quickViewStr() override;
	bool quickAction() override;*/
	// --- Sensor Stuff --- 
	/*bool displayCurrentData();
	bool displayHistoricData(); */
	

private:
	string dataFilePath; 
};

