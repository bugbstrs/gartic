#pragma once

#include <QFrame>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <string>

class LogInManager  : public QFrame
{
	Q_OBJECT

public:
	LogInManager(QWidget *parent);
	~LogInManager();

public slots:
	void showEvent(QShowEvent* event) override;

protected:
	void OnLogInCredentialsSent() noexcept;

signals:
	void OnLogInCredentialsAccepted(const std::string& username, const std::string& password);

private:
	bool firstShow{ true };
	QLineEdit* nameInput	 { new QLineEdit{} };
	QLineEdit* passwordInput { new QLineEdit{} };
	QPushButton* logInButton { new QPushButton{} };
	QLabel* incorrectCredentialsLabel{ new QLabel{} };
};
