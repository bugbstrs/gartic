module WordsEntity;

WordsEntity::WordsEntity(const String& newName):
    name(newName)
{
}

void WordsEntity::SetName(const String& newName)
{
    this->name = newName;
}

String WordsEntity::GetName() const
{
    return name;
}
