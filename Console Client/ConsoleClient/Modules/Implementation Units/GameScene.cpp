#include <cpr/cpr.h>
#include <crow.h>

module GameScene;

using Color = ColorType;

GameScene::GameScene(ConsoleManager *console, InputManager *inputManager):
	Scene{console, inputManager}
{}

void GameScene::GetPlayers()
{
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchplayers" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	) };
	if (response.status_code == 200)
	{
		auto players{ crow::json::load(response.text) };
		m_players->Clear();
		bool lastPlayerColor = false;
		int i{ 0 };
		SetAsGuesser();
		for (const auto& player : players["players"])
		{
			if (std::stoi(std::string(players["drawer index"])) == i && std::string(player["name"]) == User::GetUsername())
				SetAsDrawer();

			Color color = std::string(player["guessed"]) == "1" ? Color::Green : 
						  std::stoi(std::string(players["drawer index"])) == i ? Color::Red :
						  lastPlayerColor ? Color::DarkGray : Color::White;
			lastPlayerColor = !lastPlayerColor;
			auto layout = new VerticalLayout{ Align::Left, Align::Up, Color::White, 20, 3, m_console, 0 };
			m_players->AddObject(layout);
			layout->AddObject(new Label{ Align::Left, Align::Up, color, Color::Black, 20, 1, m_console,
										 std::string(player["name"]) });
			layout->AddObject(new Label{ Align::Left, Align::Up, color, Color::Black, 20, 1, m_console,
										 std::string(player["points"]) });
			++i;
		}
	}
}

void GameScene::GetTimer()
{
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchtime" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	) };
	if (response.status_code == 200)
	{
		m_timer->UpdateText("time: " + std::string(crow::json::load(response.text)["time"]));
	}
}

void GameScene::GetRound()
{
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchroundnumber" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	) };
	if (response.status_code == 200)
	{
		m_round->UpdateText("round " + std::string(crow::json::load(response.text)["round"]));
	}
}

void GameScene::GetChat()
{
	auto response{cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchmessages" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	)};
	if (response.status_code == 200)
	{
		auto messages{crow::json::load(response.text)};
		for (const auto& message : messages["messages"])
		{
			Color color = m_lastChatColor ? Color::DarkGray : Color::White;
			m_lastChatColor = !m_lastChatColor;
			m_chat->AddObject(new Label{Align::Left, Align::Up, color, Color::Black, 20,
							  static_cast<int16_t>((m_message.size()) / 20 + 2), m_console, std::string(message)});
		}
	}
}

void GameScene::GetGameStatus()
{
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchgamestatus" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	) };
	if (response.status_code == 200)
	{
		std::string status = std::string(crow::json::load(response.text)["status"]);
		if (status == "PickingWord")
		{
			m_gameStatus = GameStatus::PickingWord;
			m_gameStateLabel->UpdateText("PickingWord");
		}
		else if (status == "Drawing")
		{
			m_gameStatus = GameStatus::Drawing;
			m_gameStateLabel->UpdateText("Drawing");
		}
		else if (status == "Finished")
		{
			m_gameStatus = GameStatus::Finished;
			m_gameStateLabel->UpdateText("Finished");
		}
	}
}

void GameScene::SendMessageToServer()
{
	if (m_message.empty())
		return;

	auto response{cpr::Post(
		cpr::Url{ "http://localhost:18080/putmessageinchat" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()},
			{"message", m_message}
		}
	)};

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
	auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/leavegame" },
		cpr::Parameters{
			{"password", User::GetPassword()},
			{"username", User::GetUsername()}
		}
	)};
	m_nextScene = const_cast<std::type_info *>(&typeid(MenuScene));
}

void GameScene::SetAsDrawer()
{
	m_chatbox->CanBeSelected(false);

	switch (m_gameStatus)
	{
	case GameStatus::PickingWord:
		m_wordsToChoose->SetActive(true);
		SetWordsToPick();
		m_drawOptions->SetActive(false);
		m_colorsOptions->SetActive(false);
		m_widthOptions->SetActive(false);
		m_colorDisplay->SetActive(false);
		m_drawingBoard->CanBeSelected(false);
		break;
	case GameStatus::Drawing:
		m_wordsToChoose->Clear();
		m_selected = m_leaveButton;
		m_wordsToChoose->SetActive(false);
		m_drawOptions->SetActive(true);
		m_colorsOptions->SetActive(true);
		m_widthOptions->SetActive(true);
		m_colorDisplay->SetActive(true);
		m_drawingBoard->CanBeSelected(true);
		break;
	default:
		break;
	}
}

void GameScene::SetAsGuesser()
{
	m_drawOptions->SetActive(false);
	m_colorsOptions->SetActive(false);
	m_widthOptions->SetActive(false);
	m_drawingBoard->CanBeSelected(false);
	m_colorDisplay->SetActive(false);
	m_chatbox->CanBeSelected(true);
}

