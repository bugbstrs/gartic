export module SceneManager;

import LoginScene;
import MenuScene;

export class SceneManager
{
public:
	static void Start();
private:
	static SceneType m_activeScene;

	static void Update();
};