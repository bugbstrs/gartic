export module SceneManager;

import LoginScene;
import MenuScene;
import ConsoleManager;

import <memory>;

export class SceneManager
{
public:
	static void Start();

private:
	static std::unique_ptr<Scene> m_activeScene;
	static ConsoleManager* m_console;

	static void Update();
};