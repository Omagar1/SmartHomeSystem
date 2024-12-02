#include "SleepDevice.h"
void SleepDevice::quickView() {
	
}

void SleepDevice::setSleepTimer(time_t start, time_t end) {
	// add error handerling? 
	gmtime_s(this->sleepFrom, &start);
	gmtime_s(this->sleepUntil, &end);
}
void SleepDevice::setSleepTimer(time_t end) {
	time_t start = time(NULL);
	setSleepTimer(start, end);
	this->setOnVal(false); // as start is set to current time
}






//if (mktime(this->sleepUntil) < time(NULL) && mktime(this->sleepUntil) > time(NULL)) {
//	this->on = false;
//}
//else {
//	this->on = true;
//}