module LoginScene;

import <algorithm>;
import <print>;
import <string>;

import InputManager;

LoginScene::LoginScene(ConsoleManager* console, InputManager* inputManager) :
	Scene{ console, inputManager }
{}

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

void LoginScene::Display() const
{
	//Title
	m_console->SetColor(ColorType::Cyan, ColorType::Magenta);
	m_console->WriteHorizontal("GARTIC", 30, 2);

	//Username Field
	m_console->SetColor(ColorType::Black, ColorType::White);
	m_console->WriteHorizontal("User:", 20, 5);

	m_option == Options::USER ? m_console->SetColor(ColorType::Blue, ColorType::White)
		: m_console->SetColor(ColorType::Gray, ColorType::Black);
	m_console->WriteHorizontal("                  ", 28, 5);
	m_console->WriteHorizontal(m_username, 28, 5);

	//Password Field
	m_console->SetColor(ColorType::Black, ColorType::White);
	m_console->WriteHorizontal("Password:", 18, 6);

	if (m_option == Options::PASSWORD)
		m_console->SetColor(ColorType::Blue, ColorType::White);
	else
		m_console->SetColor(ColorType::Gray, ColorType::Black);
	m_console->WriteHorizontal("                  ", 28, 6);
	m_console->WriteHorizontal(m_password, 28, 6);

	//Login Button
	if (m_option == Options::LOGIN)
		m_console->SetColor(ColorType::Blue, ColorType::White);
	else
		m_console->SetColor(ColorType::DarkGray, ColorType::Green);

	m_console->WriteHorizontal("Login", 25, 10);

	//Register Button
	if (m_option == Options::REGISTER)
		m_console->SetColor(ColorType::Blue, ColorType::White);
	else
		m_console->SetColor(ColorType::DarkGray, ColorType::Cyan);

	m_console->WriteHorizontal("Register", 36, 10);

	//Controls
	m_console->SetColor(ColorType::Black, ColorType::Gray);
	m_console->WriteHorizontal("Use right click or arrow keys", 30, 12);
	m_console->WriteHorizontal("to select options And Enter to confirm", 30, 13);

	//Cursor position
	m_console->SetCursor(false);
	if (m_option == Options::USER)
		m_console->SetCursor(true, 23 + m_textpos, 5);
	if (m_option == Options::PASSWORD)
		m_console->SetCursor(true, 23 + m_textpos, 6);

	//Update console
	m_console->UpdateConsole();
}

void LoginScene::Start()
{
	m_username = "";
	m_password = "";
	m_option = Options::USER;
	m_textpos = 0;
	m_nextScene = nullptr;

	m_console->NewConsole(L"Login", 60, 15);
	Display();
}

void LoginScene::Update()
{
	while (m_nextScene == nullptr)
	{
		m_input->ReadInput();
		if (m_input->GetCurrentKeyboardInput())
		{
			switch (m_input->ControlKey())
			{
			case ControlKeys::UpArrow:
				if (m_option == Options::PASSWORD)
				{
					m_option = Options::USER;
					m_textpos = std::min((int)m_username.size(), 17);
				}
				if (m_option > Options::PASSWORD)
				{
					m_option = Options::PASSWORD;
					m_textpos = std::min((int)m_password.size(), 17);
				}
				break;
			case ControlKeys::DownArrow:
				if (m_option == Options::USER)
					m_textpos = std::min((int)m_password.size(), 17);
				if (m_option <= Options::PASSWORD)
					m_option = static_cast<Options>(static_cast<int>(m_option) + 1);
				break;
			case ControlKeys::LeftArrow:
				if (m_option == Options::REGISTER)
					m_option = Options::LOGIN;
				if (m_option < Options::LOGIN)
					m_textpos = std::max(m_textpos - 1, 0);
				break;
			case ControlKeys::RightArrow:
				if (m_option == Options::LOGIN)
					m_option = Options::REGISTER;
				if (m_option == Options::USER)
					m_textpos = std::min(m_textpos + 1, std::min((int)m_username.size(), 17));
				if (m_option == Options::PASSWORD)
					m_textpos = std::min(m_textpos + 1, std::min((int)m_password.size(), 17));
				break;
			case ControlKeys::Enter:
				if (m_option == Options::LOGIN && Login())
					m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
				if (m_option == Options::REGISTER && Register())
					m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
				break;
			default:
				break;
			}
			if (m_input->ControlKey() == ControlKeys::NotControl)
			{
				if (m_option == Options::USER)
				{
					size_t len{ m_username.size() };
					m_input->UpdateString(m_username, m_textpos, 18);
					m_textpos += m_username.size() - len;
				}
				if (m_option == Options::PASSWORD)
				{
					size_t len{ m_password.size() };
					m_input->UpdateString(m_password, m_textpos, 18);
					m_textpos += m_password.size() - len;
				}
				m_textpos = std::max(m_textpos, 0);
				m_textpos = std::min(m_textpos, 17);
			}
		}

		if (m_input->GetClickPressed())
		{
			//check what object was pressed
		}

		if (m_input->GetCurrentKeyboardInput() || m_input->GetClickPressed())
			Display();
	}
}
