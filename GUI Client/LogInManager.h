#pragma once

#include <QFrame>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>

class LogInManager  : public QFrame
{
	Q_OBJECT

public:
	LogInManager(QWidget *parent);
	~LogInManager();

public slots:
	void showEvent(QShowEvent* event) override;

protected:
	void OnSignUpCredentialsSent() noexcept;

signals:
	void OnLogInCredentialsAccepted();

private:
	bool firstShow{ true };
	QLineEdit* nameInput	 { new QLineEdit{} };
	QLineEdit* passwordInput { new QLineEdit{} };
	QPushButton* logInButton { new QPushButton{} };
};
