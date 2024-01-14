module StatsScene;

import <Windows.h>;
import MenuScene;
import Button;

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
    m_console->ResetColorsPalette();
    m_console->AddColorsToPalette({White, Black, DarkBlue, DarkGray, Green, Blue});
    m_console->NewConsole(L"Stats", 50, 25);
    m_console->SetConsoleFont(L"Consolas", 11, 24);

    // Back Button
    auto BackButton{ new Button{Align::Center, Align::Center, Color::DarkGray, Color::Green,
                          6, 3, Color::DarkBlue, Color::White, m_console, m_input, m_selected, "Back"} };
    BackButton->SetHoverColors(Color::Blue, Color::White);
    BackButton->SetFunctionOnActivate([this](std::string a) {Back(); });
    m_selectableObjects.emplace_back(BackButton);
    m_objects.emplace_back(BackButton);

    m_selected = BackButton;

    Display();
}

void StatsScene::Update()
{
    while (m_nextScene == nullptr)
    {
        Input();
        Display();
    }
}
