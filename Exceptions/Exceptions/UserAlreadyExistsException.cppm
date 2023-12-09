export module UserAlreadyExistsException;

import <string>;
import <stdexcept>;

export class UserAlreadyExistsException : public std::logic_error
{
public:
    UserAlreadyExistsException();
    const std::string type{"UserAlreadyExistsException"};
};
