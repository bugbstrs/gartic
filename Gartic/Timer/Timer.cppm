export module Timer;

import <cstdint>;

export import TimerUtils;

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