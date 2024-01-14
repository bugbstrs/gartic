#include "UserCredentials.h"
#include <stdexcept>

bool UserCredentials::m_credentialsSet = false;
std::string UserCredentials::m_username = "";
std::string UserCredentials::m_password = "";

void UserCredentials::SetCredentials(const std::string& username, const std::string& password)
{
    if (m_credentialsSet)
    {
        throw std::logic_error("Credentials can only be set once.");
    }

    m_username = username;
    m_password = password;
    m_credentialsSet = true;
}

std::string UserCredentials::GetUsername()
{
    return m_username;
}

std::string UserCredentials::GetPassword()
{
    return m_password;
}
