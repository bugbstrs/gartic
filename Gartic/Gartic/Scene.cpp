module Scene;

SceneType Scene::SetActive()
{
	Start();
	Update();
	return m_nextScene;
}