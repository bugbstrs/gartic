export module LoginScene;

import <string>;

import ConsoleManager;
import MenuScene;
export import Scene;

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
	int m_textpos;

	void Start() override;
	void Update() override;
	void Display() const override;
	bool Login() const;
	bool Register() const;
};