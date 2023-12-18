#pragma once

#include <QLineEdit>

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
	void OnConversationWaitingForUpdateSignal(const QString& message);
};
