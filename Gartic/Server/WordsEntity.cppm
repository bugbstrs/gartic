export module WordsEntity;

import <cstdint>;
import <vector>;
import <string>;

using String = std::string;
using Vector = std::vector<uint16_t>;

export class WordsEntity
{
public:
	WordsEntity() = default;
	WordsEntity(const String& newName);

	~WordsEntity() = default;

	String GetName() const;

private:
	String name;
};
