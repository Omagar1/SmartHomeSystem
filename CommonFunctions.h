#pragma once
#include<iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include"HomeDevice.h"
#include"HomeSystem.h"
#include"HomeSystemFunctions.h"
using namespace std;

static class CommonFunctions
{
public:
	static vector<string>* split(string strToSlpit, char delimiter);
};
