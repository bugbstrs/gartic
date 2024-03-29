module SceneManager;

void SceneManager::Start()
{
    m_console     = new ConsoleManager();
    m_input       = new InputManager();
    m_activeScene = std::make_unique<LoginScene>(m_console, m_input);
    Update();
}

void SceneManager::Update()
{
    while (m_activeScene)
    {
        type_info* nextScene = m_activeScene->SetActive();

        if (nextScene == &typeid(LoginScene))
            m_activeScene = std::make_unique<LoginScene>(m_console, m_input);
        if (nextScene == &typeid(MenuScene))
            m_activeScene = std::make_unique<MenuScene>(m_console, m_input);
        if (nextScene == &typeid(LobbyScene))
            m_activeScene = std::make_unique<LobbyScene>(m_console, m_input);
        if (nextScene == &typeid(StatsScene))
            m_activeScene = std::make_unique<StatsScene>(m_console, m_input);
        if (nextScene == &typeid(GameScene))
            m_activeScene = std::make_unique<GameScene>(m_console, m_input);
        if (!nextScene)
            m_activeScene = nullptr;
    }
}