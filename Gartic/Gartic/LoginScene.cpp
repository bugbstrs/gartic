module LoginScene;

import <string>;

import SceneType;
import InputManager;

void LoginScene::Start()
{
	m_username = "";
	m_password = "";
	m_option = USER;
	m_nextScene = nullptr;
	ConsoleManager::SetConsoleScale(60, 15);
	Display();
}

void LoginScene::Update()
{
	while (m_nextScene != nullptr)
	{
		InputManager::ReadInput();
		if (InputManager::GetCurrentKeyboardInput())
		{
			switch (InputManager::ControlKey())
			{
			case ControlKeys::UpArrow:

				break;
			case ControlKeys::DownArrow:

				break;
			case ControlKeys::LeftArrow:

				break;
			case ControlKeys::RightArrow:

				break;
			case ControlKeys::Enter:

				break;
			default:
				break;
			}
			if (InputManager::ControlKey() == ControlKeys::NotControl)
			{
				if (m_option == USER)
					InputManager::UpdateString(m_username, 18);
				if (m_option == PASSWORD)
					InputManager::UpdateString(m_password, 18);
			}
		}

		if (InputManager::GetCurrentKeyboardInput() || InputManager::ClickPressed())
			Display();
	}
}

void LoginScene::Display()
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
}

bool LoginScene::Login()
{
	//Init User
	return true;
}

bool LoginScene::Register()
{
	//Init User
	return false;
}