#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <thread>

import Timer;

using namespace std::chrono_literals;

namespace http
{
	class Time
	{
	public:
		Time() = delete;
		Time(int duration, bool start = true);
		Time(const Time& newTime);

		~Time();

		int GetDuration() const noexcept;
		int GetRemainingTime() const noexcept;

		void SetDuration(int newDuration);

		template <typename FuncType, typename... Args>
		void SetMethodToCall(FuncType methodToCall, Args&&... args)
		{
			m_toCall = std::bind(methodToCall, std::forward<Args>(args)...);
		}

		void CallFunction();
		void Start();
		void Stop();
		void Reset();

		bool Check();

		static void CheckTimers();
		static int GetServerTime() noexcept;

		Time operator = (const Time& t1);

	private:
		int m_startTimeStamp;
		int m_duration;
		int m_elapsedTime;
		bool m_functionActivated;
		bool m_started;
		
		std::function<void()> m_toCall;

		static Timer m_serverTimer;
		static std::vector<Time*> m_timers;
	};
}
