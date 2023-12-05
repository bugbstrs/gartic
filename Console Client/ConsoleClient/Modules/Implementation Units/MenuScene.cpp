module MenuScene;

import <Windows.h>;

import Label;
import Button;
import InputField;
import HorizontalLayout;

using Color = ColorType;

MenuScene::MenuScene(ConsoleManager* console, InputManager* inputManager) :
    Scene{ console, inputManager }
{}

void MenuScene::Display() const
{
    for (auto object : m_objects)
        object->Draw();

    m_console->UpdateConsole();
}

void MenuScene::Input() const
{
    m_input->ReadInput();

    for (auto object : m_selectableObjects)
        object->CheckCursor();

    //m_selected->CheckInput();
}

void MenuScene::Start()
{
    m_nextScene = nullptr;
    m_console->NewConsole(L"Menu", 70, 20);


    m_objects.emplace_back(new Label{30, 2, Align::Left, Align::Up, Color::Cyan, Color::Magenta, 6, 1, m_console, "GARTIC"});


    auto createLobbyButton{ new Button{25, 7, Align::Center, Align::Center, Color::DarkGray, Color::Green,
                            14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Create Lobby"} };
    createLobbyButton->SetHoverColors(Color::Blue, Color::White);
    //createLobbyButton->SetFunctionOnActivate(std::bind(&LoginScene::Login, this));
    m_objects.emplace_back(createLobbyButton);
    m_selectableObjects.emplace_back(createLobbyButton);


    auto layout{ new HorizontalLayout{25, 12, Align::Right, Align::Center, Color::Black, 30, 3, m_console, 0} };

    auto joinLobbyButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          14, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Join Lobby"} };
    joinLobbyButton->SetHoverColors(Color::Blue, Color::White);
    //joinLobbyButton->SetFunctionOnActivate(std::bind(&LoginScene::Login, this));
    layout->AddObject(joinLobbyButton);
    m_selectableObjects.emplace_back(joinLobbyButton);

    auto codeField{ new InputField{Align::Left, Align::Center, Color::Gray, Color::Black, 5, 3, Color::DarkBlue, Color::White,
                        m_console, m_input, m_selected, m_username, 5} };
    codeField->SetHoverColors(Color::Blue, Color::White);
    layout->AddObject(codeField);
    m_selectableObjects.emplace_back(codeField);

    m_objects.emplace_back(layout);

    Display();
}

void MenuScene::Update()
{
    while (true)
    {
        Input();
        Display();
    }
}