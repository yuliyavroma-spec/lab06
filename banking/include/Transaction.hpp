#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include "Account.hpp"

class Transaction {
private:
    double amount;
    std::string sender_id;
    std::string receiver_id;
    bool executed;
    bool rolled_back;

public:
    Transaction(double amount, const std::string& sender, const std::string& receiver);
    
    bool Execute(Account& from, Account& to);
    bool Rollback();
    bool IsExecuted() const;
    bool IsRolledBack() const;
};

#endif
