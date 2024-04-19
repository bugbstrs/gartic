#include "SignUpManager.h"
#include "UserCredentials.h"
#include "picosha2.h"

SignUpManager::SignUpManager(QWidget *parent)
	: QFrame{ parent }
{}

void SignUpManager::showEvent(QShowEvent* event) {
	if (m_firstShow) {
		m_nameInput = findChild<QLineEdit*>("enterNameSignUpInput");
		m_passwordInput = findChild<QLineEdit*>("enterPasswordSignUpInput");
		m_signUpButton = findChild<QPushButton*>("signUpButton");
		m_alreadyExistingAccountLabel = findChild<QLabel*>("alreadyExistingAccountLabel");
		m_togglePasswordView = findChild<QPushButton*>("toggleSignUpPasswordViewButton");

		QObject::connect(m_signUpButton, &QPushButton::released, this, &SignUpManager::OnSignUpCredentialsSent);
		QObject::connect(m_togglePasswordView, &QPushButton::released, this, &SignUpManager::OnTogglePasswordView);

		m_firstShow = false;
	}
	m_alreadyExistingAccountLabel->clear();
}

void SignUpManager::OnSignUpCredentialsSent() noexcept
{
	std::string password = m_passwordInput->text().toUtf8().constData();
	std::string username = m_nameInput->text().toUtf8().constData();

    password = picosha2::hash256_hex_string(password);
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Parameters{
			{"password", password},
			{"username", username}
		}
	);
	if (response.status_code == 201) {
		m_nameInput->clear();
		m_passwordInput->clear();
		m_alreadyExistingAccountLabel->clear();
		emit OnSignUpCredentialsAccepted();
	}
	else {
		m_alreadyExistingAccountLabel->setText(m_incorrectCredentialsText);
	}
}

void SignUpManager::OnTogglePasswordView() noexcept
{
	if (m_passwordInput->echoMode() == QLineEdit::Password) {
		m_togglePasswordView->setIcon(m_hidePasswordIcon);
		m_passwordInput->setEchoMode(QLineEdit::Normal);
	}
	else {
		m_togglePasswordView->setIcon(m_viewPasswordIcon);
		m_passwordInput->setEchoMode(QLineEdit::Password);
	}
}
