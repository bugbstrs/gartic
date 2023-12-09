export module CannotFetchWordException;

import <string>;
import <stdexcept>;

export class CannotFetchWordException : public std::logic_error
{
public:
    CannotFetchWordException();
    const std::string type{ "CannotFetchWordException" };
};