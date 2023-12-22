#include "LobbyFrame.h"

LobbyFrame::LobbyFrame(QWidget *parent)
	: QFrame(parent)
{}

LobbyFrame::~LobbyFrame()
{}

std::tuple<int, int, int> LobbyFrame::GetGameSettings()
{
	return { drawTimeComboBox->currentText().toInt(), roundsComboBox->currentText().toInt(), wordCountComboBox->currentText().toInt() };
}

void LobbyFrame::showEvent(QShowEvent * event)
{
	drawTimeComboBox = findChild<QComboBox*>("drawTimeComboBox");
	roundsComboBox = findChild<QComboBox*>("roundsComboBox");
	wordCountComboBox = findChild<QComboBox*>("wordCountComboBox");
}
