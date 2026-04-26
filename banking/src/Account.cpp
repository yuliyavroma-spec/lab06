#include "Account.hpp"

Account::Account(const std::string& owner, double initial_balance)
    : owner(owner), balance(initial_balance), locked(false) {}

const std::string& Account::GetOwner() const {
    return owner;
}

double Account::GetBalance() const {
    return balance;
}

void Account::ChangeBalance(double amount) {
    if (!locked) {
        balance += amount;
    }
}


void Account::Lock() {
    locked = true;
}

void Account::Unlock() {
    locked = false;
}

bool Account::IsLocked() const {
    return locked;
}
