#pragma once

#include <QLineEdit>

class ChatWritingBox : public QLineEdit
{
	Q_OBJECT

public:
	ChatWritingBox(QWidget *parent = nullptr);
	~ChatWritingBox();

public slots:
	void OnEnterPressed();

signals:
	void OnConversationWaitingForUpdate(const QString& message);
};
