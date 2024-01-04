#include <cpr/cpr.h>

module LoginScene;

import Label;
import Button;
import InputField;
import HorizontalLayout;

using Color = ColorType;

LoginScene::LoginScene(ConsoleManager* console, InputManager* inputManager) :
	Scene{ console, inputManager }
{}

void LoginScene::Login()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Parameters
		{
			{"password", m_password},
			{"username", m_username}
		});
	if (response.status_code == 200)
	{
		User::Initialize(m_username, m_password);
		m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
	}else
	{

	}
}

void LoginScene::Register()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Parameters{
			{"password", m_password},
			{"username", m_username}
		}
	);
	if (response.status_code == 201)
	{
		User::Initialize(m_username, m_password);
		m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
	}else
	{

	}
}

void LoginScene::Input() const
{
	m_input->ReadInput();

	for (auto object : m_selectableObjects)
		object->CheckCursor();

	m_selected->CheckInput();
}

void LoginScene::Start()
{
	m_username = "";
	m_password = "";
	m_nextScene = nullptr;
	m_console->ResetColorsPalette();
	m_console->AddColorsToPalette({Cyan, Purple, White, Black, Gray, DarkBlue, Blue, DarkGray, Green});
	m_console->SetWindowed();
	m_console->NewConsole(L"Login", 50, 11);
	m_console->SetConsoleFont(L"Consolas", 11, 24);

	m_objects.emplace_back(new Label{25, 1, Align::Left, Align::Up, Color::Cyan, Color::Purple, 6, 1, m_console, "GARTIC"});

	auto layout{new HorizontalLayout{11, 4, Align::Right, Align::Up, Color::Black, 27, 1, m_console, 0}};
	layout->AddObject(new Label{Align::Left, Align::Up, Color::Black, Color::White, 5, 1, m_console, "User:"});
	auto userField{new InputField{Align::Left, Align::Up, Color::Gray, Color::Black, 18, 1, Color::DarkBlue, Color::White,
						m_console, m_input, m_selected, m_username}};
	userField->SetHoverColors(Color::Blue, Color::White);
	layout->AddObject(userField);
	m_selectableObjects.emplace_back(userField);

	m_objects.emplace_back(layout);

	layout = new HorizontalLayout{11, 5, Align::Right, Align::Up, Color::Black, 27, 1, m_console, 0};
	layout->AddObject(new Label{Align::Left, Align::Up, Color::Black, Color::White, 9, 1, m_console, "Password:"});
	auto passwordField{new InputField{Align::Left, Align::Up, Color::Gray, Color::Black, 18, 1, Color::DarkBlue, Color::White,
						m_console, m_input, m_selected, m_password}};
	passwordField->SetHoverColors(Color::Blue, Color::White);
	layout->AddObject(passwordField);
	m_selectableObjects.emplace_back(passwordField);

	m_objects.emplace_back(layout);

	auto loginButton{new Button{20, 8, Align::Left, Align::Up, Color::DarkGray, Color::Green, 5, 1, Color::DarkBlue,
						Color::White, m_console, m_input, m_selected, "LOGIN"}};
	loginButton->SetHoverColors(Color::Blue, Color::White);
	loginButton->SetFunctionOnActivate([this]() { Login(); });
	m_objects.emplace_back(loginButton);
	m_selectableObjects.emplace_back(loginButton);

	auto registerButton{new Button{30, 8, Align::Left, Align::Up, Color::DarkGray, Color::Cyan, 8, 1, Color::DarkBlue,
						Color::White, m_console, m_input, m_selected, "REGISTER"}};
	registerButton->SetHoverColors(Color::Blue, Color::White);
	registerButton->SetFunctionOnActivate([this]() { Register(); });
	m_objects.emplace_back(registerButton);
	m_selectableObjects.emplace_back(registerButton);

	userField->SetConections(nullptr, passwordField, nullptr, nullptr);
	passwordField->SetConections(userField, loginButton, nullptr, nullptr);
	loginButton->SetConections(passwordField, nullptr, nullptr, registerButton);
	registerButton->SetConections(passwordField, nullptr, loginButton, nullptr);

	m_selected = userField;

	Display();
}

void LoginScene::Update()
{
	while (m_nextScene == nullptr)
	{
		Input();
		Display();
	}
}
