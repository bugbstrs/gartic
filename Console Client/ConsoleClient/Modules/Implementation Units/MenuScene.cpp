module MenuScene;

import <Windows.h>;

import Label;
import Button;
import LoginScene;
import LobbyScene;
import InputField;
import VerticalLayout;
import HorizontalLayout;

using Color = ColorType;

MenuScene::MenuScene(ConsoleManager* console, InputManager* inputManager) :
    Scene{ console, inputManager }
{}

void MenuScene::CreateLobby()
{
    m_nextScene = const_cast<std::type_info*>(&typeid(LobbyScene));
}

void MenuScene::JoinLobby()
{
    m_nextScene = const_cast<std::type_info*>(&typeid(LobbyScene));
}

void MenuScene::Logout()
{
    m_nextScene = const_cast<std::type_info*>(&typeid(LoginScene));
}

void MenuScene::Stats()
{
    //m_nextScene = const_cast<std::type_info*>(&typeid(StatsScene));
}

void MenuScene::Input() const
{
    m_input->ReadInput();

    for (auto object : m_selectableObjects)
        object->CheckCursor();

    m_selected->CheckInput();
}

void MenuScene::Start()
{
    m_lobbyCode = "";
    m_nextScene = nullptr;
    m_console->SetWindowed();
    m_console->NewConsole(L"Menu", 50, 25);
    m_console->SetConsoleFont(L"MS Gothic", 15, 15);


    m_objects.emplace_back(new Label{23, 2, Align::Left, Align::Up, Color::Cyan, Color::Magenta, 6, 1, m_console, "GARTIC"});


    auto createLobbyButton{ new Button{20, 6, Align::Center, Align::Center, Color::DarkGray, Color::Green,
                            14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Create Lobby"} };
    createLobbyButton->SetHoverColors(Color::Blue, Color::White);
    createLobbyButton->SetFunctionOnActivate(std::bind(&MenuScene::CreateLobby, this));
    m_objects.emplace_back(createLobbyButton);
    m_selectableObjects.emplace_back(createLobbyButton);


    auto Hlayout{ new HorizontalLayout{20, 11, Align::Left, Align::Center, Color::Black, 30, 3, m_console, 0} };

    auto joinLobbyButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Join Lobby"} };
    joinLobbyButton->SetHoverColors(Color::Blue, Color::White);
    joinLobbyButton->SetFunctionOnActivate(std::bind(&MenuScene::JoinLobby, this));
    Hlayout->AddObject(joinLobbyButton);
    m_selectableObjects.emplace_back(joinLobbyButton);

    auto codeField{ new InputField{Align::Center, Align::Center, Color::Gray, Color::Black, 7, 3,
                    Color::DarkBlue, Color::White, m_console, m_input, m_selected, m_lobbyCode, 5} };
    codeField->SetHoverColors(Color::Blue, Color::White);
    Hlayout->AddObject(codeField);
    m_selectableObjects.emplace_back(codeField);

    m_objects.emplace_back(Hlayout);


    auto statsButton{ new Button{20, 16, Align::Center, Align::Center, Color::DarkGray, Color::Green,
                            14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Stats"} };
    statsButton->SetHoverColors(Color::Blue, Color::White);
    statsButton->SetFunctionOnActivate(std::bind(&MenuScene::Stats, this));
    m_objects.emplace_back(statsButton);
    m_selectableObjects.emplace_back(statsButton);

    
    auto Vlayout = new VerticalLayout{ 22, 21, Align::Right, Align::Up, Color::Black, 28, 4, m_console, 0};

    Vlayout->AddObject(new Label{Align::Right, Align::Up, Color::Black, Color::White,
                           28, 1, m_console, "Logged as:" + User::GetUsername()});
    auto LogoutButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          8, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Logout"} };
    LogoutButton->SetHoverColors(Color::Blue, Color::White);
    LogoutButton->SetFunctionOnActivate(std::bind(&MenuScene::Logout, this));
    m_selectableObjects.emplace_back(LogoutButton);
    Vlayout->AddObject(LogoutButton);

    m_objects.emplace_back(Vlayout);


    m_selected = createLobbyButton;

    Display();
}

void MenuScene::Update()
{
    while (m_nextScene == nullptr)
    {
        Input();
        Display();
    }
}