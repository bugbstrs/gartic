#include "UserAlreadyExistsException.h"

UserAlreadyExistsException::UserAlreadyExistsException(const std::string& message): GarticException(message)
{
}
