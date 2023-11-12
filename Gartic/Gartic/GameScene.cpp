module GameScene;

GameScene::GameScene(const GameScene& newGameScene)
{
	*this = newGameScene;
}

void GameScene::SetGameStatus(GameStatus newGameStatus)
{
	m_gameStatus = newGameStatus;
}

void GameScene::SetRoundNumber(uint16_t newRoundNumber)
{
	m_roundNumber = newRoundNumber;
}

void GameScene::SetPlayers(const PlayersVector& newPlayersVector)
{
	m_players = newPlayersVector;
}

void GameScene::SetPainter(const Player& newPlayer)
{
	m_painter = newPlayer;
}

void GameScene::SetCurrentWord(const String& newCurrentWord)
{
	m_currentWord = newCurrentWord;
}

GameStatus GameScene::GetGameStatus() const
{
	return m_gameStatus;
}

uint16_t GameScene::GetRoundNumber() const
{
	return m_roundNumber;
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

void GameScene::AddPlayer(const Player& playerToAdd)
{
	m_players.push_back(playerToAdd);
}

void GameScene::RemovePlayer(const Player& playerToRemove)
{
	if (!m_players.size()) return;

	PlayersVector::iterator it = std::find(m_players.begin(), m_players.end(), playerToRemove);

	m_players.erase(it);
}

void GameScene::NextPainter()
{
	if (!m_players.size()) return;

	PlayersVector::iterator it = std::find(m_players.begin(), m_players.end(), m_painter);

	m_painter = it != m_players.end() ? *std::next(it) : m_painter;
}

