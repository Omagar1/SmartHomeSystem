#include "ThreadManager.h"
ThreadManager::ThreadManager(): MAX_THREADS(std::thread::hardware_concurrency()-1) { // -1 as main thread is already in use
	this->activeThreads = std::vector<std::thread>();
	this->stopFlag = false; 
}
ThreadManager::~ThreadManager() {
	this->stopFlag = true;
	std::cout << "\n --- Waiting For Threads to Finish Up --- \n "; 
	for (std::thread& t : activeThreads) {
		if (t.joinable()) { 
			t.join(); 
		}
	}
}