#include "doctest/doctest.h"
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

    TEST_CASE("class http::BannedWordsEntity") {
        BannedWordsEntity bwe;
        BannedWordsEntity bwe2("hello");

        REQUIRE(bwe.GetName() == "");
        REQUIRE(bwe2.GetName() == "hello");

        bwe.SetName("hello2");
        REQUIRE(bwe.GetName() == "hello2");
        bwe.SetId(1234324);
        REQUIRE(bwe.GetId() == 1234324);
    }
}

