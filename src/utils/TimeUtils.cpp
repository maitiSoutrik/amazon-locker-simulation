
#include "utils/TimeUtils.h"
#include <iomanip>
#include <sstream>

std::string TimeUtils::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool TimeUtils::isExpired(const std::chrono::system_clock::time_point& start, int days) {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - start);
    return duration.count() >= (days * 24);
}
