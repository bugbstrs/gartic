export module GameScene;

import <string>;
import <vector>;
import <cstdint>;

export import Player;
export import Vocabulary;
export import GameStatus;

using PlayersVector = std::vector<Player>;
using String = std::string;

export class GameScene
{
public:
	// Constructors
	GameScene() = default;
	GameScene(const GameScene& newGameScene);

	// Destructor
	~GameScene() = default;

	// Setters
	void SetGameStatus(GameStatus newGameStatus);
	void SetRoundNumber(uint16_t newRoundNumber);
	void SetPlayers(const PlayersVector& newPlayersVector);
	void SetPainter(const Player& newPlayer);
	void SetCurrentWord(const String& newCurrentWord);

	// Getters 
	GameStatus GetGameStatus() const;
	uint16_t GetRoundNumber() const;
	PlayersVector GetPlayers() const;
	Player GetPainter() const;
	String GetCurrentWord() const;

	// Others
	void AddPlayer(const Player& playerToAdd);
	void RemovePlayer(const Player& playerToRemove);
	void NextPainter();

private:
	GameStatus m_gameStatus;

	uint16_t m_roundNumber;
	
	PlayersVector m_players;
	Player m_painter;

	String m_currentWord;
	Vocabulary m_vocabulary;
};