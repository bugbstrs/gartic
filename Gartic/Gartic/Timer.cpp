#include "Timer.h"

using namespace std::chrono_literals;

Timer::Timer(int totalMinutes, Milliseconds timerResolution)
	: m_initialTime(totalMinutes * 60)
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
