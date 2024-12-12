#include "Schedule.h"

void Schedule::setSchedule(time_t start, time_t end) {
	// add error handerling? 
	gmtime_s(this->sleepFrom, &start);
	gmtime_s(this->sleepUntil, &end);
}
void Schedule::setSchedule(time_t end) {
	time_t start = time(NULL);
	setSchedule(start, end);
	this->setOnVal(false); // as start is set to current time
}