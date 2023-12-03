#pragma once

#include <format>

template <class ExcpType>
class GarticException
{
public:
    GarticException();
    GarticException(const std::string& message);

    const std::string& what();
private:
    ExcpType m_exception;
    std::string m_message;
};