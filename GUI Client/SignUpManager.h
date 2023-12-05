#pragma once

#include <QFrame>
#include <qpushbutton.h>
#include <qlineedit.h>

class SignUpManager  : public QFrame
{
	Q_OBJECT

public:
	SignUpManager(QWidget *parent);
	~SignUpManager();

public slots:
	void showEvent(QShowEvent* event);

protected:
	void OnSignUpCredentialsSent();

private:
	QLineEdit* nameInput;
	QLineEdit* passwordInput;
	QPushButton* signUpButton;
};
