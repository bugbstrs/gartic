module MenuScene;

import <Windows.h>;

import Label;

MenuScene::MenuScene(ConsoleManager* console, InputManager* inputManager) :
    Scene{ console, inputManager }
{}

void MenuScene::Display() const
{
    for (auto object : m_objects)
        object->Draw();

    m_console->UpdateConsole();
}

void MenuScene::Start()
{
    m_nextScene = nullptr;
    m_console->NewConsole(L"Menu", 200, 40);
    m_objects.emplace_back(new Label{ 1, 1, Align::Left, ColorType::Blue, ColorType::Red,
                                      5, 10, m_console, "Acesta este un test" });
    Display();
}

void MenuScene::Update()
{
    while (true)
        Display();
}