export module GameScene;

import <string>;

import HorizontalLayout;
import VerticalLayout;
import ColorDisplay;
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
	SelectableObject *m_selectedDrawOptionButton;
	SelectableObject *m_selectedColorButton;
	SelectableObject *m_selectedWidthButton;
	SelectableObject *m_selected;
	HorizontalLayout *m_wordsToChoose;
	VerticalLayout	 *m_users;
	VerticalLayout   *m_chat;
	DrawingBoard	 *m_drawingBoard;
	ColorDisplay	 *m_colorDisplay;
	String			  m_message;
	Label			 *m_displayWord;
	Label			 *m_gameState;
	Label			 *m_timer;
	Label			 *m_round;
	bool			  m_lastChatColor;//For alternating colors on chat

	void GetPlayers		();
	void GetTimer		();
	void GetRound		();
	void GetChat		();
	void SendMessageToServer();
	void GetDrawEvents	();
	void Leave			();
	void Input			() const override;
	void Start			()       override;
	void Update			()       override;
};
