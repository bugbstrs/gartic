module Scene;

Scene::Scene(ConsoleManager* console)
	:m_console{ console }
{}

Scene::~Scene()
{}

std::type_info* Scene::SetActive()
{
	Start();
	Update();
	return m_nextScene;
}
