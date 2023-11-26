#include "GarticException.h"

GarticException::GarticException(const std::string& message)
	: std::logic_error(message)
{
}

GarticException::GarticException()
	: std::logic_error("Unknown exception")
{
}