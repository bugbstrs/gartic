#pragma once
#include "GarticException.h"

class CannotFetchQuoteException : public GarticException
{
public:
	CannotFetchQuoteException(const std::string& message);
};

