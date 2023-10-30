module SceneManager;

import ConsoleManager;

SceneType SceneManager::m_activeScene;

void SceneManager::Start()
{
	ConsoleManager::Initialize();
	m_activeScene = LOGIN;
	Update();
}

void SceneManager::Update()
{
	while (m_activeScene != NOT_A_SCENE)
	{
		SceneType nextScene = NOT_A_SCENE;
		switch (m_activeScene)
		{
		case LOGIN:
			nextScene = LoginScene::SetActive();
			break;
		case MENU:
			break;
		case STATS:
			break;
		case GAME:
			break;
		default:
			//Scene not found
			break;
		}
		m_activeScene = nextScene;
	}
}