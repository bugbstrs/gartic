export module PlayerDoesntExistException;

import <string>;
import <stdexcept>;

export class PlayerDoesntExistException : public std::logic_error
{
public:
    PlayerDoesntExistException();
    const std::string type{ "PlayerDoesntExistException" };
};
