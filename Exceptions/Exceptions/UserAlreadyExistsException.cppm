export module UserAlreadyExistsException;

import <string>;
import <stdexcept>;

export class UserAlreadyExistsException : std::logic_error
{
public:
    UserAlreadyExistsException();
    const std::string type{"UserAlreadyExistsException"};
};
