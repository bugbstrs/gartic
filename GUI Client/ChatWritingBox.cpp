#include "ChatWritingBox.h"
#include "UserCredentials.h"

ChatWritingBox::ChatWritingBox(QWidget *parent)
	: QLineEdit{ parent }
{
	connect(this, &ChatWritingBox::returnPressed, this, &ChatWritingBox::OnEnterPressed);
}

void ChatWritingBox::OnEnterPressed() noexcept { 
	auto putMessageInChat = cpr::Post(
		cpr::Url{ "http://localhost:18080/putmessageinchat" },
		cpr::Parameters{
			{"username", UserCredentials::GetUsername()},
			{"password", UserCredentials::GetPassword()},
			{"message", std::string(text().toUtf8().constData())}
		}
	);
	emit OnMessageSentToServer(text());
	clear();
}
