#include <algorithm>

module LoginScene;

import <string>;

import InputManager;

void LoginScene::Start()
{
	m_username = "";
	m_password = "";
	m_option = USER;
	m_textpos = 0;
	m_nextScene = nullptr;
	ConsoleManager::SetConsoleScale(60, 15);
	Display();
}

void LoginScene::Update()
{
	while (m_nextScene == nullptr)
	{
		InputManager::ReadInput();
		if (InputManager::GetCurrentKeyboardInput())
		{
			switch (InputManager::ControlKey())
			{
			case ControlKeys::UpArrow:
				if (m_option == PASSWORD)
				{
					m_option = USER;
					m_textpos = std::min((int)m_username.size(), 17);
				}
				if (m_option > PASSWORD)
				{
					m_option = PASSWORD;
					m_textpos = std::min((int)m_password.size(), 17);
				}
				break;
			case ControlKeys::DownArrow:
				if (m_option == USER)
					m_textpos = std::min(m_textpos, std::min((int)m_password.size(), 17));
				if (m_option <= PASSWORD)
					m_option = static_cast<Options>(static_cast<int>(m_option) + 1);
				break;
			case ControlKeys::LeftArrow:
				if (m_option == REGISTER)
					m_option = LOGIN;
				if (m_option < LOGIN)
					m_textpos = std::max(m_textpos - 1, 0);
				break;
			case ControlKeys::RightArrow:
				if (m_option == LOGIN)
					m_option = REGISTER;
				if (m_option == USER)
					m_textpos = std::min(m_textpos + 1, std::min((int)m_username.size(), 17));
				if (m_option == PASSWORD)
					m_textpos = std::min(m_textpos + 1, std::min((int)m_password.size(), 17));
				break;
			case ControlKeys::Enter:
				if (m_option == LOGIN)
					if (Login())
						m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
				if (m_option == REGISTER)
					if (Register())
						m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
				break;
			default:
				break;
			}
			if (InputManager::ControlKey() == ControlKeys::NotControl)
			{
				if (m_option == USER)
				{
					int len = m_username.size();
					InputManager::UpdateString(m_username, m_textpos, 18);
					m_textpos += m_username.size() - len;
				}
				if (m_option == PASSWORD)
				{
					int len = m_password.size();
					InputManager::UpdateString(m_password, m_textpos, 18);
					m_textpos += m_password.size() - len;
				}
				m_textpos = std::max(m_textpos, 0);
			}
		}

		if (InputManager::GetCurrentKeyboardInput() || InputManager::ClickPressed())
			Display();
	}
}

void LoginScene::Display() const
{
	//Title
	ConsoleManager::ClearScreen();
	ConsoleManager::SetColor(ColorType::Cyan, ColorType::Magenta);
	ConsoleManager::WriteHorizontal("GARTIC", 30, 2);
	//Username Field
	ConsoleManager::SetColor(ColorType::Black, ColorType::White);
	ConsoleManager::WriteHorizontal("User:", 20, 5);
	if (m_option == USER)
		ConsoleManager::SetColor(ColorType::Blue, ColorType::White);
	else
		ConsoleManager::SetColor(ColorType::Gray, ColorType::Black);
	std::cout << "                  ";
	ConsoleManager::SetCursor(23, 5);
	std::cout << m_username;
	//Password Field
	ConsoleManager::SetColor(ColorType::Black, ColorType::White);
	ConsoleManager::WriteHorizontal("Password:", 18, 6);
	if (m_option == PASSWORD)
		ConsoleManager::SetColor(ColorType::Blue, ColorType::White);
	else
		ConsoleManager::SetColor(ColorType::Gray, ColorType::Black);
	std::cout << "                  ";
	ConsoleManager::SetCursor(23, 6);
	std::cout << m_password;
	//Login Button
	if (m_option == LOGIN)
		ConsoleManager::SetColor(ColorType::Blue, ColorType::White);
	else
		ConsoleManager::SetColor(ColorType::DarkGray, ColorType::Green);
	ConsoleManager::WriteHorizontal("Login", 25, 10);
	//Register Button
	if (m_option == REGISTER)
		ConsoleManager::SetColor(ColorType::Blue, ColorType::White);
	else
		ConsoleManager::SetColor(ColorType::DarkGray, ColorType::Cyan);
	ConsoleManager::WriteHorizontal("Register", 36, 10);
	//Controls
	ConsoleManager::SetColor(ColorType::Black, ColorType::Gray);
	ConsoleManager::WriteHorizontal("Use arrow keys to select options", 30, 12);
	ConsoleManager::WriteHorizontal("And Enter to confirm", 30, 13);

	if (m_option == USER)
		ConsoleManager::SetCursor(23 + m_textpos, 5);
	if (m_option == PASSWORD)
		ConsoleManager::SetCursor(23 + m_textpos, 6);
}

bool LoginScene::Login() const
{
	//Init User
	return true;
}

bool LoginScene::Register() const
{
	//Init User
	return false;
}