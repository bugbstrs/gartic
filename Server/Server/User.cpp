#include "User.h"

using namespace http;

http::User::User(const std::string& newUsername):
	m_username{ newUsername }
{
}

void http::User::SetUsername(const std::string& newUsername)
{
	m_username = newUsername;
}

const std::string& http::User::GetUsername() const noexcept
{
	return m_username;
}

void http::User::SetActive()
{
	m_active.SetStartValue(kSecondsForBeingActive);
	m_active.SetStartTimeStamp(m_active.GetServerTime());
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
