#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <chrono>
#include <iostream>

using Duration = std::chrono::steady_clock::duration;
using TimePoint = std::chrono::steady_clock::time_point;

class RateLimiter {
    public:
        RateLimiter(int capacity, Duration window);
        bool Request();
    private:
        int capacity;
        Duration window_length;
        TimePoint start_time;
        int current_requests;
};

#endif