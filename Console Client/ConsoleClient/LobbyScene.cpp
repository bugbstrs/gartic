module LobbyScene;

import Label;
import Button;
import InputField;
import VerticalLayout;

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
	m_console->NewConsole(L"Lobby", 50, 11);
	m_console->SetConsoleFont(L"Consolas", 12, 24);


}

void LobbyScene::Update()
{
	while (m_nextScene == nullptr)
	{
		//GetUsers();

		Input();
		Display();
	}
}
