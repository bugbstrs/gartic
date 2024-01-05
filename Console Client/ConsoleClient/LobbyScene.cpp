#include <cpr/cpr.h>
#include <crow.h>

module LobbyScene;

import <vector>;
import <string>;

import HorizontalLayout;

LobbyScene::LobbyScene(ConsoleManager* console, InputManager* inputManager) :
	Scene{ console, inputManager }
{}

void LobbyScene::StartGame()
{
	m_nextScene = const_cast<std::type_info*>(&typeid(GameScene));
}

void LobbyScene::GetUsers()
{
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchusers" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	) };
	auto usersVector{ crow::json::load(response.text) };
	m_users->Clear();
	bool lastUserColor{ false };
	bool first{ true };
	for (const auto& user : usersVector)
	{
		Color color = first ? Color::Green : lastUserColor ? Color::DarkGray : Color::White;
		if (first && std::string(user["username"]) == User::GetUsername())
			SetAsLeader();
		first = false;
		lastUserColor = !lastUserColor;
		m_users->AddObject(new Label{ Align::Center, Align::Center, color, Color::Black,
									  20, 3, m_console, std::string(user["username"]) });
	}
}

void LobbyScene::GetSettings()
{

}

void LobbyScene::SetSettings()
{

}

void LobbyScene::SetAsLeader()
{
	m_rounds->CanBeSelected(true);
	m_drawTime->CanBeSelected(true);
	m_wordCount->CanBeSelected(true);
	m_customRounds->CanBeSelected(true);
	m_startButton->SetActive(true);
}

void LobbyScene::HasStarted()
{
	m_nextScene = const_cast<std::type_info*>(&typeid(GameScene));
}

void LobbyScene::Back()
{
	auto response{ cpr::Get(
	cpr::Url{ "http://localhost:18080/leavelobby" },
	cpr::Parameters{
		{"password", User::GetPassword()},
		{"username", User::GetUsername()}
	}
) };

	m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
}

void LobbyScene::Input() const
{
	m_input->ReadInput();

	for (auto object : m_selectableObjects)
		object->CheckCursor();

	m_selected->CheckInput();
}

