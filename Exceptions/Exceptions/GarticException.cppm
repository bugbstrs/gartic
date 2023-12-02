export module GarticException;

export import <exception>;
export import <concepts>;
import <string>;

export template <typename ExcpType>
concept GarticExceptionType = requires(ExcpType exception)
{
    std::derived_from<ExcpType, std::exception>;
    exception.what();
    exception.type();
    { exception.type() } -> std::same_as<std::string>;
};

export template <GarticExceptionType ExcpType>
class GarticException
{
public:
    GarticException() = delete;
    GarticException(const std::string& message);

    const std::string what();
private:
    ExcpType m_exception;
    std::string m_message;
};