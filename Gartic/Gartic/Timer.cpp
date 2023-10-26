#include "Timer.h"

static Milliseconds ConvertToMilliseconds(int time, bool isInMinutes)
{
	return isInMinutes ? Milliseconds(time * 60000) : Milliseconds(time * 1000);
}

Timer::Timer()
	: m_initialTime(ConvertToMilliseconds(Config::defaultMinutes, true))
	, m_remainingTime(m_initialTime)
	, m_timerResolution(ConvertToMilliseconds(Config::defaultResolution))
{
}

Timer::Timer(int totalMinutes, Milliseconds timerResolution)
	: m_initialTime(ConvertToMilliseconds(totalMinutes, true))
	, m_remainingTime(m_initialTime)
	, m_timerResolution(timerResolution)
{
}

Timer::Timer(const Timer& newTimer)
	: m_initialTime(newTimer.m_initialTime)
	, m_remainingTime(newTimer.m_remainingTime)
	, m_timerResolution(newTimer.m_timerResolution)
{
}

Timer::~Timer()
{
}

void Timer::SetInitialTime(int minutes)
{
	m_initialTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetRemainingTime(int minutes)
{
	m_remainingTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetTimerResolution(int milliseconds)
{
	m_timerResolution = Milliseconds(milliseconds);
}

Milliseconds Timer::GetInitialTime() const
{
	return m_initialTime;
}

Milliseconds Timer::GetRemainingTime() const
{
	return m_remainingTime;
}

Milliseconds Timer::GetTimerResolution() const
{
	return m_timerResolution;
}
