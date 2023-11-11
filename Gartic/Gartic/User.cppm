export module User;

import <string>;
import <vector>;

using String = std::string;
using Int16Vector = std::vector <uint16_t>;

export class User
{
public:
	// Constructors
	User();
	User(const String& username, uint64_t credits, bool isPlaying);
	User(const User& otherUser);
	~User() = default;
	
	// Setters
	void SetUsername(const String& username);
	void SetCredits(int credits);
	
	// Getters
	String GetUsername() const noexcept;
	uint64_t GetCredits() const noexcept;
	
	// Functionality
	bool IsPlaying() const;
	
	void SetPlayingState(bool isPlaying);
	void AddMatchPoints(uint16_t matchPoint);

	// Overloaded Operators
	User& operator=(const User& secondUser);
	bool operator==(const User& secondUser) const noexcept;
private:
	String m_username;

	uint16_t m_averagePoints;
	
	Int16Vector m_matchesPoints;
	
	uint64_t m_credits;
	
	bool m_isPlaying;
};