export module NotEnoughScoresRegisteredException;

import <string>;
import <stdexcept>;

export class NotEnoughScoresRegisteredException : public std::logic_error
{
public:
    NotEnoughScoresRegisteredException();
    const std::string type{ "NotEnoughScoresRegisteredException" };
};