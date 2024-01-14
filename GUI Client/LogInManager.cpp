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
	if (m_firstShow) {
		m_nameInput = findChild<QLineEdit*>("enterNameLogInInput");
		m_passwordInput = findChild<QLineEdit*>("enterPasswordLogInInput");
		m_logInButton = findChild<QPushButton*>("logInButton");
		m_incorrectCredentialsLabel = findChild<QLabel*>("incorrectCredentialsLabel");
		m_togglePasswordView = findChild<QPushButton*>("toggleLogInPasswordViewButton");
		m_incorrectCredentialsLabel->clear();

		QObject::connect(m_logInButton, &QPushButton::released, this, &LogInManager::OnLogInCredentialsSent);
		QObject::connect(m_togglePasswordView, &QPushButton::released, this, &LogInManager::OnTogglePasswordView);

		m_firstShow = false;
	}
}

void LogInManager::OnLogInCredentialsSent() noexcept  
{
	std::string password = m_passwordInput->text().toUtf8().constData();
	std::string username = m_nameInput->text().toUtf8().constData();

    password = picosha2::hash256_hex_string(password);
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Parameters{
			{"password", password},
			{"username", username}
		}
	);
	if (response.status_code == 200) {
		m_nameInput->clear();
		m_passwordInput->clear();
		UserCredentials::SetCredentials(username, password);
		m_incorrectCredentialsLabel->clear();
		emit OnLogInCredentialsAccepted();
	}
	else {
		m_incorrectCredentialsLabel->setText(m_incorrectCredentialsText);
	}
}

void LogInManager::OnTogglePasswordView() noexcept
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
