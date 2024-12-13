#include<iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include"HomeDevice.h"
#include"HomeSystem.h"
#include"HomeSystemFunctions.h"
using namespace std;


int main() {
	// check memory leaks 
#ifdef _DEBUG
	// _CrtSetBreakAlloc(x);
	_onexit(_CrtDumpMemoryLeaks);

#endif
	

	// main program
	HomeSystem* test = new HomeSystem("test");
	test->menu();


	// --- tests --
	/*string testStr = ""; 
	cout << HomeSystemFunctions::trim(testStr); */

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