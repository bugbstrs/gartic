export module SceneManager;

import LoginScene;

export class SceneManager
{
public:
	static void Start();
private:
	static SceneType m_activeScene;

	static void Update();
};