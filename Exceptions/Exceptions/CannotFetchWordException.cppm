export module CannotFetchWordException;

import <string>;
import <stdexcept>;

export class CannotFetchWordException : std::logic_error
{
public:
    CannotFetchWordException();
    const std::string type{ "CannotFetchWordException" };
};