#pragma once
#include <iostream> 
#include <thread>
#include <functional>
#include <vector>
#include <mutex>
// using knowledge learnt from https://en.cppreference.com/w/cpp/thread
class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();
	template<typename FuncType, typename objectType, typename... ParamType>
	bool createThread(FuncType&& function, objectType* objectPtr, ParamType...params);
private:
	const unsigned int MAX_THREADS;
	std::vector<std::thread> activeThreads;
	std::atomic<bool> stopFlag;
	std::mutex mutex; 

};
template<typename FuncType, typename objectType, typename... ParamType>
bool ThreadManager::createThread(FuncType&& function, objectType* objectPtr, ParamType...params) {
	if ( activeThreads.size() < MAX_THREADS-1) { // keaping one open for creating threads
		mutex.lock(); // locking so threads are'nt created at the  same time
		// create thread and add to vector
		activeThreads.emplace_back(std::thread(std::forward<FuncType>(function), objectPtr, std::forward<ParamType>(params)...));
		mutex.unlock(); 
		return true; 
	}
	else {
		return false;
	}

}
