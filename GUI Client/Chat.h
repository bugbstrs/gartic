#pragma once

#include <QFrame>
#include "ChatWritingBox.h"
#include "ChatConversation.h"

class Chat  : public QFrame
{
	Q_OBJECT

public:
	Chat(QWidget *parent);
	~Chat();

	void SetWordToGuess(QString wordToGuess);
	void IsDrawer(bool isDrawer);

protected:
	void showEvent(QShowEvent* event) override;

public slots:
	void OnConversationWaitingForUpdate(const QString& newMessage);

private:
	bool isDrawer;
	QString wordToGuess;
	ChatWritingBox* chatWritingBox;
	ChatConversation* chatConversation;
};
