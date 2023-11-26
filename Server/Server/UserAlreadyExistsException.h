#pragma once
#include "GarticException.h"

class UserAlreadyExistsException : public GarticException
{
public:
	// Constructor
	UserAlreadyExistsException(const std::string&);
};

