module GarticException;

template <GarticExceptionType ExcpType>
GarticException<ExcpType>::GarticException(const std::string& message)
{
    m_message = message;
}

template <GarticExceptionType ExcpType>
const std::string GarticException<ExcpType>::what()
{
	return std::format("{}: {}", m_exception.type(), m_message);
}