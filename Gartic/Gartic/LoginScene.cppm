export module LoginScene;

import <string>;

import ConsoleManager;
export import Scene;
export import SceneType;

export class LoginScene : public Scene
{
private:
	std::string m_username;
	std::string m_password;

	enum Options
	{
		USER,
		PASSWORD,
		LOGIN,
		REGISTER
	};
	Options m_option;

	void Start() override;
	void Update() override;
	void Display() override;
	bool Login();
	bool Register();
};