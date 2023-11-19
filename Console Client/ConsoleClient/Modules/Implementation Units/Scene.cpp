module Scene;

Scene::Scene(ConsoleManager* console, InputManager* inputManager) :
    m_console { console      },
    m_input   { inputManager }
{}

std::type_info* Scene::SetActive()
{
    Start();
    Update();

    return m_nextScene;
}
