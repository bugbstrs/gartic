#pragma once

#include <Qt6/QtWidgets/QLineEdit>

class ChatWritingBox : public QLineEdit
{
	Q_OBJECT

public:
	//Constructor
	ChatWritingBox(QWidget *parent = nullptr);

	//Destructor
	~ChatWritingBox() = default;

public slots:
	void OnEnterPressed() noexcept;

signals: 
	void OnMessageSentToServer(const QString& newMessage);
};
