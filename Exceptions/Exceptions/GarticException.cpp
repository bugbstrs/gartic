//#include "GarticException.h"
//
//template <class ExcpType>
//GarticException<ExcpType>::GarticException():
//    m_message   { "empty"    },
//    m_exception { ExcpType() }
//{}
//
//template <class ExcpType>
//GarticException<ExcpType>::GarticException(const std::string& message):
//    m_message   { message    },
//    m_exception { ExcpType() }
//{}
//
//template <class ExcpType>
//const std::string& GarticException<ExcpType>::what()
//{
//	return std::format("{}: {}", m_exception.type, m_message);
//}