#pragma once

#include "Account.h"
#include "Exceptions.h"

// Subquestion (f) Implementation of RealAccount class
class RealAccount : public Account {
private:
    double balance;

public:
    RealAccount(double initial_balance) : balance(initial_balance) {}

    void Withdraw(double amount) override {
        if (balance < amount) throw NoFundsException();
        balance -= amount;
    }

    double GetBalance() override {
        return balance;
    }
};