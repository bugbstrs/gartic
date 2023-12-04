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
	void OnConversationWaitingForUpdateSignal(const QString& message);
};
