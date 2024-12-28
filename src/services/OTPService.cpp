
#include "services/OTPService.h"
#include <random>
#include <sstream>
#include <iomanip>

std::string OTPService::generateOTP() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 999999);
    
    std::stringstream ss;
    ss << std::setw(6) << std::setfill('0') << dis(gen);
    return ss.str();
}

bool OTPService::validateOTP(const std::string& input, const std::string& stored) {
    return input == stored;
}
