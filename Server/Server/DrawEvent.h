#pragma once

#include<string>

#include <format>
#include <sstream>

namespace http
{
	class DrawEvent
	{
	public:
		virtual const std::string& Serialize() = 0;
	};
}

