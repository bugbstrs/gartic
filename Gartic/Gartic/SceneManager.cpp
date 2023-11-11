module SceneManager;

import ConsoleManager;

std::unique_ptr<Scene> SceneManager::m_activeScene;

void SceneManager::Start()
{
	ConsoleManager::Initialize();
	m_activeScene = std::make_unique<LoginScene>();
	Update();
}

void SceneManager::Update()
{
	while (m_activeScene)
	{
		type_info* nextScene = m_activeScene->SetActive();

		if (nextScene == &typeid(LoginScene))
			m_activeScene = std::make_unique<LoginScene>();
		if (nextScene == &typeid(MenuScene))
			m_activeScene = std::make_unique<MenuScene>();
		if (!nextScene)
			m_activeScene = nullptr;
	}
}