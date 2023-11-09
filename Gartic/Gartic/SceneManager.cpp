module SceneManager;

import ConsoleManager;
import SceneType;

SceneType SceneManager::m_activeScene;

void SceneManager::Start()
{
	ConsoleManager::Initialize();
	m_activeScene = SceneType::LOGIN;
	Update();
}

void SceneManager::Update()
{
	while (m_activeScene != SceneType::NOT_A_SCENE)
	{
		SceneType nextScene = SceneType::NOT_A_SCENE;
		switch (m_activeScene)
		{
		case SceneType::LOGIN:
			//nextScene = LoginScene::SetActive();
			break;
		case SceneType::MENU:
			break;
		case SceneType::STATS:
			break;
		case SceneType::GAME:
			break;
		default:
			//Scene not found
			break;
		}
		m_activeScene = nextScene;
	}
}