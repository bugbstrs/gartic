module Scene;

Scene::Scene(ConsoleManager* console, InputManager* inputManager) :
    m_console { console      },
    m_input   { inputManager }
{}

Scene::~Scene()
{
    for(auto object : m_objects)
        delete object;
}

std::type_info* Scene::SetActive()
{
    Start();
    Update();

    return m_nextScene;
}

void Scene::Display() const
{
    for (auto object : m_objects)
        object->Draw();

    m_console->UpdateConsole();
}
