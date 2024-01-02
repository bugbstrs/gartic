#pragma once

#include <QFrame>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>

class SignUpManager  : public QFrame
{
	Q_OBJECT

public:
	SignUpManager(QWidget *parent);
	~SignUpManager() = default;

public slots:
	void showEvent(QShowEvent* event) override;

private:
	void OnSignUpCredentialsSent() noexcept;
	void OnTogglePasswordView() noexcept;

signals:
	void OnSignUpCredentialsAccepted();

private:
	bool firstShow{ true };
	QLineEdit* nameInput{ new QLineEdit{} };
	QLineEdit* passwordInput{ new QLineEdit{} };
	QPushButton* signUpButton{ new QPushButton{} };
	QPushButton* togglePasswordView{ new QPushButton{} };
	QLabel* alreadyExistingAccountLabel{ new QLabel{} };
	QString incorrectCredentialsText{ "Credentials match existing account." };

	QIcon viewPasswordIcon{ QIcon(QPixmap(":/others/view_password")) };
	QIcon hidePasswordIcon{ QIcon(QPixmap(":/others/hide_password")) };
};
