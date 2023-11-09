module Scene;

std::type_info* Scene::SetActive()
{
	Start();
	Update();
	return m_nextScene;
}

Scene::~Scene()
{
	delete m_nextScene;
}
