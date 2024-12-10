#include "HomeSystemFunctions.h"


// devolped with help form MS co pilate  
bool HomeSystemFunctions::canConvertToFloat(const string& str) {
	try { 
		stof(str); return true; 
	} 
	catch (const invalid_argument&) 
	{ 
		return false;

	} 
	catch (const out_of_range&) { 
		return false; 
	} 
}