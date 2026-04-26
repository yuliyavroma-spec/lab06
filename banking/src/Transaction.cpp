#include "Transaction.hpp"

Transaction::Transaction(double amount, const std::string& sender, const std::string& receiver)
    : amount(amount), sender_id(sender), receiver_id(receiver), executed(false), rolled_back(false) {}

bool Transaction::Execute(Account& from, Account& to) {
    if (executed || rolled_back) {
        return false;
    }
    
    if (from.IsLocked() || to.IsLocked()) {
        return false;
    }
    
    if (from.GetBalance() < amount) {
        return false;
    }
    
    from.ChangeBalance(-amount);
    to.ChangeBalance(amount);
    executed = true;
    return true;
}
bool Transaction::Rollback() {
    if (!executed || rolled_back) {
        return false;
    }
    rolled_back = true;
    executed = false;
    return true;
}

bool Transaction::IsExecuted() const {
    return executed;
}

bool Transaction::IsRolledBack() const {
    return rolled_back;
}
