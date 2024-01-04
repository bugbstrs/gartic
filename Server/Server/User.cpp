#include "User.h"

using namespace http;

http::User::User()
{
	m_active = new Time(3, 20, 50);
}

http::User::User(const std::string& newUsername):
	m_username{ newUsername }
{
	m_active = new Time(5, 7, 10);
}

void http::User::SetUsername(const std::string& newUsername)
{
	m_username = newUsername;
}

const std::string& http::User::GetUsername() const noexcept
{
	return m_username;
}

Time* http::User::GetTime() const noexcept
{
	return m_active;
}

void http::User::SetActive()
{
	m_active->SetStartValue(kSecondsForBeingActive);
	m_active->SetStartTimeStamp(static_cast<float>(m_active->GetServerTime()));
}

bool http::User::operator==(const User& u1)
{
	return this->m_username == u1.m_username;
}

User http::User::operator=(const User& u1)
{
	this->m_username = u1.m_username;

	this->m_active = u1.m_active;

	return *this;
}
