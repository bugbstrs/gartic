#pragma once

#include <QFrame>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>

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
	void OnLobbyCodeAccepted(std::string codeText);

private:
	bool firstShow	{ true };

	QLineEdit* codeLineEdit			{ new QLineEdit{} };
	QPushButton* joinButton			{ new QPushButton{} };
	QLabel* gameAlreadyStarted		{ new QLabel{} };
};
