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

	std::tuple <int, int, int> GetGameSettings();
	void showEvent(QShowEvent* event) override;
	void SetCode(QString code) noexcept;
	void SetLeaderStatus(bool isLeader) noexcept;

private:
	void CheckForNewPlayersJoined(std::atomic<bool>& stop);

private:
	std::atomic<bool> stop;
	bool firstShow { true };
	bool m_isLeader  { false };

	QComboBox* drawTimeComboBox{ new QComboBox{} };
	QComboBox* roundsComboBox{ new QComboBox{} };
	QComboBox* wordCountComboBox{ new QComboBox{} };

	QLineEdit* codeLineEdit { new QLineEdit{} };
	LobbyTable* lobbyTable{ new LobbyTable{} };

	QPushButton* startGameButton{ new QPushButton{} };
};