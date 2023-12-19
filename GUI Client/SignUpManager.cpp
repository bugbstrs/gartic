#include "SignUpManager.h"

SignUpManager::SignUpManager(QWidget *parent)
	: QFrame{ parent }
{}

void SignUpManager::showEvent(QShowEvent* event) {
	nameInput = findChild<QLineEdit*>("enterNameSignUpInput");
	passwordInput = findChild<QLineEdit*>("enterPasswordSignUpInput");
	signUpButton = findChild<QPushButton*>("signUpButton");

	QObject::connect(signUpButton, &QPushButton::released, this, &SignUpManager::OnSignUpCredentialsSent);
}

void SignUpManager::OnSignUpCredentialsSent() noexcept
{
	nameInput->clear();
	passwordInput->clear();
}
