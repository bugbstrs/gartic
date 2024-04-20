#include "Chat.h"
#include <thread>
#include <crow.h>
#include <qdatetime.h>
#include "UserCredentials.h"

Chat::Chat(QWidget *parent)
	: QFrame{ parent },
	m_stop(false)
{}

Chat::~Chat()
{
	delete m_chatConversation;
	delete m_chatWritingBox;
}

void Chat::AddMessageInChat(const QString& newMessage) noexcept
{
	QMetaObject::invokeMethod(this, [this, newMessage]() {
		QDateTime currentTime = QDateTime::currentDateTime();
		QString formattedTime = currentTime.toString("hh:mm");
		QString name = newMessage.section(": ", 0, 0);
		QString messageSent = newMessage.section(": ", 1);
		QString formattedMessage;
		if (newMessage != kFoundWord)
			formattedMessage = QString("[%1] <b>%2:</b> <b style='color: blue;'>%3</b><br>").arg(formattedTime, name, messageSent);
		else {
			formattedMessage = QString("<b style='color: white; background-color: green; padding: 5px;'> %1 </b><br>").arg(newMessage);
		}
		m_chatConversation->insertHtml(formattedMessage);
		m_chatConversation->moveCursor(QTextCursor::End);
	}, Qt::QueuedConnection);
}

void Chat::StopCheckingForUpdates()
{
	m_stop.store(true);
}

void Chat::SetWordToGuess(QString wordToGuess) noexcept
{
	m_wordToGuess = wordToGuess;
}

void Chat::SetChatConfigurationAccordingToPlayerType(bool isDrawer) noexcept
{
	QMetaObject::invokeMethod(this, [this, isDrawer]() {
		if (isDrawer)
			m_chatWritingBox->setDisabled(true);
	}, Qt::QueuedConnection);
}

void Chat::ToggleAccessToWritingMessages(bool canWrite)
{
	QMetaObject::invokeMethod(this, [this, canWrite]() {
		m_chatWritingBox->clear();
		m_chatWritingBox->setDisabled(!canWrite);
	}, Qt::QueuedConnection);
}

void Chat::Clear() noexcept
{
	m_chatConversation->clear();
	m_chatWritingBox->clear();
}

void Chat::showEvent(QShowEvent* event)
{
	if (m_firstShow) {
		m_chatWritingBox = findChild<ChatWritingBox*>("chatWritingBox");
		m_chatConversation = findChild<ChatConversation*>("chatConversation");
		m_firstShow = false;
		QObject::connect(m_chatWritingBox, &ChatWritingBox::OnMessageSentToServer, this, [this](const QString& messageSent) {
			QDateTime currentTime = QDateTime::currentDateTime();
			QString formattedTime = currentTime.toString("hh:mm");
			QString formattedMessage;
			formattedMessage = QString("[%1] <b>You:</b> <b style='color: blue;'>%3</b><br>").arg(formattedTime, messageSent);
			m_chatConversation->insertHtml(formattedMessage);
			m_chatConversation->moveCursor(QTextCursor::End);
		});
	}

	m_stop.store(false);

	std::thread checkForMessagesUpdates(&Chat::CheckForNewMessages, this, std::ref(m_stop));
	checkForMessagesUpdates.detach();
}

void Chat::CheckForNewMessages(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto newMessages = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchmessages" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (newMessages.status_code == 200) {
			auto messages = crow::json::load(newMessages.text);
			if (messages.has("messages")) {
				for (int index{ 0 }; index < messages["messages"].size(); index++) {
					AddMessageInChat(QString::fromUtf8(std::string(messages["messages"][index])));
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	if (stop.load()) {

	}
}
