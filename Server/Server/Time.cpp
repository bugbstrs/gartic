#include "Time.h"

using namespace http;


Timer http::Time::m_serverTimer(1440);//one day

std::vector<Time*> http::Time::m_timers;


http::Time::Time(int duration) :
	m_startTimeStamp{ GetServerTime() },
	m_duration{ duration },
	m_currentPlayerToRemove{ "" }
{
	m_timers.push_back(this);
}

http::Time::Time(const Time& newTime) :
	m_startTimeStamp{ newTime.m_startTimeStamp },
	m_duration{ newTime.m_duration },
	m_toCall{ newTime.m_toCall },
	m_currentPlayerToRemove{ newTime.m_currentPlayerToRemove }
{
	m_timers.push_back(this);
}

http::Time::~Time()
{
	if (auto it = std::find(m_timers.begin(), m_timers.end(), this);  it != m_timers.end())
		m_timers.erase(it);
}

int http::Time::GetDuration() const noexcept
{
	return m_duration;
}

int http::Time::GetRemainingTime() const noexcept
{
	int remainingTime = m_duration - GetServerTime() + m_startTimeStamp;
	return remainingTime >= 0 ? remainingTime : 0;
}

void http::Time::SetDuration(int newDuration)
{
	m_duration = newDuration;
}

void http::Time::Reset()
{
	m_startTimeStamp = GetServerTime();
}

bool http::Time::Check()
{
	if(GetRemainingTime() == 0)
	{
		if(m_toCall)
			m_toCall();
		return true;
	}
	return false;
}
#include <Windows.h>
#include <iostream>
void http::Time::CheckTimers()
{
	m_serverTimer.StartTimer();

	std::thread([]()
	{
		while (true)
		{
			std::vector<Time*> localTimers = m_timers;
			for (auto& timer : localTimers)
				if (timer != nullptr)
					timer->Check();

			std::cout << GetServerTime()<<" ";
			Sleep(1000);
		}
	}).detach();
}

int http::Time::GetServerTime() noexcept
{
	return static_cast<int>(m_serverTimer.GetElapsedTime().count());
}

Time http::Time::operator=(const Time& t1)
{
	this->m_startTimeStamp = t1.m_startTimeStamp;
	this->m_duration = t1.m_duration;
	this->m_toCall = t1.m_toCall;
	this->m_currentPlayerToRemove = t1.m_currentPlayerToRemove;

	return *this;
}