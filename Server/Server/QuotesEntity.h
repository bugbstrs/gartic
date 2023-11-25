#pragma once
#include<string>

namespace http
{
	class QuotesEntity
	{
	public:
		QuotesEntity() = default;
		QuotesEntity(const std::string& newName);

		~QuotesEntity() = default;

		void SetId(int newId);
		void SetName(const std::string& newName);

		int			GetId()	  const;
		std::string GetName() const;
	private:
		int id;
		std::string name;
	};
}

