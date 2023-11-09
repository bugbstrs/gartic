export module SceneManager;

import LoginScene;
import MenuScene;
import <memory>;

export class SceneManager
{
public:
	static void Start();

private:
	static std::unique_ptr<Scene> m_activeScene;

	static void Update();
};