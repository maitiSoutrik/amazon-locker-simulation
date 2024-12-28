
#pragma once
#include <chrono>
#include <string>

class TimeUtils {
public:
    static std::string getCurrentTime();
    static bool isExpired(const std::chrono::system_clock::time_point& start, int days);
};
