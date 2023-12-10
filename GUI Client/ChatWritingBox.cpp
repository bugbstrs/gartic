#include "ChatWritingBox.h"

ChatWritingBox::ChatWritingBox(QWidget *parent)
	: QLineEdit{ parent }
{
	connect(this, &ChatWritingBox::returnPressed, this, &ChatWritingBox::OnEnterPressed);
}

ChatWritingBox::~ChatWritingBox()
{
}

void ChatWritingBox::OnEnterPressed() {
	emit OnConversationWaitingForUpdateSignal(text());
	clear();
}
