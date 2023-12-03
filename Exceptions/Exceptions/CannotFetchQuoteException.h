#pragma once
#include <string>
#include <stdexcept>

class CannotFetchQuoteException : public std::logic_error
{
public:
    CannotFetchQuoteException();
    const std::string type{ "CannotFetchQuoteException" };
};

CannotFetchQuoteException::CannotFetchQuoteException():
    std::logic_error("")
{}