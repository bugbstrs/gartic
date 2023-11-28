#include "UserDoesntExistException.h"

UserDoesntExistException::UserDoesntExistException(const std::string& message): GarticException(message)
{
}
