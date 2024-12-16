#include "TempHumidSensor.h"
#include "HomeSystem.h"

TempHumidSensor::TempHumidSensor(string Name, HomeSystem* homeSystem, bool onVal): HomeDevice(Name, homeSystem, onVal) {
	// set file paths - if i get a chance i wil create a strandard file path that can be chanaged
	

	this->FilePath = "C:/Users/josia/Documents/UNI Stuff/CS/24 25/Advanced Programing/SmartHomeSystem/RuntimeFiles/"+ this->getName() +"SensorData";
	// --- genarate last data ---
	this->lastHumidReading = (rand() % 100) / 100;
	this->lastTempReading = rand() % 30; 
	// --- store last data --- 
	time_t timeNow = std::time(nullptr); // Get current time 
	string timeNowStr = HomeSystemFunctions::timeToStr(timeNow);
	// setting up data string
	vector<string> data = { timeNowStr, this->getLastHumidReadingStr(), this->getLastTempReadingStr() };
	// storing data 
	HomeSystemFunctions::storeData(this->FilePath, data, ":");
	// --- setting up thread to generate historic data --- 
	ThreadManager* threadManager = homeSystem->getThreadManagerPtr();
	threadManager->createThread(&TempHumidSensor::generateHistoricData, this, threadManager, 5); // last param is the time between reading, if i have time i will make this user set

}


bool TempHumidSensor::quickAction() {
	cout << "\n This device dosent have a quick action \n ";
	return true; 
}


void TempHumidSensor::setCurrentReading() {
	// Seed the random number generator with the current time to make rand actualy random
	srand(static_cast<unsigned int>(time(0)));
	// --- set humid data --- 
	if (rand() % 2 == 0) { this->lastHumidReading += rand() % 5; }
	else { this->lastHumidReading -= rand() % 5; }
	//--- set temp data --- 
	if (rand() % 2 == 0) { this->lastTempReading += rand() % 5; }
	else { this->lastTempReading -= rand() % 5; }
	// --- store in file --- 
	time_t timeNow = std::time(nullptr); // Get current time 
	string timeNowStr = HomeSystemFunctions::timeToStr(timeNow);
	// setting up data string
	vector<string> data = { timeNowStr, this->getLastHumidReadingStr(), this->getLastTempReadingStr() };
	// storing data 
	HomeSystemFunctions::storeData(this->FilePath, data, ":");
}

bool TempHumidSensor::displayCurrentData() {
	cout << "\n--- Displaying Current Data ---\n\n";
	cout << "Humidity: " << this->getLastHumidReadingStr() <<"\n";
	cout << "tempriture: " << this->getLastTempReadingStr() <<"\n";
	return true;
}

bool TempHumidSensor::displayHistoricData() {
	vector<string> historicData = HomeSystemFunctions::loadData(this->FilePath); 
	cout << "\n--- Displaying Hisoric Data ---\n"; 
	for(string line: historicData){
		cout << line << "\n";
	}
	return true;
}

void TempHumidSensor::generateHistoricData(ThreadManager* threadManager, int readEvery) {

	while (this->getOnVal() && threadManager->getStopFlag().load()) { // seccond value so when sytsem is closed the thread stops
		std::this_thread::sleep_for(std::chrono::minutes(readEvery));
		this->setCurrentReading();
	}
}

void TempHumidSensor::menu() {
	// so reading are simulated to be taken without using threads 
	this->setCurrentReading();

	cout << "\n"; // so teh input line doesnt get mixed up with the output
	// numbers and leters in headers are so they are displayed in correct order
	map<string, string> menuDispaly = {
		{"0Adataheader", "\n-----" + this->getName() + "Data ----- \n"}, 
		{"0data", this->quickViewStr("\n")}, 
		{"0header", "\n-----" + this->getName() + " Home Device Menu----- \n"},
		{"0intro", "Enter From the following:\n"},
		{"1", ": Toggle On Switch\n"},
		{"2", ": Rename Device  \n"},
		{"3", ": Display Current Readings  \n"},
		{"4", ": Display Historic Readings  \n"},
		{"D", ": Delete \n"},
	};
	

	map<char, function<bool()>> menuFunctions;
	menuFunctions['1'] = [this]() {cout << "\n Switching " << this->getOpositeOnValStr() << "\n"; this->switchOnVal(); return true;   };
	menuFunctions['2'] = [this]() {return this->rename(this->getHomeSystem()); };
	menuFunctions['3'] = [this]() {return this->displayCurrentData(); };
	menuFunctions['4'] = [this]() {return this->displayHistoricData(); };
	menuFunctions['D'] = [this]() {return this->getHomeSystem()->deleteDevice(this); };

	vector<string> ignoreHeader = { "0header", "0intro" , "0data" , "0Adataheader"};

	HomeSystemFunctions::menuDisplay<HomeDevice*>(menuDispaly, menuFunctions, this, ignoreHeader);
}

