export module User;

import <string>;

using String = std::string;

export class User
{
public:
    static void Initialize(const String& username, const String& password);

    const static String GetUsername();
    const static String GetPassword();

private:
    static String m_username;
    static String m_password;
};