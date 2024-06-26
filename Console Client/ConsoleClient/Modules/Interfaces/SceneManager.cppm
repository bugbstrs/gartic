export module SceneManager;

#pragma region SceneManager
import ConsoleManager;
import InputManager;
import StatsScene;
import LobbyScene;
import LoginScene;
import MenuScene;
import GameScene;   

import <memory>;
#pragma endregion imports

using UniquePtrScene = std::unique_ptr<Scene>;

export class SceneManager
{
public:
    void Start();

private:
    ConsoleManager* m_console;
    InputManager*   m_input;
    UniquePtrScene  m_activeScene;

    void Update();
};