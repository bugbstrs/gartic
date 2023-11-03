export module User;

import <string>;
import <vector>;

export class User
{
public:
	User();
	User(const std::string& username, uint64_t credits, bool isPlaying);
	void SetUsername(const std::string& username);
	void SetCredits(int credits);
	std::string GetUsername() const;
	uint64_t GetCredits() const;
	bool IsPlaying() const;
	void SetPlayingState(bool isPlaying);
	void AddMatchPoints(uint16_t matchPoint);

	bool operator==(const User& secondUser);
private:
	std::string m_username;
	uint16_t averagePoints;
	std::vector <uint16_t> m_matchesPoints;
	uint64_t m_credits;
	bool m_isPlaying;
};