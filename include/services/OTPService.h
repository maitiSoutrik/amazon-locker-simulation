
#pragma once
#include <string>

class OTPService {
public:
    static std::string generateOTP();
    static bool validateOTP(const std::string& input, const std::string& stored);
};
