
# Add executable
add_executable(amazon_locker 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Package.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Locker.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Location.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Item.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Order.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Notification.cpp
    ${PROJECT_SOURCE_DIR}/src/models/GeoLocation.cpp
    ${PROJECT_SOURCE_DIR}/src/services/LockerService.cpp
    ${PROJECT_SOURCE_DIR}/src/services/OTPService.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/ConsoleUI.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/TimeUtils.cpp
)
