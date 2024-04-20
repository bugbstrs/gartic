#pragma once

#include <QFrame>
#include <thread>
#include <atomic>
#include <chrono>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include "LobbyTable.h"

class LobbyFrame  : public QFrame
{
	Q_OBJECT

public:
	LobbyFrame(QWidget *parent);
	~LobbyFrame();

	std::tuple <int, int, int> GetGameSettings() const noexcept;
	void showEvent(QShowEvent* event) override;
	void SetCode(QString code) noexcept;
	void SetLeaderStatus(bool isLeader) noexcept;
	void ResetSettings() noexcept;
	void Clear();

private:
	void SendOrCheckForLobbyUpdates(std::atomic<bool>& stop);
	void SetLeaderSettings();
	void SetNonLeaderSettings();

signals:
	void OnGameStarted();
	void OnLobbyLeft();

private:
	std::atomic<bool> m_stop;
	bool m_leaveGame	{ false };
	bool m_firstShow  { true };
	bool m_isLeader { false };

	const std::string kWaitingToStart = "WaitingToStart";
	const std::string kStartedGame = "StartedGame";

	QComboBox* m_drawTimeComboBox{ new QComboBox{} };
	QComboBox* m_roundsComboBox{ new QComboBox{} };
	QComboBox* m_wordCountComboBox{ new QComboBox{} };

	QLineEdit* m_codeLineEdit { new QLineEdit{} };
	LobbyTable* m_lobbyTable{ new LobbyTable{} };

	QPushButton* m_startGameButton{ new QPushButton{} };
	QPushButton* m_leaveLobbyButton{ new QPushButton{} };
};