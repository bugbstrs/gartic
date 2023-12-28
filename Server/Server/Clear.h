#pragma once
#include "DrawEvent.h"

namespace http
{
	class Clear : public DrawEvent
	{
	public:
		Clear() = default;
		
		// Inherited via DrawEvent
		const std::string& Serialize() override;

		void Deserialize(const std::string&) override;
	};
}

