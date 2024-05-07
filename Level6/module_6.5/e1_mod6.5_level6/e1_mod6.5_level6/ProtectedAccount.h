#pragma once

#include <iostream>
#include <stdexcept>
#include "Exceptions.h"
#include "Account.h"
#include "RealAccount.h"

// Subquestion (g): ProtectedAccount class
class ProtectedAccount : public Account {
private:
    std::shared_ptr<RealAccount> linkedAccount_;
    std::string pwd_;                             

public:
    // Constructor with initial balance and password
    ProtectedAccount(double balance, std::string pwd)
        : linkedAccount_(std::make_shared<RealAccount>(balance)), pwd_(std::move(pwd)) {}

    // Subquestion (h)
    void Withdraw(double amount) override {
        linkedAccount_->Withdraw(amount);
    }

    // Subquestion (i)
    double GetBalance(const std::string& pwdAttempt) {
        if (pwdAttempt != pwd_) throw NoAccessException();
        return linkedAccount_->GetBalance();
    }

    double GetBalance() override {
        throw NoAccessException();
    }
};