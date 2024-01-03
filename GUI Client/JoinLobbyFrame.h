#pragma once

#include <QFrame>
#include <qlineedit.h>
#include <qpushbutton.h>

class JoinLobbyFrame  : public QFrame
{
	Q_OBJECT

public:
	JoinLobbyFrame(QWidget *parent);
	~JoinLobbyFrame();

	void showEvent(QShowEvent* event) override;

private:
	void OnLobbyCodeSentForVerification() noexcept;

signals:
	void OnLobbyCodeAccepted();

private:
	bool firstShow	{ true };

	QLineEdit* codeLineEdit			{ new QLineEdit{} };
	QPushButton* joinButton			{ new QPushButton{} };
};
