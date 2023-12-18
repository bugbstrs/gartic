#include "Chat.h"
#include <qdatetime.h>

Chat::Chat(QWidget *parent)
	: QFrame{ parent }
{}

Chat::~Chat()
{
	delete m_chatConversation;
	delete m_chatWritingBox;
}

void Chat::OnConversationWaitingForUpdate(const QString& newMessage) noexcept
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString formattedTime = currentTime.toString("hh:mm");
	QString formattedMessage;
	if (newMessage != m_wordToGuess)
		formattedMessage = QString("[%1] <b>You:</b> <b style='color: blue;'>%2</b><br>").arg(formattedTime, newMessage);
	else {
		formattedMessage = QString("<b style='color: white; background-color: green; padding: 5px;'> You have guessed the word</b><br>");
		m_chatWritingBox->setDisabled(true);
	}
    m_chatConversation->insertHtml(formattedMessage);
}

void Chat::SetWordToGuess(QString wordToGuess) noexcept
{
	m_wordToGuess = wordToGuess;
}

void Chat::SetChatConfigurationAccordingToPlayerType(bool isDrawer) noexcept
{
	if (isDrawer)
		m_chatWritingBox->setDisabled(true);
}

void Chat::showEvent(QShowEvent* event)
{
	m_chatWritingBox = findChild<ChatWritingBox*>("chatWritingBox");
	m_chatConversation = findChild<ChatConversation*>("chatConversation"); 
	QObject::connect(m_chatWritingBox, &ChatWritingBox::OnConversationWaitingForUpdateSignal, this, &Chat::OnConversationWaitingForUpdate);
	QWidget::showEvent(event);
}
