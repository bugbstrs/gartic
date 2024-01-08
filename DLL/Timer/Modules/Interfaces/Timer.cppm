#pragma region module
export module Timer;

#pragma region Timer
import <chrono>;
import <cstdint>;
import <functional>;
import <mutex>;
import <thread>;
import <iostream>;
#pragma endregion imports

#pragma region Timer
using ConditionVariable = std::condition_variable;
using Milliseconds      = std::chrono::milliseconds;
using Mutex             = std::mutex;
using Thread            = std::thread;
using TimePoint         = std::chrono::steady_clock::time_point;
using TimerCallback     = std::function<void()>;

using namespace std::chrono_literals;
#pragma endregion using statements

#pragma region Timer
export const int defaultMinutes    = 1;
export const int defaultResolution = 12;
#pragma endregion constants

#pragma region Timer
export class Timer
{
#pragma region Timer
public:
    #pragma region Timer
    __declspec(dllexport) Timer ();
    __declspec(dllexport) Timer (uint16_t totalMinutes, Milliseconds timerResolution = 1ms);
    __declspec(dllexport) Timer (uint16_t initialMinutes, uint16_t remainingMinutes, Milliseconds timerResolution = 1ms);
    __declspec(dllexport) Timer (const Timer& newTimer);
    
    __declspec(dllexport) ~Timer ();
    #pragma endregion constructors & destructor

    #pragma region Timer
    __declspec(dllexport) void SetCallback        (TimerCallback callback);
    __declspec(dllexport) void SetInitialTime     (uint16_t minutes);
    __declspec(dllexport) void SetRemainingTime   (uint16_t minutes);
    __declspec(dllexport) void SetTimeoutCallback (TimerCallback timeoutCallback);
    __declspec(dllexport) void SetTimerResolution (uint32_t milliseconds);
    #pragma endregion setters
    
    #pragma region Timer
    __declspec(dllexport) double       GetRemainingTimePercentage () const;
    __declspec(dllexport) Milliseconds GetElapsedTime             () const;
    __declspec(dllexport) Milliseconds GetInitialTime             () const;
    __declspec(dllexport) Milliseconds GetRemainingTime           () const;
    __declspec(dllexport) Milliseconds GetTimerResolution         () const;
    #pragma endregion getters

    #pragma region Timer
    __declspec(dllexport) void ResetTimer     ();
    __declspec(dllexport) void StartTimer     ();
    __declspec(dllexport) void StartTimerFrom (Milliseconds customStartTime);
    __declspec(dllexport) void StopTimer      ();
    #pragma endregion timer flow: start, stop, reset, starttimerfrom
    
    #pragma region Timer
    __declspec(dllexport) bool IsTimeExpired ()  const;
    __declspec(dllexport) void Run           ();
    #pragma endregion functionality
#pragma endregion public members
#pragma region Timer
private:
    Thread m_thread;

    Mutex m_mutex;

    ConditionVariable m_conditionalVariable;

    bool m_isSuspended;

    Milliseconds m_initialTime;
    Milliseconds m_remainingTime;
    Milliseconds m_timerResolution;
    Milliseconds m_timeToDecrease;

    TimerCallback m_callback;
    TimerCallback m_timeoutCallback;
#pragma endregion private members
};
#pragma endregion class
#pragma endregion module