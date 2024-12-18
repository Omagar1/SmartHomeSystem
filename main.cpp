#include<iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include"HomeDevice.h"
#include"HomeSystem.h"
#include"HomeSystemFunctions.h"
using namespace std;

//void runTests() {
//	std::vector<HomeDevice*> devices = { 
//		new HomeDevice("Alpha" , nullptr), 
//		new HomeDevice("Beta" , nullptr),
//		new HomeDevice("Gamma", nullptr),
//		new HomeDevice("alpha", nullptr),
//		new HomeDevice("beta", nullptr),
//		new HomeDevice("gamma", nullptr)
//	}; 
//	for (size_t i = 0; i < devices.size(); ++i) {
//		for (size_t j = 0; j < devices.size(); ++j) { 
//			std::cout << "Comparing " << (*devices[i]).getName() << " < " << (*devices[j]).getName() << ": " << (*devices[i] < *devices[j] ? "true" : "false") << std::endl;
//		}
//	}
//}


int main() {
	// check memory leaks 
#ifdef _DEBUG
	// _CrtSetBreakAlloc(x);
	_onexit(_CrtDumpMemoryLeaks);

#endif
	

	// main program
	HomeSystem* test = new HomeSystem("test","C:/Users/josia/Documents/UNI Stuff/CS/24 25/Advanced Programing/SmartHomeSystem/RuntimeFiles/",true);
	test->menu();


	// --- tests --

	/*runTests(); */

	/*string testStr = "Hello World Its So Good to be here"; 
	vector<string> testVector = HomeSystemFunctions::split(testStr, ' ');
	for (string str : testVector) {
		cout << str << "\n"; 
	}*/

	//string testData1[] = { "\n-----Test 1: Home Smart System Menu----- \n", 
	//	"Enter From the following:\n", 
	//	"1 : List devices \n", 
	//	"2 : Sort by name \n", 
	//	"3 : Sort by device type (by name as secondary order) \n", 
	//	"4 [device name] : Select device to interact with its full feature set \n", 
	//	"5 : Add device \n", 
	//	"9 : Exit \n", "Input: " 
	//};
	////HomeSystemFunctions::displayOptions(testData1); 

	//unordered_map<string, function<bool()>> menuFunctions;
	//menuFunctions["option0"] = &(HomeSystemFunctions::notDevelopedYet); 
	//menuFunctions["option0"]();

	// memory managemnt
	delete(test); 
	test = nullptr;
	return 0; 
}