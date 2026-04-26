#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Account {
private:
    std::string owner;
    double balance;
    bool locked;

public:
    Account(const std::string& owner, double initial_balance = 0);
    virtual ~Account() = default;
    
    virtual const std::string& GetOwner() const;
    virtual double GetBalance() const;
    virtual void ChangeBalance(double amount);
    virtual void Lock();
    virtual void Unlock();
    virtual bool IsLocked() const;
};

#endif
