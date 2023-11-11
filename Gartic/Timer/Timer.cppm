export module Timer;

import <thread>;
import <mutex>;
import <chrono>;
import <cstdint>;
import <functional>;

using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using Milliseconds = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;
using TimerCallback = std::function<void()>;

using namespace std::chrono_literals;

export const int defaultMinutes = 1;
export const int defaultResolution = 12;

export class __declspec(dllexport) Timer
{
public:
	// Constructors
	Timer();
	Timer(uint16_t totalMinutes, Milliseconds timerResolution = 1ms);
	Timer(const Timer& newTimer);

	// Destructor
	~Timer();

	// Setters
	void SetInitialTime(uint16_t minutes);
	void SetRemainingTime(uint16_t minutes);
	void SetTimerResolution(uint32_t milliseconds);
	void SetCallback(TimerCallback callback);
	void SetTimeoutCallback(TimerCallback timeoutCallback);

	// Getters
	Milliseconds GetInitialTime() const;
	Milliseconds GetRemainingTime() const;
	Milliseconds GetTimerResolution() const;
	Milliseconds GetElapsedTime() const;

	// Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	void StartTimerFrom(Milliseconds customStartTime);

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

	TimerCallback m_callback;
	TimerCallback m_timeoutCallback;
};