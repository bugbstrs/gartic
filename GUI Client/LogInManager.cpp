#include "LogInManager.h"
#include <iomanip>
#include "UserCredentials.h"

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
		incorrectCredentialsLabel->setStyleSheet("color: transparent");

		QObject::connect(logInButton, &QPushButton::released, this, &LogInManager::OnLogInCredentialsSent);
		firstShow = false;
	}
}

void LogInManager::OnLogInCredentialsSent() noexcept  
{
	std::string password = passwordInput->text().toUtf8().constData();
	std::string username = nameInput->text().toUtf8().constData();
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
		incorrectCredentialsLabel->setStyleSheet("color: transparent");
		emit OnLogInCredentialsAccepted(username, password);
	}
	else {
		incorrectCredentialsLabel->setStyleSheet("color: red");
	}
}