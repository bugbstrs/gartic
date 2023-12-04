#include "SignUpManager.h"

SignUpManager::SignUpManager(QWidget *parent)
	: QFrame(parent)
{}

SignUpManager::~SignUpManager()
{}

void SignUpManager::showEvent(QShowEvent* event) {
	nameInput = findChild<QLineEdit*>("enterNameInput");
	passwordInput = findChild<QLineEdit*>("enterPasswordInput");
	signUpButton = findChild<QPushButton*>("signUpButton");

	QObject::connect(signUpButton, &QPushButton::released, this, &SignUpManager::OnSignUpCredentialsSent);
}

void SignUpManager::OnSignUpCredentialsSent()
{
	/*nameInput->clear();
	passwordInput->clear();*/
}
