export module LoginScene;

import <string>;

import ConsoleManager;
export import SceneType;

export class LoginScene
{
public:
	static SceneType SetActive();
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
	static SceneType m_nextScene;

	static void Start();
	static void Update();
	static void Display();
	static bool Login();
	static bool Register();
};