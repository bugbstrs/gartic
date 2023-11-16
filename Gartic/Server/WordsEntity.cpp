module WordsEntity;

WordsEntity::WordsEntity(const String& newName, const Vector& newPreviousScores, uint16_t newPoints):
    name(newName),
    previousScores(newPreviousScores),
    points(newPoints)
{
}

String WordsEntity::GetName() const
{
    return name;
}

Vector WordsEntity::GetPreviousScores() const
{
    return previousScores;
}

uint16_t WordsEntity::GetPoints() const
{
    return points;
}
