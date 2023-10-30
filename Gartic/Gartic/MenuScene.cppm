export module MenuScene;

export import SceneType;

class MenuScene
{
public:
	static SceneType SetActive();
private:
	enum Options
	{
		PLAY,
		STATS,
		LOGOUT
	};
	static Options m_option;
	static SceneType m_nextScene;

	static void Start();
	static void Update();
	static void Display();
};