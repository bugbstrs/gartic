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

signals:
	void OnLogInCredentialsAccepted(const std::string& username, const std::string& password);

private:
	void OnLogInCredentialsSent() noexcept;
	void OnTogglePasswordView() noexcept;

private:
	bool firstShow					  { true };
	QLineEdit* nameInput			  { new QLineEdit{} };
	QLineEdit* passwordInput		  { new QLineEdit{} };
	QPushButton* logInButton		  { new QPushButton{} };
	QPushButton* togglePasswordView	  { new QPushButton{} };
	QLabel* incorrectCredentialsLabel { new QLabel{} };
	QString incorrectCredentialsText  { "Incorrect username or password. Please try again." };

	QIcon viewPasswordIcon			  { QIcon(QPixmap(":/others/view_password")) };
	QIcon hidePasswordIcon			  { QIcon(QPixmap(":/others/hide_password")) };
};
