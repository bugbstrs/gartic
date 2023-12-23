#pragma once

#include <QFrame>
#include "ChatWritingBox.h"
#include "ChatConversation.h"

class Chat  : public QFrame
{
	Q_OBJECT

public:

	//Constructor
	Chat(QWidget *parent = nullptr);

	//Destructor
	~Chat();

	//Functionality
	void SetWordToGuess(QString wordToGuess) noexcept;
	void SetChatConfigurationAccordingToPlayerType(bool isDrawer) noexcept;

protected:
	void showEvent(QShowEvent* event) override;

public slots:
	void OnConversationWaitingForUpdate(const QString& newMessage) noexcept;

private:
	bool firstShow{ true };
	QString m_wordToGuess				 {};
	ChatWritingBox* m_chatWritingBox     { new ChatWritingBox{} };
	ChatConversation* m_chatConversation { new ChatConversation{} };
};
