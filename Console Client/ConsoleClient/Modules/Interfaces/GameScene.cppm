export module GameScene;

#pragma region GameScene
import <string>;
import <vector>;
import <cstdint>;

export import Player;
export import Vocabulary;
export import GameStatus;
#pragma endregion imports

#pragma region GameScene
using PlayersVector = std::vector<Player>;
using String = std::string;
#pragma endregion using statements

export class GameScene
{
public:
	#pragma region GameScene
	GameScene() = default;
	GameScene(const GameScene& newGameScene);

	~GameScene() = default;
	#pragma endregion constructors & destructor

	#pragma region GameScene
	void SetGameStatus(GameStatus newGameStatus);
	void SetRoundNumber(uint16_t newRoundNumber);
	void SetPlayers(const PlayersVector& newPlayersVector);
	void SetPainter(const Player& newPlayer);
	void SetCurrentWord(const String& newCurrentWord);
	#pragma endregion setters

	#pragma region GameScene
	GameStatus GetGameStatus() const;
	uint16_t GetRoundNumber() const;
	PlayersVector GetPlayers() const;
	Player GetPainter() const;
	String GetCurrentWord() const;
	#pragma endregion getters

	#pragma region GameScene
	void AddPlayer(const Player& playerToAdd);
	void RemovePlayer(const Player& playerToRemove);
	void NextPainter();
	#pragma endregion functionality
private:
	GameStatus m_gameStatus;

	uint16_t m_roundNumber;
	
	PlayersVector m_players;
	Player m_painter;

	String m_currentWord;
	Vocabulary m_vocabulary;
};