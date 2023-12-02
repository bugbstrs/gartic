#include "NotEnoughPlayersException.h"

NotEnoughPlayersException::NotEnoughPlayersException(const std::string& message): GarticException(message)
{
}
