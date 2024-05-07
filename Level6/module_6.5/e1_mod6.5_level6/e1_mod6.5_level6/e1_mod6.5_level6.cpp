#include <iostream>
#include <stdexcept>
#include "Exceptions.h"
#include "Account.h"
#include "RealAccount.h"
#include "ProtectedAccount.h"

int main()
{
    double initialBalance = 1000.0;
    std::string correctPassword = "correctpassword";
    std::string wrongPassword = "wrongpassword";

    // Testing RealAccount
    std::cout << "Testing RealAccount...\n";
    RealAccount realAccount(initialBalance);

    try {
        std::cout << "Initial balance: $" << realAccount.GetBalance() << "\n";

        // Withdraw with enough balance
        realAccount.Withdraw(100);
        std::cout << "Balance after withdrawing $100: $" << realAccount.GetBalance() << "\n";

        // Withdraw with not enough balance
        realAccount.Withdraw(1000);  // This should cause an exception
    }
    catch (const NoFundsException&) {
        std::cerr << "NoFundsException: Not enough funds to withdraw $1000\n";
    }

    // Testing ProtectedAccount
    std::cout << "\nTesting ProtectedAccount...\n";
    ProtectedAccount protectedAccount(initialBalance, correctPassword);

    try {
        // Trying to get balance with correct password
        std::cout << "Balance with correct password: $" << protectedAccount.GetBalance(correctPassword) << "\n";

        // Trying to get balance with wrong password
        std::cout << "Attempting to get balance with wrong password...\n";
        std::cout << "Balance with wrong password: $" << protectedAccount.GetBalance(wrongPassword) << "\n";
    }
    catch (const NoAccessException&) {
        std::cerr << "NoAccessException: Incorrect password provided for balance check.\n";
    }

    try {
        // Withdrawing from protected account with enough balance
        protectedAccount.Withdraw(100);
        std::cout << "Protected account balance after withdrawing $100: $" << protectedAccount.GetBalance(correctPassword) << "\n";
    }
    catch (const NoFundsException&) {
        std::cerr << "NoFundsException: Not enough funds to withdraw $100.\n";
    }
    catch (const NoAccessException&) {
        std::cerr << "NoAccessException: Incorrect password provided for balance check after withdrawal.\n";
    }

    return 0;
}