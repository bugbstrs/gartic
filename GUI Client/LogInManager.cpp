#include "LogInManager.h"

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
	nameInput->clear();
	passwordInput->clear();
}