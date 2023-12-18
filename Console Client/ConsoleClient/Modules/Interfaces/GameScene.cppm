export module GameScene;

import VerticalLayout;
import DrawingBoard;
import MenuScene;
import Scene;

export class GameScene: public Scene
{
public:
	GameScene(ConsoleManager *console, InputManager *inputManager);

	~GameScene() = default;

private:
	SelectableObject *m_selected;
	VerticalLayout	 *m_users;
	VerticalLayout   *m_chat;
	DrawingBoard	 *m_drawingBoard;

	void GetPlayers		();
	void GetTimer		();
	void GetRound		();
	void GetChat		();
	void GetDrawEvents	();
	void Leave			();
	void Input			() const override;
	void Start			()       override;
	void Update			()       override;
};
