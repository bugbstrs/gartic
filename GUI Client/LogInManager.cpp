#include "LogInManager.h"

LogInManager::LogInManager(QWidget *parent)
	: QFrame(parent)
{}

LogInManager::~LogInManager()
{}

void LogInManager::showEvent(QShowEvent* event) {
	nameInput = findChild<QLineEdit*>("enterNameInput_2");
	passwordInput = findChild<QLineEdit*>("enterPasswordInput_2");
	logInButton = findChild<QPushButton*>("logInButton_2");

	QObject::connect(logInButton, &QPushButton::released, this, &LogInManager::OnSignUpCredentialsSent);
}

void LogInManager::OnSignUpCredentialsSent()
{
	/*nameInput->clear();
	passwordInput->clear();*/
}
