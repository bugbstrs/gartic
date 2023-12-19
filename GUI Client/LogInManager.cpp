#include "LogInManager.h"

LogInManager::LogInManager(QWidget *parent)
	: QFrame { parent }
{}

LogInManager::~LogInManager()
{}

void LogInManager::showEvent(QShowEvent* event) {
	nameInput = findChild<QLineEdit*>("enterNameLogInInput");
	passwordInput = findChild<QLineEdit*>("enterPasswordLogInInput");
	logInButton = findChild<QPushButton*>("logInButton");

	QObject::connect(logInButton, &QPushButton::released, this, &LogInManager::OnSignUpCredentialsSent);
}

void LogInManager::OnSignUpCredentialsSent() noexcept  
{
	nameInput->clear();
	passwordInput->clear();
}
