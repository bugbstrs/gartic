#include "SignUpManager.h"
#include "UserCredentials.h"

SignUpManager::SignUpManager(QWidget *parent)
	: QFrame{ parent }
{}

void SignUpManager::showEvent(QShowEvent* event) {
	if (firstShow) {
		nameInput = findChild<QLineEdit*>("enterNameSignUpInput");
		passwordInput = findChild<QLineEdit*>("enterPasswordSignUpInput");
		signUpButton = findChild<QPushButton*>("signUpButton");
		alreadyExistingAccountLabel = findChild<QLabel*>("alreadyExistingAccountLabel");
		togglePasswordView = findChild<QPushButton*>("toggleSignUpPasswordViewButton");
		alreadyExistingAccountLabel->clear();

		QObject::connect(signUpButton, &QPushButton::released, this, &SignUpManager::OnSignUpCredentialsSent);
		QObject::connect(togglePasswordView, &QPushButton::released, this, &SignUpManager::OnTogglePasswordView);

		firstShow = false;
	}
}

void SignUpManager::OnSignUpCredentialsSent() noexcept
{
	std::string password = passwordInput->text().toUtf8().constData();
	std::string username = nameInput->text().toUtf8().constData();
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Parameters{
			{"password", password},
			{"username", username}
		}
	);
	if (response.status_code == 201) {
		nameInput->clear();
		passwordInput->clear();
		alreadyExistingAccountLabel->clear();
		emit OnSignUpCredentialsAccepted();
	}
	else {
		alreadyExistingAccountLabel->setText(incorrectCredentialsText);
	}
}

void SignUpManager::OnTogglePasswordView() noexcept
{
	if (passwordInput->echoMode() == QLineEdit::Password) {
		togglePasswordView->setIcon(hidePasswordIcon);
		passwordInput->setEchoMode(QLineEdit::Normal);
	}
	else {
		togglePasswordView->setIcon(viewPasswordIcon);
		passwordInput->setEchoMode(QLineEdit::Password);
	}
}
