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
		Time GetTime() const noexcept;

		void SetActive();

	private:
		const float kSecondsForBeingActive = 5.0;

	private:
		std::string m_username;

		Time m_active;
	};
}

