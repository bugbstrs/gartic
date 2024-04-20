#pragma once

#include <Qt6/QtWidgets/QFrame>
#include <Qt6/QtWidgets/QLineEdit>
#include <Qt6/QtWidgets/QPushButton>
#include <Qt6/QtWidgets/QLabel>

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
	bool m_firstShow	{ true };

	QLineEdit* m_codeLineEdit			{ new QLineEdit{} };
	QPushButton* m_joinButton			{ new QPushButton{} };
	QLabel* m_gameAlreadyStarted		{ new QLabel{} };
};
