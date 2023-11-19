export module Timer;

#pragma region Timer
import <thread>;
import <mutex>;
import <chrono>;
import <cstdint>;
import <functional>;
#pragma endregion imports

#pragma region Timer
using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using Milliseconds = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;
using TimerCallback = std::function<void()>;

using namespace std::chrono_literals;
#pragma endregion using statements

#pragma region Timer
export const int defaultMinutes = 1;
export const int defaultResolution = 12;
#pragma endregion constants

export class __declspec(dllexport) Timer
{
public:
	#pragma region Timer
	Timer();
	Timer(uint16_t totalMinutes, Milliseconds timerResolution = 1ms);
	Timer(uint16_t initialMinutes, uint16_t remainingMinutes, Milliseconds timerResolution = 1ms);
	Timer(const Timer& newTimer);
	~Timer();
	#pragma endregion constructors & destructor

	#pragma region Timer
	void SetInitialTime(uint16_t minutes);
	void SetRemainingTime(uint16_t minutes);
	void SetTimerResolution(uint32_t milliseconds);
	void SetCallback(TimerCallback callback);
	void SetTimeoutCallback(TimerCallback timeoutCallback);
	#pragma endregion setters
	
	#pragma region Timer
	Milliseconds GetInitialTime() const;
	Milliseconds GetRemainingTime() const;
	Milliseconds GetTimerResolution() const;
	Milliseconds GetElapsedTime() const;
	double GetRemainingTimePercentage() const;
	#pragma endregion getters

	#pragma region Timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();
	void StartTimerFrom(Milliseconds customStartTime);
	#pragma endregion timer flow: start, stop, reset, starttimerfrom
	
	#pragma region Timer
	bool IsTimeExpired() const;
	void Run();
	#pragma endregion functionality

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