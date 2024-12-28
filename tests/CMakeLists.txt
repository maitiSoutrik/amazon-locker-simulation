
# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(amazon_locker_test 
    locker_test.cpp
    package_test.cpp
    location_test.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Package.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Locker.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Location.cpp
    ${PROJECT_SOURCE_DIR}/src/models/GeoLocation.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Item.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Order.cpp
    ${PROJECT_SOURCE_DIR}/src/models/Notification.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/TimeUtils.cpp
)

target_link_libraries(amazon_locker_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(amazon_locker_test)
