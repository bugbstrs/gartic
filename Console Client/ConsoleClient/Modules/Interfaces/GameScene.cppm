//export module GameScene;
//
//#pragma region GameScene
//import <cstdint>;
//import <string>;
//import <vector>;
//
//export import GameStatus;
//export import Player;
//export import Vocabulary;
//#pragma endregion imports
//
//#pragma region GameScene
//using PlayersVector = std::vector<Player>;
//using String        = std::string;
//#pragma endregion using statements
//
//export class GameScene
//{
//public:
//    #pragma region GameScene
//    GameScene() = default;
//    GameScene(const GameScene& newGameScene);
//
//    ~GameScene() = default;
//    #pragma endregion constructors & destructor
//
//    #pragma region GameScene
//    void SetCurrentWord (const String& newCurrentWord);
//    void SetGameStatus  (GameStatus newGameStatus);
//    void SetPainter     (const Player& newPlayer);
//    void SetPlayers     (const PlayersVector& newPlayersVector);
//    void SetRoundNumber (uint16_t newRoundNumber);
//    #pragma endregion setters
//
//    #pragma region GameScene
//    GameStatus    GetGameStatus()  const;
//    Player        GetPainter()     const;
//    PlayersVector GetPlayers()     const;
//    String        GetCurrentWord() const;
//    uint16_t      GetRoundNumber() const;
//    #pragma endregion getters
//
//    #pragma region GameScene
//    void AddPlayer    (const Player& playerToAdd);
//    void NextPainter  ();
//    void RemovePlayer (const Player& playerToRemove);
//    #pragma endregion functionality
//private:
//    GameStatus    m_gameStatus;
//    Player        m_painter;
//    PlayersVector m_players;
//    String        m_currentWord;
//    uint16_t      m_roundNumber;
//    Vocabulary    m_vocabulary;
//};