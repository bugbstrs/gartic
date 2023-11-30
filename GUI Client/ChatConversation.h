#pragma once

#include <QTextBrowser>

class ChatConversation  : public QTextBrowser
{
	Q_OBJECT

public:
	ChatConversation(QWidget *parent = nullptr);
	~ChatConversation();

public slots:
	/*void OnEnterPressed();*/
};
