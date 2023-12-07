#pragma once

#include <functional>

import Timer;

namespace http
{
	class Time
	{
	public:
		Time() = default;
		Time(float newStartTimeStamp, float newStartValue, float newEndValue);
		Time(const Time& newTime);

		~Time() = default;

		float GetStartTimeStamp() const noexcept;
		float GetStartValue() const noexcept;
		float GetEndValue() const noexcept;

		std::function<void()> GetMethodToCall() const noexcept;

		void SetMethodToCall(const std::function<void()>& methodToCall);

		void Start(float timeStamp, float startValue, float endValue);

		bool Check();

	private:
		float m_startTimeStamp;
		float m_startValue;
		float m_endValue;
		
		std::function<void()> m_toCall;

		static Timer m_serverTimer;
	};
}

