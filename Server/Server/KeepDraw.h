#pragma once
#include "DrawEvent.h"

namespace http
{
    class KeepDraw : public DrawEvent
    {
        KeepDraw(int newX, int newY);

        // Inherited via DrawEvent
        const std::string& Serialize() override;

        void Deserialize(const std::string&) override;

    private:
        int m_x;
        int m_y;

    };
}

