export module Timer;

import <thread>;
import <mutex>;
import <chrono>;

export import config;

using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using Milliseconds = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;

using namespace std::chrono_literals;

export class Timer
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

	// Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();

	// Functionality
	bool IsTimeExpired() const;

	void Run();

private:
	Thread m_thread;

	Mutex m_mutex;

	ConditionVariable m_conditionalVariable;

	bool m_isSuspended;

	Milliseconds m_initialTime;
	Milliseconds m_remainingTime;
	Milliseconds m_timerResolution;
	Milliseconds m_timeToDecrease;
};