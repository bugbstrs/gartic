module WordsEntity;

WordsEntity::WordsEntity(const String& newName):
    name(newName)
{
}

String WordsEntity::GetName() const
{
    return name;
}
