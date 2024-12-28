
#include "models/Notification.h"
#include "utils/TimeUtils.h"

void Notification::send() const {
    // In a real implementation, this would integrate with an email/SMS service
    // For simulation, we'll just print to console
    std::cout << "\n=== Package Delivery Notification ===\n";
    std::cout << "Time: " << TimeUtils::getCurrentTime() << "\n";
    std::cout << "Dear Customer " << customerId << ",\n\n";
    std::cout << "Your package (Order: " << orderId << ") has been delivered to our locker facility.\n";
    std::cout << "Pickup Details:\n";
    std::cout << "- Locker ID: " << lockerId << "\n";
    std::cout << "- Access Code: " << code << "\n";
    std::cout << "- Valid for: 3 days from delivery\n";
    std::cout << "\nPlease collect your package within the validity period.\n";
    std::cout << "For security reasons, this code will expire after 3 days.\n";
    std::cout << "================================\n";
}
