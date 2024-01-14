#include "LogInManager.h"
#include <iomanip>
#include "UserCredentials.h"
#include "picosha2.h"

LogInManager::LogInManager(QWidget *parent)
	: QFrame { parent }
{}

LogInManager::~LogInManager()
{}

void LogInManager::showEvent(QShowEvent* event) {
	if (firstShow) {
		nameInput = findChild<QLineEdit*>("enterNameLogInInput");
		passwordInput = findChild<QLineEdit*>("enterPasswordLogInInput");
		logInButton = findChild<QPushButton*>("logInButton");
		incorrectCredentialsLabel = findChild<QLabel*>("incorrectCredentialsLabel");
		togglePasswordView = findChild<QPushButton*>("toggleLogInPasswordViewButton");
		incorrectCredentialsLabel->clear();

		QObject::connect(logInButton, &QPushButton::released, this, &LogInManager::OnLogInCredentialsSent);
		QObject::connect(togglePasswordView, &QPushButton::released, this, &LogInManager::OnTogglePasswordView);

		firstShow = false;
	}
}

void LogInManager::OnLogInCredentialsSent() noexcept  
{
	std::string password = passwordInput->text().toUtf8().constData();
	std::string username = nameInput->text().toUtf8().constData();

    password = picosha2::hash256_hex_string(password);
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Parameters{
			{"password", password},
			{"username", username}
		}
	);
	if (response.status_code == 200) {
		nameInput->clear();
		passwordInput->clear();
		UserCredentials::SetCredentials(username, password);
		incorrectCredentialsLabel->clear();
		emit OnLogInCredentialsAccepted();
	}
	else {
		incorrectCredentialsLabel->setText(incorrectCredentialsText);
	}
}

void LogInManager::OnTogglePasswordView() noexcept
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
