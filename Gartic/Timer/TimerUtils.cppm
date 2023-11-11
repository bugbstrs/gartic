export module TimerUtils;

import <thread>;
import <mutex>;
import <chrono>;

using Thread = std::thread;
using Mutex = std::mutex;
using ConditionVariable = std::condition_variable;
using Milliseconds = std::chrono::milliseconds;
using TimePoint = std::chrono::steady_clock::time_point;

export const int defaultMinutes = 1;
export const int defaultResolution = 12;