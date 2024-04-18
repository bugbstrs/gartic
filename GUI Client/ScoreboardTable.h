#pragma once

#include <QTableWidget>
#include <unordered_map>

class ScoreboardTable  : public QTableWidget
{
	Q_OBJECT

public:
	ScoreboardTable(QWidget *parent = nullptr);
	~ScoreboardTable();

	void AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby) noexcept;
	void SetPointsToPlayer(const QString& username, int numberOfPoints) noexcept;
	void MarkGuessedForPlayer(const QString& username) noexcept;

	std::vector <std::tuple<QIcon, QString, int, QColor>> GetPlayersOrdered() const noexcept;

	void StopCheckingForPlayers(bool leavedGame);
	void ResetGuessedIcons() noexcept;
	void ClearScoreboard() noexcept;
	void CheckForScoreboardUpdates(std::atomic<bool>& stop);

	void showEvent(QShowEvent* event) override;

signals:
	void OnGameFinished();

private:
	void MarkDrawer(const QString& username);


private:
	std::atomic<bool> m_stop;
	bool m_firstShow																			 { true };
	bool m_leavedGame																			 { false };
	QFont m_nameFont																			 {};
	QFont m_pointsFont																			 {};
	QFont m_yourNameFont																		 {};
	std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> m_players						 {};
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> m_takenAvatars;
	std::vector <std::tuple<QIcon, QString, int, QColor>> m_playersToSendForResultsDisplaying	 {};
	QIcon m_drawerIcon;
};
