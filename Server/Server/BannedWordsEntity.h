#pragma once
#include <string>

namespace http
{
	class BannedWordsEntity
	{
	public:
		BannedWordsEntity() = default;
		BannedWordsEntity(const std::string& newName);

		~BannedWordsEntity() = default;

		void SetId(int newId);
		void SetName(const std::string& newName);

		int			GetId()	  const;
		std::string GetName() const;

	private:
		int id;
		std::string name;
	};
}

