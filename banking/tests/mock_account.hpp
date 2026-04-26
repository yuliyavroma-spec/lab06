#ifndef MOCK_ACCOUNT_HPP
#define MOCK_ACCOUNT_HPP

#include <gmock/gmock.h>
#include "Account.hpp"

class MockAccount : public Account {
public:
    MockAccount(const std::string& owner, double balance) : Account(owner, balance) {}
    
    ~MockAccount() override = default;
    
    MOCK_METHOD(const std::string&, GetOwner, (), (const));
    MOCK_METHOD(double, GetBalance, (), (const));
    MOCK_METHOD(void, ChangeBalance, (double amount));
    MOCK_METHOD(void, Lock, ());
    MOCK_METHOD(void, Unlock, ());
    MOCK_METHOD(bool, IsLocked, (), (const));
};

#endif
