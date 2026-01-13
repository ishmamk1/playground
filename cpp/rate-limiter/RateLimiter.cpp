#include "RateLimiter.h"

RateLimiter::RateLimiter(int capacity, Duration window)
    : capacity(capacity), window_length(window), start_time(std::chrono::steady_clock::now()), current_requests(0) {}

bool RateLimiter::Request() {

    // Adjust window if it exceeds the time
    TimePoint current_time = std::chrono::steady_clock::now();

    if (current_time - start_time > window_length) {
        start_time = current_time;
        current_requests = 0;
    }

    if (current_requests == capacity) {
        return false;
    } else {
        current_requests += 1;

        return true;
    }
}