#pragma once

#include<thread>
#include<mutex>
#include<chrono>

import Config;

using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using AtomicBool = std::atomic<bool>;
using Milliseconds = std::chrono::milliseconds;

using namespace std::chrono_literals;

class Timer
{
public:
	// Constructors
	Timer();
	Timer(int totalMinutes, Milliseconds timerResolution = 1ms);
	Timer(const Timer& newTimer);

	// Destructor
	~Timer();

	// Setters
	void SetInitialTime(int minutes);
	void SetRemainingTime(int minutes);
	void SetTimerResolution(int milliseconds);

	// Getters
	Milliseconds GetInitialTime() const;
	Milliseconds GetRemainingTime() const;
	Milliseconds GetTimerResolution() const;

private:
	Milliseconds m_initialTime;
	Milliseconds m_remainingTime;
	Milliseconds m_timerResolution;
};
