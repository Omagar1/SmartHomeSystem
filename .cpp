#include "CommonFunctions.h"
vector<string>* CommonFunctions::split(string strToSlpit, char delimiter) {
	vector<string>* newVector = new vector<string>();
	int indexNewItem = 0;
	for(int i = 0; i <= strToSlpit.size(); i++){
		if (i == strToSlpit.size() || strToSlpit[i] == delimiter) {
			string subStr;
			// creating new substring
			for (int j = indexNewItem; j < i; j++) {
				subStr += strToSlpit[j]; 
			}
			// adding to vector
			newVector->push_back(subStr);
			indexNewItem = i + 1;
		}
		
	}
	return newVector;
}