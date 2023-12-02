#pragma once

#include "GarticException.h"

class NotEnoughPlayersException : public GarticException
{
public:
	NotEnoughPlayersException(const std::string&);
};

