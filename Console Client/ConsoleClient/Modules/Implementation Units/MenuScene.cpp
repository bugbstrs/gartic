#include <cpr/cpr.h>

module MenuScene;

import <Windows.h>;

import Label;
import Button;
import LoginScene;
import LobbyScene;
import StatsScene;
import InputField;
import VerticalLayout;
import HorizontalLayout;

using Color = ColorType;

MenuScene::MenuScene(ConsoleManager* console, InputManager* inputManager) :
    Scene{ console, inputManager }
{}

void MenuScene::CreateLobby()
{
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/createlobby" },
        cpr::Parameters{
            {"username", User::GetUsername()},
            {"password", User::GetPassword()}
        }
    );
    if (response.status_code == 200)
    {
        m_nextScene = const_cast<std::type_info*>(&typeid(LobbyScene));
    }
    else
    {

    }
}

void MenuScene::JoinLobby()
{
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/joinlobby" },
        cpr::Parameters{
            {"username", User::GetUsername()},
            {"password", User::GetPassword()},
            {"code", m_lobbyCode}
        }
    );
    if (response.status_code == 200)
    {
        m_nextScene = const_cast<std::type_info*>(&typeid(LobbyScene));
    }
    else
    {

    }
}

void MenuScene::Logout()
{
    User::Initialize("", "");
    m_nextScene = const_cast<std::type_info*>(&typeid(LoginScene));
}

void MenuScene::Stats()
{
    m_nextScene = const_cast<std::type_info*>(&typeid(StatsScene));
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
    m_console->ResetColorsPalette();
    m_console->AddColorsToPalette({Cyan, Purple, White, Black, DarkGray, DarkBlue, Blue, Green});
    m_console->SetWindowed();
    m_console->NewConsole(L"Menu", 50, 25);
    m_console->SetConsoleFont(L"MS Gothic", 15, 15);

    // Title
    m_objects.emplace_back(new Label{23, 2, Align::Left, Align::Up, Color::Cyan, Color::Purple, 6, 1, m_console, "GARTIC"});

    // Create lobby
    auto createLobbyButton{ new Button{20, 6, Align::Center, Align::Center, Color::DarkGray, Color::Green,
                            14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Create Lobby"} };
    createLobbyButton->SetHoverColors(Color::Blue, Color::White);
    createLobbyButton->SetFunctionOnActivate([this]() { CreateLobby(); });
    m_objects.emplace_back(createLobbyButton);
    m_selectableObjects.emplace_back(createLobbyButton);

    // Join lobby
    auto Hlayout{ new HorizontalLayout{20, 11, Align::Left, Align::Center, Color::Black, 30, 3, m_console, 0} };

    auto joinLobbyButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Join Lobby"} };
    joinLobbyButton->SetHoverColors(Color::Blue, Color::White);
    joinLobbyButton->SetFunctionOnActivate([this]() { JoinLobby(); });
    Hlayout->AddObject(joinLobbyButton);
    m_selectableObjects.emplace_back(joinLobbyButton);

    // Lobby code
    auto codeField{ new InputField{Align::Center, Align::Center, Color::Gray, Color::Black, 7, 3,
                    Color::DarkBlue, Color::White, m_console, m_input, m_selected, m_lobbyCode, 11} };
    codeField->SetHoverColors(Color::Blue, Color::White);
    Hlayout->AddObject(codeField);
    m_selectableObjects.emplace_back(codeField);

    m_objects.emplace_back(Hlayout);

    // Stats
    auto statsButton{ new Button{20, 16, Align::Center, Align::Center, Color::DarkGray, Color::Green,
                            14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Stats"} };
    statsButton->SetHoverColors(Color::Blue, Color::White);
    statsButton->SetFunctionOnActivate([this]() { Stats(); });
    m_objects.emplace_back(statsButton);
    m_selectableObjects.emplace_back(statsButton);

    // User
    auto Vlayout = new VerticalLayout{ 22, 21, Align::Right, Align::Up, Color::Black, 28, 4, m_console, 0};

    Vlayout->AddObject(new Label{Align::Right, Align::Up, Color::Black, Color::White,
                           28, 1, m_console, "Logged as:" + User::GetUsername()});
    // Logout
    auto LogoutButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          8, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Logout"} };
    LogoutButton->SetHoverColors(Color::Blue, Color::White);
    LogoutButton->SetFunctionOnActivate([this]() { Logout(); });
    m_selectableObjects.emplace_back(LogoutButton);
    Vlayout->AddObject(LogoutButton);

    m_objects.emplace_back(Vlayout);


    createLobbyButton->SetConections(nullptr, joinLobbyButton, nullptr, nullptr);
    joinLobbyButton->SetConections(createLobbyButton, statsButton, nullptr, codeField);
    codeField->SetConections(nullptr, nullptr, joinLobbyButton, nullptr);
    statsButton->SetConections(joinLobbyButton, LogoutButton, nullptr, nullptr);
    LogoutButton->SetConections(statsButton, nullptr, nullptr, nullptr);

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