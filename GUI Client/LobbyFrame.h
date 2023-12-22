#pragma once

#include <QFrame>
#include <qcombobox.h>
#include "LobbyTable.h"

class LobbyFrame  : public QFrame
{
	Q_OBJECT

public:
	LobbyFrame(QWidget *parent);
	~LobbyFrame();

	std::tuple <int, int, int> GetGameSettings();
	void showEvent(QShowEvent* event) override;

private:
	QComboBox* drawTimeComboBox{ new QComboBox{} };
	QComboBox* roundsComboBox{ new QComboBox{} };
	QComboBox* wordCountComboBox{ new QComboBox{} };
};