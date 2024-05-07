#pragma once

// Subquestion (d) and (e) Abstract base class Account with Withdraw() and GetBalance() methods.
class Account {
public:
    virtual void Withdraw(double amount) = 0;
    virtual double GetBalance() = 0;
    virtual ~Account() = default;
};