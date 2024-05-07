#pragma once
// Subquestion (a) Simple class Exception with no members.
class Exception {};

// Subquestion (b) NoFundsException class, a subclass of Exception.
class NoFundsException : public Exception {};

// Subquestion (c) NoAccessException class, a subclass of Exception.
class NoAccessException : public Exception {};
