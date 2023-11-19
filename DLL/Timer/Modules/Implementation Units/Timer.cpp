module Timer;

static Milliseconds ConvertToMilliseconds(uint16_t time, bool isInMinutes)
{
	return isInMinutes ? Milliseconds(time * 60000)
					   : Milliseconds(time * 1000);
}

static Milliseconds CurrentTimeInMillis(const TimePoint& initialTime)
{
	auto currentTime = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<Milliseconds>(currentTime - initialTime);
}

Timer::Timer():
	m_initialTime	  { ConvertToMilliseconds(defaultMinutes, true)    },
	m_remainingTime	  { m_initialTime								   },
	m_timerResolution { ConvertToMilliseconds(defaultResolution, true) },
	m_timeToDecrease  { 0ms											   },
	m_isSuspended	  { false										   }
{}

Timer::Timer(uint16_t totalMinutes, Milliseconds timerResolution):
	m_initialTime	  { ConvertToMilliseconds(totalMinutes, true) },
	m_remainingTime	  { m_initialTime							  },
	m_timerResolution { timerResolution							  },
	m_timeToDecrease  { 0ms										  },
	m_isSuspended	  { false									  }
{}

Timer::Timer(const Timer& newTimer):
	m_initialTime	  { newTimer.m_initialTime	   },
	m_remainingTime	  { newTimer.m_remainingTime   },
	m_timerResolution { newTimer.m_timerResolution },
	m_timeToDecrease  { 0ms						   },
	m_isSuspended	  { newTimer.m_isSuspended	   }
{}

Timer::~Timer()
{
	m_conditionalVariable.notify_one();

	if (m_thread.joinable()) m_thread.join();
}

void Timer::SetInitialTime(uint16_t minutes)
{
	m_initialTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetRemainingTime(uint16_t minutes)
{
	m_remainingTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetTimerResolution(uint32_t milliseconds)
{
	m_timerResolution = Milliseconds(milliseconds);
}

void Timer::SetCallback(TimerCallback callback)
{
	m_callback = callback;
}

void Timer::SetTimeoutCallback(TimerCallback timeoutCallback)
{
	m_timeoutCallback = timeoutCallback;
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

Milliseconds Timer::GetElapsedTime() const
{
	return m_initialTime - m_remainingTime;
}

double Timer::GetRemainingTimePercentage() const
{
	if (m_initialTime == 0ms) return 0.0;

	return static_cast<double>(m_remainingTime.count() / m_initialTime.count()) * 100.0;
}

void Timer::StartTimer()
{
	m_isSuspended = false;

	m_conditionalVariable.notify_all();

	if (!m_thread.joinable())
	{
		m_thread = Thread(&Timer::Run, this);
	}
}

void Timer::StopTimer()
{
	m_isSuspended = true;

	m_conditionalVariable.notify_all();
}

void Timer::ResetTimer()
{
	m_remainingTime = m_initialTime;
}

void Timer::StartTimerFrom(Milliseconds customStartTime)
{
	if (customStartTime <= 0ms) return;

	m_remainingTime = customStartTime;

	this->StartTimer();
}

bool Timer::IsTimeExpired() const
{
	return m_remainingTime <= Milliseconds(0);
}

void Timer::Run()
{
	while (!m_isSuspended)
	{
		auto initialTime = std::chrono::steady_clock::now();

		std::unique_lock lock(m_mutex);
		m_conditionalVariable.wait_for(lock, m_timerResolution, [&] { return !m_isSuspended; });

		auto elapsedTime	  =  CurrentTimeInMillis(initialTime);
			 m_timeToDecrease += elapsedTime;

		initialTime = std::chrono::steady_clock::now();

		auto& remainingTime = m_remainingTime;
			  remainingTime = elapsedTime < remainingTime 
							? remainingTime - elapsedTime
							: 0ms;

		if (IsTimeExpired())
		{
			StopTimer();
		}
	}
}