#pragma once
#include "GarticException.h"

class UserDoesntExistException : public GarticException
{
public:
	// Constructor
	UserDoesntExistException(const std::string& message);
};
