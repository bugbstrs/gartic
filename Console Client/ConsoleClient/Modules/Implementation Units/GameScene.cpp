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

void GameScene::SendMessage()
{
	if (m_message.empty())
		return;


	//send message to server


	Color color = m_lastChatColor ? Color::Gray : Color::White;
	m_lastChatColor = !m_lastChatColor;
	m_chat->AddObject(new Label{Align::Left, Align::Up, color, Color::Black, 20,
					  static_cast<int16_t>((m_message.size() + 4) / 20 + 2), m_console, "You: " + m_message});

	m_message.clear();
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
	m_message = "";
	m_lastChatColor = false;
	m_console->SetWindowed();
	m_console->NewConsole(L"Game", 160, 90);
	m_console->SetConsoleFont(L"MS Gothic", 12, 12);
	m_console->SetFullscreen();

	// Drawing Board
	m_drawingBoard = new DrawingBoard{24, 5, 112, 70, Color::White, m_console, m_input, m_selected, 784, 490};
	m_selectableObjects.emplace_back(m_drawingBoard);
	m_objects.emplace_back(m_drawingBoard);

	// Users layout
	m_users = new VerticalLayout{2, 5, Align::Center, Align::Up, Color::White, 20, 70, m_console, 0};
	m_objects.emplace_back(m_users);

	// Chat layout
	m_chat = new VerticalLayout{138, 5, Align::Center, Align::Up, Color::White, 20, 77, m_console, 0};
	m_objects.emplace_back(m_chat);

	// Chatbox
	auto chatbox = new InputField{138, 83, Align::Left, Align::Up, Color::Gray, Color::Black, 20, 5,
								 Color::Gray, Color::Black, m_console, m_input, m_selected, m_message, 100};
	chatbox->SetFunctionOnActivate(std::bind(&GameScene::SendMessage, this));
	m_selectableObjects.emplace_back(chatbox);
	m_objects.emplace_back(chatbox);

	// Leave button
	auto leaveButton = new Button{2, 83, Align::Center, Align::Center, Color::Blue, Color::White, 11, 5,
							Color::DarkBlue, Color::White, m_console, m_input, m_selected, "LEAVE"};
	leaveButton->SetFunctionOnActivate(std::bind(&GameScene::Leave, this));
	m_selectableObjects.emplace_back(leaveButton);
	m_objects.emplace_back(leaveButton);

	m_selected = leaveButton;
}

void GameScene::Update()
{
	while (m_nextScene == nullptr)
	{
		Input();
		Display();
	}
}
