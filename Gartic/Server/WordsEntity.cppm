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
	WordsEntity(const String& newName, const Vector& newPreviousScores, uint16_t newPoints);

	~WordsEntity() = default;

	String GetName() const;
	Vector GetPreviousScores() const;
	uint16_t GetPoints() const;

private:
	String name;
	Vector previousScores;
	uint16_t points;
};
