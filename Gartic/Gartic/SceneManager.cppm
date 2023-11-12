export module SceneManager;

import LoginScene;
import MenuScene;
import ConsoleManager;

import <memory>;

using UniquePtrScene = std::unique_ptr<Scene>;

export class SceneManager
{
public:
	static void Start();

private:
	static UniquePtrScene m_activeScene;
	static ConsoleManager* m_console;

	static void Update();
};

// TODO: remove static