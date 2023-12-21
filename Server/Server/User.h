#pragma once

#include <string>

#include "Time.h"

namespace http
{
	class User
	{
	public:
		User() = default;
		User(const std::string& newUsername);

		~User() = default;

		std::string GetUsername() const noexcept;

		void SetActive();
		// TODO: implement
		bool operator == (const User& u1) { return true; }
		User operator = (const User& u1) { return *this; }

	private:
		const float kSecondsForBeingActive = 5.0;

	private:
		std::string m_username;

		Time m_active;
	};
}

