#pragma once

#include <string>
#include <numeric>
#include <sstream>
#include <regex>
#include <cpr/cpr.h>

class UserCredentials
{
public:
    static void SetCredentials(const std::string& username, const std::string& password);
    // Static method to get the first string
    static std::string GetUsername();

    // Static method to get the second string
    static std::string GetPassword();
private:
    UserCredentials() = default;
    UserCredentials(const UserCredentials&) = delete;
    UserCredentials& operator=(const UserCredentials&) = delete;
    static std::string m_username;
    static std::string m_password;
    static bool credentialsSet;
};

