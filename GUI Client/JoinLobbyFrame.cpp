#include "JoinLobbyFrame.h"

JoinLobbyFrame::JoinLobbyFrame(QWidget *parent)
	: QFrame(parent)
{}

JoinLobbyFrame::~JoinLobbyFrame()
{}

void JoinLobbyFrame::showEvent(QShowEvent * event)
{
	if (m_firstShow) {
		m_joinButton = findChild<QPushButton*>("joinButton");
		m_codeLineEdit = findChild<QLineEdit*>("codeInputLineEdit");
		m_gameAlreadyStarted = findChild<QLabel*>("gameAlreadyStartedLabel");

		m_gameAlreadyStarted->hide();

		QObject::connect(m_joinButton, &QPushButton::released, this, &JoinLobbyFrame::OnLobbyCodeSentForVerification);

		m_firstShow = false;
	}
}

void JoinLobbyFrame::OnLobbyCodeSentForVerification() noexcept
{
	emit OnLobbyCodeAccepted(m_codeLineEdit->text().toUtf8().constData());
	m_codeLineEdit->clear();
}
