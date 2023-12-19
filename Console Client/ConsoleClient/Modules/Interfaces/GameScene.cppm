export module GameScene;

import <string>;

import VerticalLayout;
import DrawingBoard;
import InputField;
import MenuScene;
import Button;
import Label;
import Scene;

using String = std::string;

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
	String			  m_message;
	bool			  m_lastChatColor;//For alternating colors on chat

	void GetPlayers		();
	void GetTimer		();
	void GetRound		();
	void GetChat		();
	void SendMessage	();
	void GetDrawEvents	();
	void Leave			();
	void Input			() const override;
	void Start			()       override;
	void Update			()       override;
};
