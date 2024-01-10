#pragma once
#include "DrawEvent.h"

namespace http
{
    class Fill : public DrawEvent
    {
    public:
        Fill(int newX, int newY, int newColor);

        // Inherited via DrawEvent
        const std::string& Serialize() override;

        void Deserialize(const std::string&);

    private:
        int m_x;
        int m_y;
        int m_color;

    };
}

