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


	Color color = m_lastChatColor ? Color::DarkGray : Color::White;
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
	m_console->ResetColorsPalette();
	m_console->AddColorsToPalette({White, Black, DarkGray, Red, DarkRed, Orange, Yellow, Green, DarkGreen,
								  Cyan, Blue, DarkBlue, Purple, Pink, DarkPink, DarkBrown});
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

	// Color display
	m_colorDisplay = new ColorDisplay{24, 79, Color::Black, 7, 7, m_console};
	m_objects.emplace_back(m_colorDisplay);

	// Colors
	auto VLayout = new VerticalLayout{33, 77, Align::Left, Align::Up, Color::Black, 95, 11, m_console, 1};
	m_objects.emplace_back(VLayout);
	auto row1 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 95, 5, m_console, 1};
	VLayout->AddObject(row1);
	auto row2 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 95, 5, m_console, 1};
	VLayout->AddObject(row2);
	auto aux = new Button{Align::Center, Align::Center, Color::White, Color::White, 5, 5,
					Color::White, Color::White, m_console, m_input, m_selectedColorButton, ""};
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::White);
		m_drawingBoard->SetDrawColor(Color::White);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Pink, Color::Pink, 5, 5,
					Color::Pink, Color::Pink, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Pink);
		m_drawingBoard->SetDrawColor(Color::Pink);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Red, Color::Red, 5, 5,
					Color::Red, Color::Red, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Red);
		m_drawingBoard->SetDrawColor(Color::Red);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Orange, Color::Orange, 5, 5,
					Color::Orange, Color::Orange, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Orange);
		m_drawingBoard->SetDrawColor(Color::Orange);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Yellow, Color::Yellow, 5, 5,
					Color::Yellow, Color::Yellow, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Yellow);
		m_drawingBoard->SetDrawColor(Color::Yellow);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Green, Color::Green, 5, 5,
					Color::Green, Color::Green, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Green);
		m_drawingBoard->SetDrawColor(Color::Green);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Blue, Color::Blue, 5, 5,
					Color::Blue, Color::Blue, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Blue);
		m_drawingBoard->SetDrawColor(Color::Blue);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Cyan, Color::Cyan, 5, 5,
					Color::Cyan, Color::Cyan, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Cyan);
		m_drawingBoard->SetDrawColor(Color::Cyan);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::Black, Color::White, 5, 5,
					Color::Black, Color::White, m_console, m_input, m_selectedColorButton, "BLACK"});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Black);
		m_drawingBoard->SetDrawColor(Color::Black);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::DarkGray, 5, 5,
					Color::DarkGray, Color::DarkGray, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkGray);
		m_drawingBoard->SetDrawColor(Color::DarkGray);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkRed, Color::DarkRed, 5, 5,
					Color::DarkRed, Color::DarkRed, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkRed);
		m_drawingBoard->SetDrawColor(Color::DarkRed);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkBrown, Color::DarkBrown, 5, 5,
					Color::DarkBrown, Color::DarkBrown, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkBrown);
		m_drawingBoard->SetDrawColor(Color::DarkBrown);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkPink, Color::DarkPink, 5, 5,
					Color::DarkPink, Color::DarkPink, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkPink);
		m_drawingBoard->SetDrawColor(Color::DarkPink);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGreen, Color::DarkGreen, 5, 5,
					Color::DarkGreen, Color::DarkGreen, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkGreen);
		m_drawingBoard->SetDrawColor(Color::DarkGreen);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkBlue, Color::DarkBlue, 5, 5,
					Color::DarkBlue, Color::DarkBlue, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::DarkBlue);
		m_drawingBoard->SetDrawColor(Color::DarkBlue);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::Purple, Color::Purple, 5, 5,
					Color::Purple, Color::Purple, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this]()
	{
		m_colorDisplay->SetDisplayColor(Color::Purple);
		m_drawingBoard->SetDrawColor(Color::Purple);
	});
	m_selectableObjects.emplace_back(aux);

	// Width
	VLayout = new VerticalLayout{85, 77, Align::Left, Align::Up, Color::Black, 11, 11, m_console, 1};
	m_objects.emplace_back(VLayout);
	row1 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 11, 5, m_console, 1};
	VLayout->AddObject(row1);
	row2 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 11, 5, m_console, 1};
	VLayout->AddObject(row2);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedColorButton, "4"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetPenWidth(4); });
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedColorButton, "10"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetPenWidth(10); });
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedColorButton, "18"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetPenWidth(18); });
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedColorButton, "26"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetPenWidth(26); });
	m_selectableObjects.emplace_back(aux);

	// Draw options
	auto HLayout = new HorizontalLayout{101, 80, Align::Left, Align::Up, Color::Black, 31, 5, m_console, 1};
	m_objects.emplace_back(HLayout);
	HLayout->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedColorButton, "pen"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetOption(DrawingBoard::Option::draw); });
	m_selectableObjects.emplace_back(aux);
	HLayout->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedColorButton, "fill"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->SetOption(DrawingBoard::Option::fill); });
	m_selectableObjects.emplace_back(aux);
	HLayout->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedColorButton, "undo"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->Undo(); });
	m_selectableObjects.emplace_back(aux);
	HLayout->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedColorButton, "clear"});
	aux->SetFunctionOnActivate([this](){ m_drawingBoard->Clear(); });
	m_selectableObjects.emplace_back(aux);

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
