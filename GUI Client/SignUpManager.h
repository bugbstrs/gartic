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

protected:
	void OnSignUpCredentialsSent() noexcept;

signals:
	void OnSignUpCredentialsAccepted();

private:
	bool firstShow{ true };
	QLineEdit* nameInput{ new QLineEdit{} };
	QLineEdit* passwordInput{ new QLineEdit{} };
	QPushButton* signUpButton{ new QPushButton{} };
	QLabel* alreadyExistingAccountLabel{ new QLabel{} };
};
