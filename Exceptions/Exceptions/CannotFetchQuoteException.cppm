export module CannotFetchQuoteException;

import <string>;
import <stdexcept>;

export class CannotFetchQuoteException : public std::logic_error
{
public:
    CannotFetchQuoteException();
    const std::string type{ "CannotFetchQuoteException" };
};