#pragma once

#include <QFrame>
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

private:
	bool firstShow{ true };

	QComboBox* drawTimeComboBox{ new QComboBox{} };
	QComboBox* roundsComboBox{ new QComboBox{} };
	QComboBox* wordCountComboBox{ new QComboBox{} };
	QLineEdit* codeLineEdit { new QLineEdit{} };
};