#pragma once
#include "DrawEvent.h"

namespace http
{
    class Undo : public DrawEvent
    {
    public:
        Undo() = default;

        // Inherited via DrawEvent
        const std::string& Serialize() override;

        void Deserialize(const std::string&) override;
    };
}

