
#include <gtest/gtest.h>
#include "models/Location.h"

TEST(LocationTest, CreationTest) {
    auto location = std::make_unique<LockerLocation>("LOC1", 37.7749, -122.4194);
    EXPECT_EQ(location->getId(), "LOC1");
    EXPECT_DOUBLE_EQ(location->getLatitude(), 37.7749);
    EXPECT_DOUBLE_EQ(location->getLongitude(), -122.4194);
}

TEST(LocationTest, LockerManagement) {
    auto location = std::make_unique<LockerLocation>("LOC1", 37.7749, -122.4194);
    auto locker = new Locker("L1", LockerSize::MEDIUM, "LOC1");
    
    location->addLocker(locker);
    auto& lockers = location->getLockers();
    EXPECT_EQ(lockers.size(), 1);
    EXPECT_EQ(lockers[0]->getId(), "L1");
}
