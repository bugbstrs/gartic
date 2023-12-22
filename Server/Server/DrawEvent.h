#pragma once

#include<string>

#include <format>

namespace http
{
	class DrawEvent
	{
	public:

		virtual const std::string& Serialize() = 0;
	};
}