void LobbyScene::Start()
{
	m_nextScene = nullptr;
	m_console->ResetColorsPalette();
	m_console->AddColorsToPalette({White, Black, Gray, DarkBlue, Blue, DarkGray, Green, DarkGreen});
	m_console->NewConsole(L"Lobby", 160, 45);
	m_console->SetConsoleFont(L"Consolas", 12, 24);
	m_console->SetFullscreen();

	// Users display
	m_users = new VerticalLayout{ 7, 5, Align::Left, Align::Up, Color::Gray, 20, 36, m_console, 0 };
	m_objects.emplace_back(m_users);

	// Draw time
	auto horizontalLayout = new HorizontalLayout{ 40, 5, Align::Right, Align::Up, Color::Black, 21, 3, m_console, 1 };

	horizontalLayout->AddObject(new Label{ Align::Right, Align::Center, Color::Black, Color::White,
		9, 3, m_console, "Draw time" });

	m_drawTime = new SpinBox{Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::DarkBlue, Color::Black};
	m_drawTime->CanBeSelected(false);
	m_drawTime->SetOptions({ "15", "20", "30", "40", "50", "60", "70", "80", "90", "100", "120" }, 5);
	m_drawTime->SetHoverColors(Color::Blue, Color::Black);
	m_selectableObjects.emplace_back(m_drawTime);
	horizontalLayout->AddObject(m_drawTime);

	m_objects.emplace_back(horizontalLayout);

	// Rounds
	horizontalLayout = new HorizontalLayout{ 40, 9, Align::Right, Align::Up, Color::Black, 21, 3, m_console, 1 };

	horizontalLayout->AddObject(new Label{ Align::Right, Align::Center, Color::Black, Color::White,
		6, 3, m_console, "Rounds" });

	m_rounds = new SpinBox{ Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::DarkBlue, Color::Black };
	m_rounds->CanBeSelected(false);
	m_rounds->SetOptions({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }, 3);
	m_rounds->SetHoverColors(Color::Blue, Color::Black);
	m_selectableObjects.emplace_back(m_rounds);
	horizontalLayout->AddObject(m_rounds);

	m_objects.emplace_back(horizontalLayout);

	// Words to choose
	horizontalLayout = new HorizontalLayout{ 40, 13, Align::Right, Align::Up, Color::Black, 21, 3, m_console, 1 };

	horizontalLayout->AddObject(new Label{ Align::Right, Align::Center, Color::Black, Color::White,
		10, 3, m_console, "Word count" });

	m_wordCount = new SpinBox{ Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::DarkBlue, Color::Black };
	m_wordCount->CanBeSelected(false);
	m_wordCount->SetOptions({ "1", "2", "3", "4", "5" }, 2);
	m_wordCount->SetHoverColors(Color::Blue, Color::Black);
	m_selectableObjects.emplace_back(m_wordCount);
	horizontalLayout->AddObject(m_wordCount);
	
	m_objects.emplace_back(horizontalLayout);

	// Custom rounds
	horizontalLayout = new HorizontalLayout{ 40, 17, Align::Right, Align::Up, Color::Black, 21, 3, m_console, 1 };

	horizontalLayout->AddObject(new Label{ Align::Right, Align::Center, Color::Black, Color::White,
		10, 3, m_console, "Custom rounds" });

	m_customRounds = new CheckBox{ Color::Gray, Color::Green, Color::DarkBlue, 6, 3, m_console, m_input, m_selected };
	m_customRounds->CanBeSelected(false);
	m_customRounds->SetHoverColors(Color::Blue, Color::Black);
	m_selectableObjects.emplace_back(m_customRounds);
	horizontalLayout->AddObject(m_customRounds);

	m_objects.emplace_back(horizontalLayout);

	// Code label
	m_codeLabel = new Label{ 40, 22, Align::Center, Align::Center, Color::Black, Color::White,
		17, 1, m_console, "Code: " };
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchcode" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	);
	if (response.status_code == 200)
	{
		auto code = crow::json::load(response.text);
		m_codeLabel->UpdateText(std::string("Code: ") + std::string(code[0]["code"]));
	}
	else
	{

	}
	m_objects.emplace_back(m_codeLabel);

	// Leave lobby button
	auto leaveButton = new Button{ 150, 40, Align::Center, Align::Center, Color::Gray, Color::Black, 7, 3,
		Color::DarkBlue, Color::Black, m_console, m_input, m_selected, "LEAVE" };

	leaveButton->SetHoverColors(Color::Blue, Color::White);
	leaveButton->SetFunctionOnActivate([this]() { Back(); });
	m_selectableObjects.emplace_back(leaveButton);
	m_objects.emplace_back(leaveButton);

	// Start button
	m_startButton = new Button{ 40, 40, Align::Center, Align::Center, Color::DarkGreen, Color::White, 15, 3,
		Color::Green, Color::White, m_console, m_input, m_selected, "START" };
	m_startButton->SetHoverColors(Color::Green, Color::White);
	m_startButton->SetFunctionOnActivate([this]() { StartGame(); });
	m_startButton->SetActive(false);
	m_selectableObjects.emplace_back(m_startButton);
	m_objects.emplace_back(m_startButton);


	m_drawTime->SetConections(nullptr, m_rounds, nullptr, nullptr);
	m_rounds->SetConections(m_drawTime, m_wordCount, nullptr, nullptr);
	m_wordCount->SetConections(m_rounds, m_customRounds, nullptr, nullptr);
	m_customRounds->SetConections(m_wordCount, m_startButton, nullptr, nullptr);
	m_startButton->SetConections(m_customRounds, nullptr, nullptr, leaveButton);
	leaveButton->SetConections(nullptr, nullptr, m_startButton, nullptr);

	m_selected = leaveButton;
}

void LobbyScene::Update()
{
	while (m_nextScene == nullptr)
	{
		GetUsers();

		Input();
		Display();
	}
}
