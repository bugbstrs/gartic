module InteractableObject;

bool InteractableObject::IsPointInside(COORD point)
{
    if (m_upLeftCorner.X <= point.X && m_upLeftCorner.X + m_width > point.X &&
        m_upLeftCorner.Y <= point.Y && m_upLeftCorner.Y + m_height > point.Y)
        return true;
    return false;
}

void InteractableObject::SetColor()
{
    if (IsPointInside(m_im->GetCurrentCursorPosition()))
        m_cm->SetColor(m_hoverBackgroundColor, m_hoverTextColor);
    else
        m_cm->SetColor(m_backgroundColor, m_textColor);
}