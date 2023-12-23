#pragma once

#include <QFrame>
#include <qpushbutton.h>
#include <qlineedit.h>

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

private:
	bool firstShow{ true };
	QLineEdit* nameInput;
	QLineEdit* passwordInput;
	QPushButton* signUpButton;
};
