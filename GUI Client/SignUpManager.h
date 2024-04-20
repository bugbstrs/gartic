#pragma once

#include <Qt6/QtWidgets/QFrame>
#include <Qt6/QtWidgets/QPushButton>
#include <Qt6/QtWidgets/QLineEdit>
#include <Qt6/QtWidgets/QLabel>

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
	bool m_firstShow{ true };
	QLineEdit* m_nameInput{ new QLineEdit{} };
	QLineEdit* m_passwordInput{ new QLineEdit{} };
	QPushButton* m_signUpButton{ new QPushButton{} };
	QPushButton* m_togglePasswordView{ new QPushButton{} };
	QLabel* m_alreadyExistingAccountLabel{ new QLabel{} };
	QString m_incorrectCredentialsText{ "Credentials match existing account." };

	QIcon m_viewPasswordIcon{ QIcon(QPixmap(":/others/view_password")) };
	QIcon m_hidePasswordIcon{ QIcon(QPixmap(":/others/hide_password")) };
};
