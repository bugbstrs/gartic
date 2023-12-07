#include "Time.h"

using namespace http;

Timer http::Time::m_serverTimer(10);

http::Time::Time(float newStartTimeStamp, float newStartValue, float newEndValue) : 
	m_startTimeStamp{newStartTimeStamp},
	m_startValue{newStartValue},
	m_endValue{newEndValue}
{
	m_serverTimer.StartTimer();
}

http::Time::Time(const Time& newTime) :
	m_startTimeStamp{newTime.m_startTimeStamp},
	m_startValue{newTime.m_startValue},
	m_endValue{newTime.m_endValue},
	m_toCall{newTime.m_toCall}
{
	m_serverTimer.StartTimer();
}

float http::Time::GetStartTimeStamp() const noexcept
{
	return m_startTimeStamp;
}

float http::Time::GetStartValue() const noexcept
{
	return m_startValue;
}

float http::Time::GetEndValue() const noexcept
{
	return m_endValue;
}

std::function<void()> http::Time::GetMethodToCall() const noexcept
{
	return m_toCall;
}

void http::Time::SetStartTimeStamp(float newTimeStamp)
{
	m_startTimeStamp = newTimeStamp;
}

void http::Time::SetStartValue(float newStartValue)
{
	m_startValue = newStartValue;
}

void http::Time::SetEndValue(float newEndValue)
{
	m_endValue = newEndValue;
}

void http::Time::SetMethodToCall(const std::function<void()>& methodToCall)
{
	m_toCall = methodToCall;
}

void http::Time::Start(float timeStamp, float startValue, float endValue)
{
	m_startTimeStamp = timeStamp;
	m_startValue = startValue;
	m_endValue = endValue;
}

// Momentan avem si constructor si start dar trebuie sa vedem la care sa renuntam ulterior in implementare

bool http::Time::Check()
{
	if ((m_startValue > m_endValue && static_cast<int>(m_serverTimer.GetElapsedTime().count()) - m_startTimeStamp >= m_endValue) || (m_startValue <= m_endValue && static_cast<int>(m_serverTimer.GetElapsedTime().count()) - m_startTimeStamp >= m_endValue))
	{
		m_toCall();
		return true;
	}

	return false;
}
