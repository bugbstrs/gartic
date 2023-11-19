#pragma region Timer
module Timer;

#pragma region Timer
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
#pragma endregion static methods

#pragma region Timer
Timer::Timer():
    m_initialTime     { ConvertToMilliseconds(defaultMinutes, true)    },
    m_remainingTime   { m_initialTime                                  },
    m_timerResolution { ConvertToMilliseconds(defaultResolution, true) },
    m_timeToDecrease  { 0ms                                            },
    m_isSuspended     { false                                          }
{}

Timer::Timer(uint16_t totalMinutes, Milliseconds timerResolution):
    m_initialTime     { ConvertToMilliseconds(totalMinutes, true) },
    m_remainingTime   { m_initialTime                             },
    m_timerResolution { timerResolution                           },
    m_timeToDecrease  { 0ms                                       },
    m_isSuspended     { false                                     }
{}

Timer::Timer(const Timer& newTimer):
    m_initialTime     { newTimer.m_initialTime     },
    m_remainingTime   { newTimer.m_remainingTime   },
    m_timerResolution { newTimer.m_timerResolution },
    m_timeToDecrease  { 0ms                        },
    m_isSuspended     { newTimer.m_isSuspended     }
{}

Timer::~Timer()
{
    m_conditionalVariable.notify_one();

    if (m_thread.joinable()) m_thread.join();
}
#pragma endregion constructors & destructor

#pragma region Timer
void Timer::SetCallback(TimerCallback callback)
{
    m_callback = callback;
}

void Timer::SetInitialTime(uint16_t minutes)
{
    m_initialTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetRemainingTime(uint16_t minutes)
{
    m_remainingTime = ConvertToMilliseconds(minutes, true);
}

void Timer::SetTimeoutCallback(TimerCallback timeoutCallback)
{
    m_timeoutCallback = timeoutCallback;
}

void Timer::SetTimerResolution(uint32_t milliseconds)
{
    m_timerResolution = Milliseconds(milliseconds);
}
#pragma endregion setters

#pragma region Timer
Milliseconds Timer::GetRemainingTime() const
{
    return m_remainingTime;
}

Milliseconds Timer::GetElapsedTime() const
{
    return m_initialTime - m_remainingTime;
}

Milliseconds Timer::GetInitialTime() const
{
    return m_initialTime;
}

double Timer::GetRemainingTimePercentage() const
{
    if (m_initialTime == 0ms) return 0.0;

    return static_cast<double>(m_remainingTime.count() / m_initialTime.count()) * 100.0;
}

Milliseconds Timer::GetTimerResolution() const
{
    return m_timerResolution;
}
#pragma endregion getters

#pragma region Timer
void Timer::ResetTimer()
{
    m_remainingTime = m_initialTime;
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

void Timer::StartTimerFrom(Milliseconds customStartTime)
{
    if (customStartTime <= 0ms) return;

    m_remainingTime = customStartTime;

    this->StartTimer();
}

void Timer::StopTimer()
{
    m_isSuspended = true;

    m_conditionalVariable.notify_all();
}
#pragma endregion timer flow: start, stop, reset, starttimerfrom

#pragma region Timer
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

        auto elapsedTime      =  CurrentTimeInMillis(initialTime);
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
#pragma endregion functionality
#pragma endregion module