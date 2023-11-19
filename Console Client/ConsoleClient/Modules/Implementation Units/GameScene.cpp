module GameScene;

GameScene::GameScene(const GameScene& newGameScene)
{
    *this = newGameScene;
}

void GameScene::SetCurrentWord(const String& newCurrentWord)
{
    m_currentWord = newCurrentWord;
}

void GameScene::SetGameStatus(GameStatus newGameStatus)
{
    m_gameStatus = newGameStatus;
}

void GameScene::SetPainter(const Player& newPlayer)
{
    m_painter = newPlayer;
}

void GameScene::SetPlayers(const PlayersVector& newPlayersVector)
{
    m_players = newPlayersVector;
}

void GameScene::SetRoundNumber(uint16_t newRoundNumber)
{
    m_roundNumber = newRoundNumber;
}

GameStatus GameScene::GetGameStatus() const
{
    return m_gameStatus;
}

PlayersVector GameScene::GetPlayers() const
{
    return m_players;
}

Player GameScene::GetPainter() const
{
    return m_painter;
}

String GameScene::GetCurrentWord() const
{
    return m_currentWord;
}

uint16_t GameScene::GetRoundNumber() const
{
    return m_roundNumber;
}

void GameScene::AddPlayer(const Player& playerToAdd)
{
    m_players.push_back(playerToAdd);
}

void GameScene::NextPainter()
{
    if (!m_players.size()) return;

    PlayersVector::iterator it = std::find(m_players.begin(), m_players.end(), m_painter);

    m_painter = it != m_players.end() ? *std::next(it) : m_painter;
}

void GameScene::RemovePlayer(const Player& playerToRemove)
{
    if (!m_players.size()) return;

    PlayersVector::iterator it = std::find(m_players.begin(), m_players.end(), playerToRemove);

    m_players.erase(it);
}