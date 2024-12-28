
#include <gtest/gtest.h>
#include "models/Locker.h"
#include "models/Package.h"

TEST(LockerTest, CreationTest) {
    Locker locker("L1", LockerSize::MEDIUM, "LOC1");
    EXPECT_EQ(locker.getId(), "L1");
    EXPECT_EQ(locker.getSize(), LockerSize::MEDIUM);
    EXPECT_EQ(locker.getLocationId(), "LOC1");
    EXPECT_TRUE(locker.isAvailable());
}

TEST(LockerTest, PackageOperations) {
    Locker locker("L1", LockerSize::MEDIUM, "LOC1");
    auto package = new LockerPackage("PKG1", 1500.0, "ORDER1", "L1", "123456");
    
    EXPECT_TRUE(locker.addPackage(package));
    EXPECT_FALSE(locker.isAvailable());
    EXPECT_EQ(locker.getCurrentPackage(), package);
    
    EXPECT_TRUE(locker.removePackage());
    EXPECT_TRUE(locker.isAvailable());
    EXPECT_EQ(locker.getCurrentPackage(), nullptr);
}
