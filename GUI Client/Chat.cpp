#include "Chat.h"
#include <qdatetime.h>

Chat::Chat(QWidget *parent)
	: QFrame{ parent },
	chatWritingBox{ new ChatWritingBox{} },
	chatConversation{ new ChatConversation{} }
{
}

void Chat::OnConversationWaitingForUpdate(const QString& newMessage) {
	QDateTime currentTime = QDateTime::currentDateTime();
	QString formattedTime = currentTime.toString("hh:mm");
	QString formattedMessage;
	if (newMessage != wordToGuess)
		formattedMessage = QString("[%1] <b>You:</b> <b style='color: blue;'>%2</b><br>").arg(formattedTime, newMessage);
	else {
		formattedMessage = QString("<b style='color: white; background-color: green; padding: 5px;'> You have guessed the word</b><br>");
		chatWritingBox->setDisabled(true);
	}
    chatConversation->insertHtml(formattedMessage);
}

Chat::~Chat()
{}

void Chat::SetWordToGuess(QString wordToGuess)
{
	this->wordToGuess = wordToGuess;
}

void Chat::IsDrawer(bool isDrawer)
{
	if (isDrawer)
		chatWritingBox->setDisabled(true);
}

void Chat::showEvent(QShowEvent* event)
{
	chatWritingBox = findChild<ChatWritingBox*>("chatWritingBox");
	chatConversation = findChild<ChatConversation*>("chatConversation"); 
	QObject::connect(chatWritingBox, &ChatWritingBox::OnConversationWaitingForUpdateSignal, this, &Chat::OnConversationWaitingForUpdate);
	QWidget::showEvent(event);
}
