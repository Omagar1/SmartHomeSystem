#include "ThreadManager.h"
ThreadManager::ThreadManager(): MAX_THREADS(std::thread::hardware_concurrency()) {
	this->activeThreads = std::vector<std::thread>();
	this->stopFlag = false; 
}
ThreadManager::~ThreadManager() {
	this->stopFlag = true; 
	for (std::thread& t : activeThreads) {
		if (t.joinable()) { 
			t.join(); 
		}
	}
}