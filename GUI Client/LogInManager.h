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
	void OnLogInCredentialsAccepted();

private:
	void OnLogInCredentialsSent() noexcept;
	void OnTogglePasswordView() noexcept;

private:
	bool m_firstShow					  { true };
	QLineEdit* m_nameInput				  { new QLineEdit{} };
	QLineEdit* m_passwordInput			  { new QLineEdit{} };
	QPushButton* m_logInButton			  { new QPushButton{} };
	QPushButton* m_togglePasswordView	  { new QPushButton{} };
	QLabel* m_incorrectCredentialsLabel   { new QLabel{} };
	QString m_incorrectCredentialsText    { "Incorrect username or password. Please try again." };

	QIcon m_viewPasswordIcon			  { QIcon(QPixmap(":/others/view_password")) };
	QIcon m_hidePasswordIcon			  { QIcon(QPixmap(":/others/hide_password")) };
};
