#pragma once

#include <stdexcept>

class GarticException : public std::logic_error
{
public:
	// Constructors
	GarticException();
	GarticException(const std::string&);
};

