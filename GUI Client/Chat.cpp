#include "Chat.h"
#include <qdatetime.h>

Chat::Chat(QWidget *parent)
	: QFrame(parent),
	chatWritingBox(new ChatWritingBox()),
	chatConversation(new ChatConversation())
{
}

void Chat::OnConversationWaitingForUpdate(const QString& newMessage) {
	QDateTime currentTime = QDateTime::currentDateTime();
	QString formattedTime = currentTime.toString("hh:mm");
	QString formattedMessage = QString("[%1] <b>You:</b> <b style='color: blue;'>%2</b><br>").arg(formattedTime, newMessage);
    chatConversation->insertHtml(formattedMessage);
}

Chat::~Chat()
{}

void Chat::showEvent(QShowEvent * event)
{
	chatWritingBox = findChild<ChatWritingBox*>("chatWritingBox");
	chatConversation = findChild<ChatConversation*>("chatConversation"); 
	QObject::connect(chatWritingBox, &ChatWritingBox::OnConversationWaitingForUpdate, this, &Chat::OnConversationWaitingForUpdate);
	QWidget::showEvent(event);
}
