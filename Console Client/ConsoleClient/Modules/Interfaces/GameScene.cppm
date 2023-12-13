export module GameScene;

import Scene;

export class GameScene: public Scene
{
public:
	GameScene(ConsoleManager *console, InputManager *inputManager);

	~GameScene() = default;

private:
	SelectableObject *m_selected;

	void GetPlayers		();
	void GetTimer		();
	void GetRound		();
	void GetChat		();
	void GetDrawEvents	();
	void Input			() const override;
	void Start			()       override;
	void Update			()       override;
};
