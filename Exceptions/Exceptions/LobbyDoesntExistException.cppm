export module LobbyDoesntExistException;

import <string>;
import <stdexcept>;

export class LobbyDoesntExistException : public std::logic_error
{
public:
    LobbyDoesntExistException();
    const std::string type{ "LobbyDoesntExistException" };
};