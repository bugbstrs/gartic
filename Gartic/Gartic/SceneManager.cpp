module SceneManager;

std::unique_ptr<Scene> SceneManager::m_activeScene;
ConsoleManager* SceneManager::m_console;

void SceneManager::Start()
{
	m_console = new ConsoleManager();
	m_activeScene = std::make_unique<LoginScene>(m_console);
	Update();
}

void SceneManager::Update()
{
	while (m_activeScene)
	{
		type_info* nextScene = m_activeScene->SetActive();

		if (nextScene == &typeid(LoginScene))
			m_activeScene = std::make_unique<LoginScene>(m_console);
		if (nextScene == &typeid(MenuScene))
			m_activeScene = std::make_unique<MenuScene>(m_console);
		if (!nextScene)
			m_activeScene = nullptr;
	}
}