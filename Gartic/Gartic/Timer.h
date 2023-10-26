#pragma once

#include<thread>
#include<mutex>
#include<chrono>

using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using AtomicBool = std::atomic<bool>;
using Milliseconds = std::chrono::milliseconds;

class Timer
{
public:
	// Constructors
	Timer(int totalMinutes, Milliseconds timerResolution = 1ms);
	Timer(const Timer& newTimer);

	// Destructor
	~Timer();

private:
	Milliseconds m_initialTime;
	Milliseconds m_remainingTime;
	Milliseconds m_timerResolution;
};
