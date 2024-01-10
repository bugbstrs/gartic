#pragma once

#include <QFrame>
#include <atomic>
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
	void StopCheckingForUpdates(bool value);
	void SetWordToGuess(QString wordToGuess) noexcept;
	void SetChatConfigurationAccordingToPlayerType(bool isDrawer) noexcept;

protected:
	void showEvent(QShowEvent* event) override;

private:
	void CheckForNewMessages(std::atomic<bool>& stop);
	void AddMessageInChat(const QString& newMessage) noexcept;

signals:
	void OnWordGuessed();

private:
	std::atomic<bool> stop;
	bool firstShow { true };
	QString m_wordToGuess				 {};
	ChatWritingBox* m_chatWritingBox     { new ChatWritingBox{} };
	ChatConversation* m_chatConversation { new ChatConversation{} };
};
