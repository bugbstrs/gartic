export module NotEnoughPlayersException;

import <string>;
import <stdexcept>;

export class NotEnoughPlayersException : public std::logic_error
{
public:
    NotEnoughPlayersException();
    const std::string type{ "NotEnoughPlayersException" };
};