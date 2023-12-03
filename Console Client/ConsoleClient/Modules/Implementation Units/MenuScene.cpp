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

    m_selected->CheckInput();
}

void MenuScene::Start()
{
    m_nextScene = nullptr;
    m_console->NewConsole(L"Menu", 60, 15);

    m_objects.emplace_back(new Label{30, 2, Align::Left, Color::Cyan, Color::Magenta, 6, 1, m_console, "GARTIC"});

    auto layout{new HorizontalLayout{20, 5, Align::Left, Color::Black, 23, 1, m_console, 0}};
    layout->AddObject(new Label{Align::Left, Color::Black, Color::White, 5, 1, m_console, "User:"});
    auto userField{new InputField{Align::Left, Color::Gray, Color::Black, 18, 1, Color::DarkBlue, Color::White,
                        m_console, m_input, m_selected, m_username}};
    userField->SetHoverColors(Color::Blue, Color::White);
    layout->AddObject(userField);
    m_selectableObjects.emplace_back(userField);

    m_objects.emplace_back(layout);

    layout = new HorizontalLayout{16, 6, Align::Left, Color::Black, 27, 1, m_console, 0};
    layout->AddObject(new Label{Align::Left, Color::Black, Color::White, 9, 1, m_console, "Password:"});
    auto passwordField{new InputField{Align::Left, Color::Gray, Color::Black, 18, 1, Color::DarkBlue, Color::White,
                        m_console, m_input, m_selected, m_password}};
    passwordField->SetHoverColors(Color::Blue, Color::White);
    layout->AddObject(passwordField);
    m_selectableObjects.emplace_back(passwordField);

    m_objects.emplace_back(layout);

    auto loginButton{new Button{25, 10, Align::Left, Color::DarkGray, Color::Green, 5, 1, Color::DarkBlue,
                        Color::White, m_console, m_input, m_selected, "LOGIN"}};
    loginButton->SetHoverColors(Color::Blue, Color::White);
    //loginButton->SetFunctionOnActivate();
    m_objects.emplace_back(loginButton);
    m_selectableObjects.emplace_back(loginButton);

    auto registerButton{new Button{36, 10, Align::Left, Color::DarkGray, Color::Cyan, 8, 1, Color::DarkBlue,
                        Color::White, m_console, m_input, m_selected, "REGISTER"}};
    registerButton->SetHoverColors(Color::Blue, Color::White);
    //loginButton->SetFunctionOnActivate();
    m_objects.emplace_back(registerButton);
    m_selectableObjects.emplace_back(registerButton);

    userField->SetConections(nullptr, passwordField, nullptr, nullptr);
    passwordField->SetConections(userField, loginButton, nullptr, nullptr);
    loginButton->SetConections(passwordField, nullptr, nullptr, registerButton);
    registerButton->SetConections(passwordField, nullptr, loginButton, nullptr);

    delete m_selected;
    m_selected = userField;

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