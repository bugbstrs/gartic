#pragma once

#include <QFrame>
#include <qlineedit.h>
#include <qpushbutton.h>

class LogInManager  : public QFrame
{
	Q_OBJECT

public:
	LogInManager(QWidget *parent);
	~LogInManager();

public slots:
	void showEvent(QShowEvent* event);

protected:
	void OnSignUpCredentialsSent();

private:
	QLineEdit* nameInput;
	QLineEdit* passwordInput;
	QPushButton* logInButton;
};
