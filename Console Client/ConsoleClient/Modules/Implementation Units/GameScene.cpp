module GameScene;

using Color = ColorType;

GameScene::GameScene(ConsoleManager *console, InputManager *inputManager):
	Scene{console, inputManager}
{}

void GameScene::GetPlayers()
{

}

void GameScene::GetTimer()
{

}

void GameScene::GetRound()
{

}

void GameScene::GetChat()
{

}

void GameScene::GetDrawEvents()
{

}

void GameScene::Leave()
{
	m_nextScene = const_cast<std::type_info *>(&typeid(MenuScene));
}

void GameScene::Input() const
{
	m_input->ReadInput();

	for (auto object : m_selectableObjects)
		object->CheckCursor();

	m_selected->CheckInput();
}

void GameScene::Start()
{
	m_nextScene = nullptr;
	m_console->SetWindowed();
	m_console->NewConsole(L"Game", 160, 90);
	m_console->SetConsoleFont(L"MS Gothic", 12, 12);
	m_console->SetFullscreen();

	// Drawing Board  120x75
	m_drawingBoard = new DrawingBoard{24, 5, 112, 70, Color::White, m_console, m_input, m_selected, 784, 490};
	m_selectableObjects.emplace_back(m_drawingBoard);
	m_objects.emplace_back(m_drawingBoard);

	// Users layout
	m_users = new VerticalLayout{2, 5, Align::Center, Align::Up, Color::White, 20, 70, m_console, 0};
	m_objects.emplace_back(m_users);

	// Chat layout
	m_chat = new VerticalLayout{138, 5, Align::Center, Align::Up, Color::White, 20, 80, m_console, 0};
	m_objects.emplace_back(m_chat);


	m_selected = m_drawingBoard;
}

void GameScene::Update()
{
	while (m_nextScene == nullptr)
	{
		Input();
		Display();
	}
}
