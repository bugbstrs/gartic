module StatsScene;

import <Windows.h>;

import MenuScene;

using Color = ColorType;

StatsScene::StatsScene(ConsoleManager* console, InputManager* inputManager) :
    Scene{ console, inputManager }
{}

void StatsScene::GetStatistics()
{

}

void StatsScene::Back()
{
    m_nextScene = const_cast<std::type_info*>(&typeid(MenuScene));
}

void StatsScene::Input() const
{
    m_input->ReadInput();

    for (auto object : m_selectableObjects)
        object->CheckCursor();

    m_selected->CheckInput();
}

void StatsScene::Start()
{
    m_nextScene = nullptr;
    m_console->SetWindowed();
    m_console->NewConsole(L"Menu", 50, 25);
    m_console->SetConsoleFont(L"MS Gothic", 15, 15);
}

void StatsScene::Update()
{
    while (m_nextScene == nullptr)
    {
        Input();
        Display();
    }
}
