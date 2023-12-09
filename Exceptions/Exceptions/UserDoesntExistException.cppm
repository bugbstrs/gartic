export module UserDoesntExistException;

import <string>;
import <stdexcept>;

export class UserDoesntExistException : public std::logic_error
{
public:
    UserDoesntExistException();
    const std::string type{"UserDoesntExistException"};
};