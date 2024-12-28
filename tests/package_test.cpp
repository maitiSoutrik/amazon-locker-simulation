
#include <gtest/gtest.h>
#include "models/Package.h"

TEST(PackageTest, CreationTest) {
    LockerPackage package("PKG1", 1500.0, "ORDER1", "L1", "123456");
    EXPECT_EQ(package.getId(), "PKG1");
    EXPECT_EQ(package.getSize(), 1500.0);
    EXPECT_EQ(package.getOrderId(), "ORDER1");
    EXPECT_EQ(package.getLockerId(), "L1");
}

TEST(PackageTest, CodeVerification) {
    LockerPackage package("PKG1", 1500.0, "ORDER1", "L1", "123456");
    EXPECT_TRUE(package.verifyCode("123456"));
    EXPECT_FALSE(package.verifyCode("wrong_code"));
}