void GameScene::SetWordsToPick()
{
	if (m_wordsToChoose->IsEmpty())
	{
		auto response{ cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchwordstoguess" },
		cpr::Parameters{
				{"password", User::GetPassword()},
				{"username", User::GetUsername()}
			}
		) };
		if (response.status_code == 200)
		{
			auto words = crow::json::load(response.text);
			Button* prevButton{ nullptr };
			for (const auto& word : words["words"])
			{
				std::function<void(std::string)> buttonFunction = [](std::string word)
				{
					cpr::Post(
						cpr::Url{ "http://localhost:18080/putwordtoguess" },
						cpr::Parameters{
								{"password", User::GetPassword()},
								{"username", User::GetUsername()},
								{"word", word}
						}
					);
				};
				auto button{ new Button{ Align::Center, Align::Center, Color::DarkGreen, Color::Black, 5, 5,
					Color::Green, Color::Black, m_console, m_input, m_selected, std::string(word)} };
				m_wordsToChoose->AddObject(button);
				m_selected = button;
				button->SetFunctionOnActivate(buttonFunction, std::string(word));
				button->AddConections(nullptr, nullptr, prevButton, nullptr);
				if(prevButton)
					prevButton->AddConections(nullptr, nullptr, nullptr, button);
				prevButton = button;
			}
		}
	}
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
	m_gameStatus = GameStatus::PickingWord;
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
	m_players = new VerticalLayout{2, 5, Align::Center, Align::Up, Color::White, 20, 70, m_console, 0};
	m_objects.emplace_back(m_players);

	// Chat layout
	m_chat = new VerticalLayout{138, 5, Align::Center, Align::Up, Color::White, 20, 77, m_console, 0};
	m_objects.emplace_back(m_chat);

	// Chatbox
	m_chatbox = new InputField{138, 83, Align::Left, Align::Up, Color::DarkGray, Color::Black, 20, 5,
								 Color::DarkGray, Color::Black, m_console, m_input, m_selected, m_message, 100};
	m_chatbox->SetFunctionOnActivate([this](std::string a) { SendMessageToServer(); });
	m_selectableObjects.emplace_back(m_chatbox);
	m_objects.emplace_back(m_chatbox);

	// Timer
	m_timer = new Label{2, 2, Align::Left, Align::Up, Color::Black, Color::White, 9, 1, m_console, "time: "};
	m_objects.emplace_back(m_timer);

	// Round
	m_round = new Label{122, 2, Align::Right, Align::Up, Color::Black, Color::White, 14, 1, m_console, "round 10 of 10"};
	m_objects.emplace_back(m_round);

	// Game state
	m_gameStateLabel = new Label{143, 2, Align::Right, Align::Up, Color::Black, Color::White, 15, 1, m_console, "Waiting"};
	m_objects.emplace_back(m_gameStateLabel);

	// Word
	m_displayWord = new Label{70, 2, Align::Center, Align::Up, Color::Black, Color::White, 20, 1, m_console, "CUVANT"};
	m_objects.emplace_back(m_displayWord);

	// Words to choose
	m_wordsToChoose = new HorizontalLayout{40, 37, Align::Center, Align::Up, Color::DarkGray, 80, 5, m_console, 2};
	m_wordsToChoose->SetActive(false);
	m_objects.emplace_back(m_wordsToChoose);

	// Color display
	m_colorDisplay = new ColorDisplay{24, 79, Color::Black, 7, 7, m_console};
	m_objects.emplace_back(m_colorDisplay);

	// Colors
	m_colorsOptions = new VerticalLayout{33, 77, Align::Left, Align::Up, Color::Black, 95, 11, m_console, 1};
	m_objects.emplace_back(m_colorsOptions);
	auto row1 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 95, 5, m_console, 1};
	m_colorsOptions->AddObject(row1);
	auto row2 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 95, 5, m_console, 1};
	m_colorsOptions->AddObject(row2);
	auto aux = new Button{Align::Center, Align::Center, Color::White, Color::White, 5, 5,
					Color::White, Color::White, m_console, m_input, m_selectedColorButton, ""};
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::White);
		m_drawingBoard->SetDrawColor(Color::White);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Pink, Color::Pink, 5, 5,
					Color::Pink, Color::Pink, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Pink);
		m_drawingBoard->SetDrawColor(Color::Pink);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Red, Color::Red, 5, 5,
					Color::Red, Color::Red, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Red);
		m_drawingBoard->SetDrawColor(Color::Red);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Orange, Color::Orange, 5, 5,
					Color::Orange, Color::Orange, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Orange);
		m_drawingBoard->SetDrawColor(Color::Orange);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Yellow, Color::Yellow, 5, 5,
					Color::Yellow, Color::Yellow, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Yellow);
		m_drawingBoard->SetDrawColor(Color::Yellow);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Green, Color::Green, 5, 5,
					Color::Green, Color::Green, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Green);
		m_drawingBoard->SetDrawColor(Color::Green);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Blue, Color::Blue, 5, 5,
					Color::Blue, Color::Blue, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Blue);
		m_drawingBoard->SetDrawColor(Color::Blue);
	});
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::Cyan, Color::Cyan, 5, 5,
					Color::Cyan, Color::Cyan, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Cyan);
		m_drawingBoard->SetDrawColor(Color::Cyan);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::Black, Color::White, 5, 5,
					Color::Black, Color::White, m_console, m_input, m_selectedColorButton, "BLACK"});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Black);
		m_drawingBoard->SetDrawColor(Color::Black);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::DarkGray, 5, 5,
					Color::DarkGray, Color::DarkGray, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkGray);
		m_drawingBoard->SetDrawColor(Color::DarkGray);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkRed, Color::DarkRed, 5, 5,
					Color::DarkRed, Color::DarkRed, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkRed);
		m_drawingBoard->SetDrawColor(Color::DarkRed);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkBrown, Color::DarkBrown, 5, 5,
					Color::DarkBrown, Color::DarkBrown, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkBrown);
		m_drawingBoard->SetDrawColor(Color::DarkBrown);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkPink, Color::DarkPink, 5, 5,
					Color::DarkPink, Color::DarkPink, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkPink);
		m_drawingBoard->SetDrawColor(Color::DarkPink);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGreen, Color::DarkGreen, 5, 5,
					Color::DarkGreen, Color::DarkGreen, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkGreen);
		m_drawingBoard->SetDrawColor(Color::DarkGreen);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkBlue, Color::DarkBlue, 5, 5,
					Color::DarkBlue, Color::DarkBlue, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::DarkBlue);
		m_drawingBoard->SetDrawColor(Color::DarkBlue);
	});
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::Purple, Color::Purple, 5, 5,
					Color::Purple, Color::Purple, m_console, m_input, m_selectedColorButton, ""});
	aux->SetFunctionOnActivate([this](std::string a)
	{
		m_colorDisplay->SetDisplayColor(Color::Purple);
		m_drawingBoard->SetDrawColor(Color::Purple);
	});
	m_selectableObjects.emplace_back(aux);

	// Width
	m_widthOptions = new VerticalLayout{87, 77, Align::Left, Align::Up, Color::Black, 11, 11, m_console, 1};
	m_objects.emplace_back(m_widthOptions);
	row1 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 11, 5, m_console, 1};
	m_widthOptions->AddObject(row1);
	row2 = new HorizontalLayout{Align::Left, Align::Up, Color::Black, 11, 5, m_console, 1};
	m_widthOptions->AddObject(row2);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedWidthButton, "4"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetPenWidth(4); });
	m_selectableObjects.emplace_back(aux);
	row1->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedWidthButton, "10"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetPenWidth(10); });
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedWidthButton, "18"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetPenWidth(18); });
	m_selectableObjects.emplace_back(aux);
	row2->AddObject(aux = new Button{Align::Center, Align::Center, Color::DarkGray, Color::Black, 5, 5,
					Color::DarkGray, Color::Black, m_console, m_input, m_selectedWidthButton, "26"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetPenWidth(26); });
	m_selectableObjects.emplace_back(aux);

	// Draw options
	m_drawOptions = new HorizontalLayout{105, 80, Align::Left, Align::Up, Color::Black, 31, 5, m_console, 1};
	m_objects.emplace_back(m_drawOptions);
	m_drawOptions->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedDrawOptionButton, "pen"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetOption(DrawingBoard::Option::draw); });
	m_selectableObjects.emplace_back(aux);
	m_drawOptions->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedDrawOptionButton, "fill"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->SetOption(DrawingBoard::Option::fill); });
	m_selectableObjects.emplace_back(aux);
	m_drawOptions->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedDrawOptionButton, "undo"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->Undo(); });
	m_selectableObjects.emplace_back(aux);
	m_drawOptions->AddObject(aux = new Button{Align::Center, Align::Center, Color::White, Color::Black, 7, 5,
					Color::White, Color::Black, m_console, m_input, m_selectedDrawOptionButton, "clear"});
	aux->SetFunctionOnActivate([this](std::string a){ m_drawingBoard->Clear(); });
	m_selectableObjects.emplace_back(aux);

	// Leave button
	m_leaveButton = new Button{2, 83, Align::Center, Align::Center, Color::Blue, Color::White, 11, 5,
							Color::DarkBlue, Color::White, m_console, m_input, m_selected, "LEAVE"};
	m_leaveButton->SetFunctionOnActivate([this](std::string a) { Leave(); });
	m_selectableObjects.emplace_back(m_leaveButton);
	m_objects.emplace_back(m_leaveButton);

	m_selected = m_leaveButton;
}

void GameScene::Update()
{
	while (m_nextScene == nullptr)
	{
		GetGameStatus();
		GetPlayers();
		GetRound();
		GetTimer();
		GetChat();
		
		Input();
		Display();
	}
}
