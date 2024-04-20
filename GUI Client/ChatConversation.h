#pragma once

#include <Qt6/QtWidgets/QTextBrowser>

class ChatConversation  : public QTextBrowser
{
	Q_OBJECT

public:
	//Constructor
	ChatConversation(QWidget *parent = nullptr);

	//Destructor
	~ChatConversation() = default;
};
