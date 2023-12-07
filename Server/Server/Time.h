#pragma once

#include <functional>

namespace http
{
	class Time
	{
	public:
		Time() = default;
		Time(float newStartTimeStamp, float newStartValue, float newEndValue);

		~Time() = default;

		void Start(float timeStamp, float startValue, float endValue);

		bool Check();

	private:
		float m_startTimeStamp;
		float m_startValue;
		float m_endValue;
		std::function<void()> m_toCall;
	};
}

