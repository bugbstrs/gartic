#include "Time.h"

using namespace http;

Timer http::Time::m_serverTimer(10);
namespace http {
	std::vector<Time*> Time::m_timers;
}

http::Time::Time(float newStartTimeStamp, float newStartValue, float newEndValue) : 
	m_startTimeStamp{newStartTimeStamp},
	m_startValue{newStartValue},
	m_endValue{newEndValue},
	m_currentPlayerToRemove{""}
{
	m_serverTimer.StartTimer();
	m_timers.push_back(this);
}

http::Time::Time(const Time& newTime) :
	m_startTimeStamp{newTime.m_startTimeStamp},
	m_startValue{newTime.m_startValue},
	m_endValue{newTime.m_endValue},
	m_toCall{newTime.m_toCall},
	m_currentPlayerToRemove{""}
{
	m_serverTimer.StartTimer();
	m_timers.push_back(this);
}

http::Time::~Time()
{
	if (auto it = std::find(m_timers.begin(), m_timers.end(), this);  it != m_timers.end()) {
		m_timers.erase(it);
	}
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

int http::Time::GetServerTime() const noexcept
{
	return static_cast<int>(m_serverTimer.GetElapsedTime().count());
}

const std::function<void()>& http::Time::GetMethodToCall() const noexcept
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

	//m_currentPlayerToRemove = nameToRemove;
}

void http::Time::Start(float timeStamp, float startValue, float endValue)
{
	m_startTimeStamp = timeStamp;
	m_startValue = startValue;
	m_endValue = endValue;
}

bool http::Time::Check()
{
	if ((m_startValue > m_endValue && static_cast<int>(m_serverTimer.GetElapsedTime().count()) - m_startTimeStamp >= m_endValue) || (m_startValue <= m_endValue && static_cast<int>(m_serverTimer.GetElapsedTime().count()) - m_startTimeStamp >= m_endValue))
	{
		m_toCall();
		return true;
	}

	return false;
}

void http::Time::CheckTimers()
{
	auto myLambda = []() {
		while (true) {
			for (auto& time : m_timers) {
				time->Check();
			}
		}
	};
	std::thread myThread(myLambda);
	myThread.detach();
}

Time http::Time::operator=(const Time& t1)
{
	this->m_startTimeStamp = t1.m_startTimeStamp;
	this->m_startValue = t1.m_startValue;
	this->m_endValue = t1.m_endValue;
	m_toCall = t1.m_toCall;

	//SetMethodToCall(t1.m_toCall, t1.m_currentPlayerToRemove);

	this->m_currentPlayerToRemove = t1.m_currentPlayerToRemove;

	return *this;
}
