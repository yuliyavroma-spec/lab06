#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock_account.hpp"
#include "Transaction.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

class TransactionTest : public ::testing::Test {
protected:
    NiceMock<MockAccount>* from;
    NiceMock<MockAccount>* to;
    
    void SetUp() override {
        from = new NiceMock<MockAccount>("Alice", 1000.0);
        to = new NiceMock<MockAccount>("Bob", 500.0);
    }
    
    void TearDown() override {
        delete from;
        delete to;
    }
};
TEST_F(TransactionTest, ExecuteValidTransaction) {
    EXPECT_CALL(*from, GetBalance()).WillOnce(Return(1000.0));
    EXPECT_CALL(*from, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*to, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*from, ChangeBalance(-300.0)).Times(1);
    EXPECT_CALL(*to, ChangeBalance(300.0)).Times(1);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_TRUE(txn.Execute(*from, *to));
    EXPECT_TRUE(txn.IsExecuted());
}

TEST_F(TransactionTest, ExecuteFailsWhenSenderLocked) {
    EXPECT_CALL(*from, IsLocked()).WillOnce(Return(true));
    EXPECT_CALL(*from, ChangeBalance(_)).Times(0);
    EXPECT_CALL(*to, ChangeBalance(_)).Times(0);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_FALSE(txn.Execute(*from, *to));
    EXPECT_FALSE(txn.IsExecuted());
}
TEST_F(TransactionTest, ExecuteFailsWhenReceiverLocked) {
    EXPECT_CALL(*from, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*to, IsLocked()).WillOnce(Return(true));
    EXPECT_CALL(*from, ChangeBalance(_)).Times(0);
    EXPECT_CALL(*to, ChangeBalance(_)).Times(0);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_FALSE(txn.Execute(*from, *to));
}

TEST_F(TransactionTest, ExecuteFailsWithInsufficientFunds) {
    EXPECT_CALL(*from, GetBalance()).WillOnce(Return(100.0));
    EXPECT_CALL(*from, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*to, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*from, ChangeBalance(_)).Times(0);
    EXPECT_CALL(*to, ChangeBalance(_)).Times(0);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_FALSE(txn.Execute(*from, *to));
}
TEST_F(TransactionTest, CannotExecuteTwice) {
    EXPECT_CALL(*from, GetBalance()).WillOnce(Return(1000.0));
    EXPECT_CALL(*from, IsLocked()).WillRepeatedly(Return(false));
    EXPECT_CALL(*to, IsLocked()).WillRepeatedly(Return(false));
    EXPECT_CALL(*from, ChangeBalance(-300.0)).Times(1);
    EXPECT_CALL(*to, ChangeBalance(300.0)).Times(1);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_TRUE(txn.Execute(*from, *to));
    EXPECT_FALSE(txn.Execute(*from, *to));
}
TEST_F(TransactionTest, RollbackAfterExecution) {
    EXPECT_CALL(*from, GetBalance()).WillOnce(Return(1000.0));
    EXPECT_CALL(*from, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*to, IsLocked()).WillOnce(Return(false));
    EXPECT_CALL(*from, ChangeBalance(-300.0)).Times(1);
    EXPECT_CALL(*to, ChangeBalance(300.0)).Times(1);
    
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_TRUE(txn.Execute(*from, *to));
    EXPECT_TRUE(txn.Rollback());
    EXPECT_TRUE(txn.IsRolledBack());
}

TEST_F(TransactionTest, CannotRollbackWithoutExecution) {
    Transaction txn(300.0, "Alice", "Bob");
    EXPECT_FALSE(txn.Rollback());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
