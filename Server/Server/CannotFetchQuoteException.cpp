#include "CannotFetchQuoteException.h"

CannotFetchQuoteException::CannotFetchQuoteException(const std::string& message) : GarticException(message)
{
}
