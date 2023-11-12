export module MenuScene;

export import Scene;

export class MenuScene : public Scene
{
public:
	// Constructors
	MenuScene(ConsoleManager* console);

	// Destructors
	~MenuScene();

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
	void Display() const override;
};