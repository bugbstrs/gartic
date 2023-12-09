module LobbyScene;

import <vector>;
import <string>;

import Label;
import Button;
import HorizontalLayout;

using Color = ColorType;

LobbyScene::LobbyScene(ConsoleManager* console, InputManager* inputManager) :
	Scene{ console, inputManager }
{}

void LobbyScene::StartGame()
{
	//m_nextScene = const_cast<std::type_info*>(&typeid(GameScene));
}

void LobbyScene::GetUsers()
{

}

void LobbyScene::GetSettings()
{

}

void LobbyScene::SetSettings()
{

}

void LobbyScene::HasStarted()
{
	//m_nextScene = const_cast<std::type_info*>(&typeid(GameScene));
}

void LobbyScene::Back()
{
	m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
}

void LobbyScene::Input() const
{
	m_input->ReadInput();

	for (auto object : m_selectableObjects)
		object->CheckCursor();

	//m_selected->CheckInput();
}

void LobbyScene::Start()
{
	m_nextScene = nullptr;
	m_console->NewConsole(L"Lobby", 160, 45);
	m_console->SetConsoleFont(L"Consolas", 12, 24);
	m_console->SetFullscreen();

	// Players display
	m_users = new VerticalLayout{ 7, 5, Align::Left, Align::Up, Color::Gray, 20, 36, m_console, 0 };
	m_objects.emplace_back(m_users);

	// Draw time
	auto horizontalLayout = new HorizontalLayout{ 40, 5, Align::Right, Align::Up, Color::Black, 20, 3, m_console, 1 };

	horizontalLayout->AddObject(new Label{ Align::Left, Align::Center, Color::Black, Color::White,
		9, 3, m_console, "Draw time" });

	m_drawTime = new SpinBox{Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::Blue, Color::Black};
	m_drawTime->SetOptions({ "15", "20", "30", "40", "50", "60", "70", "80", "90", "100", "120" }, 5);
	horizontalLayout->AddObject(m_drawTime);

	m_selectableObjects.emplace_back(m_drawTime->GetPreviousButton());
	m_selectableObjects.emplace_back(m_drawTime->GetNextButton());

	m_objects.emplace_back(horizontalLayout);

	// Rounds
	m_rounds = new SpinBox{ 40, 9, Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::Blue, Color::Black };

	m_rounds->SetOptions({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }, 3);
	m_objects.emplace_back(m_rounds);

	m_selectableObjects.emplace_back(m_rounds->GetPreviousButton());
	m_selectableObjects.emplace_back(m_rounds->GetNextButton());

	// Words to choose
	m_wordCount = new SpinBox{ 40, 13, Align::Left, Align::Center, Color::Gray, Color::Black,
		10, 3, m_console, m_input, m_selected, Color::DarkGray, Color::White, Color::Blue, Color::Black };

	m_wordCount->SetOptions({ "1", "2", "3", "4", "5" }, 2);
	m_objects.emplace_back(m_wordCount);

	m_selectableObjects.emplace_back(m_wordCount->GetPreviousButton());
	m_selectableObjects.emplace_back(m_wordCount->GetNextButton());

	// Leave lobby button
	auto leaveButton = new Button{ 150, 40, Align::Center, Align::Center, Color::Gray, Color::Black, 7, 3,
		Color::Blue, Color::Black, m_console, m_input, m_selected, "LEAVE" };

	leaveButton->SetHoverColors(Color::Blue, Color::White);
	leaveButton->SetFunctionOnActivate(std::bind(&LobbyScene::Back, this));
	m_selectableObjects.emplace_back(leaveButton);
	m_objects.emplace_back(leaveButton);
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
