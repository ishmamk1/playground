#include <iostream>
#include <thread>   // for std::this_thread::sleep_for
#include "RateLimiter.h"

int main() {
    // Create a rate limiter: max 3 requests per 2 seconds
    RateLimiter limiter(7, std::chrono::seconds(2));

    for (int i = 1; i <= 5; ++i) {
        if (limiter.Request()) {
            std::cout << "Request " << i << " allowed\n";
        } else {
            std::cout << "Request " << i << " blocked\n";
        }
    }

    std::cout << "Waiting for window to reset...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Try again after window reset
    for (int i = 6; i <= 8; ++i) {
        if (limiter.Request()) {
            std::cout << "Request " << i << " allowed\n";
        } else {
            std::cout << "Request " << i << " blocked\n";
        }
    }

    return 0;
}
