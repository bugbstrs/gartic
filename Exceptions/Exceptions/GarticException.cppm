export module GarticException;

import <format>;

template <typename ExcpType>
concept GarticExceptionClass = requires(ExcpType exception)
{
    exception.what();
    exception.type;
};

export template <GarticExceptionClass ExcpType>
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

template <GarticExceptionClass ExcpType>
GarticException<ExcpType>::GarticException() :
    m_message{ "empty" },
    m_exception{ ExcpType() }
{}

template <GarticExceptionClass ExcpType>
GarticException<ExcpType>::GarticException(const std::string& message) :
    m_message{ message },
    m_exception{ ExcpType() }
{}

template <GarticExceptionClass ExcpType>
const std::string& GarticException<ExcpType>::what()
{
    return std::format("{}: {}", m_exception.type, m_message);
}