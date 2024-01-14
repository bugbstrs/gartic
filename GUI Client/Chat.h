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
	void ToggleAccessToWritingMessages(bool canWrite);
	void StopLookingForUpdates();
	void Clear() noexcept;

protected:
	void showEvent(QShowEvent* event) override;

private:
	void CheckForNewMessages(std::atomic<bool>& stop);
	void AddMessageInChat(const QString& newMessage) noexcept;

signals:
	void OnWordGuessed();

private:
	const QString kFoundWord = "[Server]: You guessed the word!";
	std::atomic<bool> m_stop;
	bool m_firstShow { true };
	QString m_wordToGuess				 {};
	ChatWritingBox* m_chatWritingBox     { new ChatWritingBox{} };
	ChatConversation* m_chatConversation { new ChatConversation{} };
};
