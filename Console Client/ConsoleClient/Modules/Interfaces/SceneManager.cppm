export module SceneManager;

#pragma region SceneManager
import LoginScene;
import MenuScene;
import InputManager;
import ConsoleManager;

import <memory>;
#pragma endregion imports

using UniquePtrScene = std::unique_ptr<Scene>;

export class SceneManager
{
public:
	void Start();

private:
	UniquePtrScene m_activeScene;
	ConsoleManager* m_console;
	InputManager* m_input;

	void Update();
};