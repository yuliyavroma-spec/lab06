#include <gtest/gtest.h>
#include "Account.hpp"

TEST(AccountTest, ConstructorInitializesCorrectly) {
    Account acc("John Doe", 1000.0);
    
    EXPECT_EQ(acc.GetOwner(), "John Doe");
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 1000.0);
    EXPECT_FALSE(acc.IsLocked());
}

TEST(AccountTest, ConstructorDefaultBalance) {
    Account acc("Jane Doe");
    
    EXPECT_EQ(acc.GetOwner(), "Jane Doe");
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 0.0);
}
TEST(AccountTest, ChangeBalanceWhenUnlocked) {
    Account acc("Test", 500.0);
    
    acc.ChangeBalance(200.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 700.0);
    
    acc.ChangeBalance(-100.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 600.0);
}

TEST(AccountTest, ChangeBalanceWhenLockedDoesNothing) {
    Account acc("Test", 500.0);
    acc.Lock();
    
    acc.ChangeBalance(200.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 500.0);
}
TEST(AccountTest, LockUnlock) {
    Account acc("Test", 100.0);
    
    EXPECT_FALSE(acc.IsLocked());
    acc.Lock();
    EXPECT_TRUE(acc.IsLocked());
    acc.Unlock();
    EXPECT_FALSE(acc.IsLocked());
}
