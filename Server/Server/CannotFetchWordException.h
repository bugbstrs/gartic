#pragma once
#include "GarticException.h"

class CannotFetchWordException : public GarticException
{
public:
	// Constructor
	CannotFetchWordException(const std::string&);
};

