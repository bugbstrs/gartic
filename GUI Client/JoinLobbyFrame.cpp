#include "JoinLobbyFrame.h"

JoinLobbyFrame::JoinLobbyFrame(QWidget *parent)
	: QFrame(parent)
{}

JoinLobbyFrame::~JoinLobbyFrame()
{}

void JoinLobbyFrame::showEvent(QShowEvent * event)
{
	if (firstShow) {
		joinButton = findChild<QPushButton*>("joinButton");
		codeLineEdit = findChild<QLineEdit*>("codeInputLineEdit");
		gameAlreadyStarted = findChild<QLabel*>("gameAlreadyStartedLabel");

		gameAlreadyStarted->hide();

		QObject::connect(joinButton, &QPushButton::released, this, &JoinLobbyFrame::OnLobbyCodeSentForVerification);

		firstShow = false;
	}
}

void JoinLobbyFrame::OnLobbyCodeSentForVerification() noexcept
{
	emit OnLobbyCodeAccepted(codeLineEdit->text().toUtf8().constData());
	codeLineEdit->clear();
}
