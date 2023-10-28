export module LoginScene;

import <string>;

export import ConsoleManager;

export class LoginScene
{
public:
	static void SetActive();
private:
	static std::string m_username;
	static std::string m_password;

	enum Options
	{
		USER,
		PASSWORD,
		LOGIN,
		REGISTER
	};
	static Options m_option;

	static void Start();
	static void Update();
	static void Display();
	static bool Login();
	static bool Register();
};