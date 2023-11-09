export module MenuScene;

export import Scene;
export import SceneType;

export class MenuScene : public Scene
{
private:
	enum Options
	{
		PLAY,
		STATS,
		LOGOUT
	};
	Options m_option;

	void Start() override;
	void Update() override;
	void Display() override;
};