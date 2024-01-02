#include "LogInManager.h"
#include <iomanip>


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

		QObject::connect(logInButton, &QPushButton::released, this, &LogInManager::OnSignUpCredentialsSent);
		firstShow = false;
	}
}

void LogInManager::OnSignUpCredentialsSent() noexcept  
{
	std::string password = passwordInput->text().toUtf8().constData();
	std::string username = nameInput->text().toUtf8().constData();
	/*auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Payload{
			{ "password", password },
			{ "username", username }
		}
	);*/
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
		emit OnLogInCredentialsAccepted();
	}
}