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
	void showEvent(QShowEvent* event) override;

protected:
	void OnSignUpCredentialsSent() noexcept;

private:
	QLineEdit* nameInput	 { new QLineEdit{} };
	QLineEdit* passwordInput { new QLineEdit{} };
	QPushButton* logInButton { new QPushButton{} };
};
