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
	if (firstShow) {
		drawTimeComboBox = findChild<QComboBox*>("drawTimeComboBox");
		roundsComboBox = findChild<QComboBox*>("roundsComboBox");
		wordCountComboBox = findChild<QComboBox*>("wordCountComboBox");
		codeLineEdit = findChild<QLineEdit*>("codeLineEdit");

		firstShow = false;
	}
}

void LobbyFrame::SetCode(QString codeText) noexcept
{
	codeLineEdit->setText(codeText);
}
