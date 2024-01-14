#pragma once

#include <QTableWidget>
#include <unordered_map>

class ScoreboardTable  : public QTableWidget
{
	Q_OBJECT

public:
	ScoreboardTable(QWidget *parent = nullptr);
	~ScoreboardTable();

	void AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby);
	void AddPointsToPlayerWithIndex(uint8_t index);
	void SetPointsToPlayer(const QString& username, int numberOfPoints);
	void MarkGuessedForPlayer(const QString& username);

	std::vector <std::tuple<QIcon, QString, int, QColor>> GetPlayersOrdered();

	void StopCheckingForPlayers();
	void ResetGuessedIcons();
	void ClearScoreboard();
	void CheckForScoreboardUpdates(std::atomic<bool>& stop);

	void showEvent(QShowEvent* event) override;

private:

private:
	std::atomic<bool> m_stop;
	bool m_firstShow																			 { true };
	int m_currentIndex = 0;
	QFont m_nameFont																			 {};
	QFont m_pointsFont																			 {};
	QFont m_yourNameFont																		 {};
	std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> m_players						 {};
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> m_takenAvatars;
	std::vector <std::tuple<QIcon, QString, int, QColor>> m_playersToSendForResultsDisplaying	 {};
};
