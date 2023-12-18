#include "ChatWritingBox.h"

ChatWritingBox::ChatWritingBox(QWidget *parent)
	: QLineEdit{ parent }
{
	connect(this, &ChatWritingBox::returnPressed, this, &ChatWritingBox::OnEnterPressed);
}

void ChatWritingBox::OnEnterPressed() noexcept { 
	emit OnConversationWaitingForUpdateSignal(text());
	clear();
}
