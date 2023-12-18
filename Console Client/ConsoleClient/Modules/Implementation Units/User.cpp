module User;
//import "picosha2.h";

String User::m_username;
String User::m_password;

void User::Initialize(const String& username, const String& password)
{
    m_username = username;
    m_password = password;//picosha2::hash256_hex_string(password);
}

const String User::GetUsername()
{
    return m_username;
}

const String User::GetPassword()
{
    return m_password;
}