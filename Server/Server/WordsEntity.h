#pragma once
#include <string>

namespace http
{
	class WordsEntity
	{
	public:
		WordsEntity() = default;
		WordsEntity(const std::string& newName);

		~WordsEntity() = default;

		void SetId(int newId);
		void SetName(const std::string& newName);

		int			GetId()	  const;
		std::string GetName() const;

	private:
		int			id;
		std::string name;
	};
}
