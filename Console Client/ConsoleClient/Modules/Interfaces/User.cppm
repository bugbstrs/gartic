export module User;

#pragma region User
import <string>;
import <vector>;
#pragma endregion imports

#pragma region User
using String = std::string;
using Int16Vector = std::vector <uint16_t>;
#pragma endregion using statements

export class User
{
public:
	#pragma region User
	User() noexcept;
	User(const String& username, uint64_t credits, bool isPlaying);
	User(const User& otherUser) noexcept;
	User(User&& otherUser) noexcept;
	~User() = default;
	#pragma endregion constructors & destructor

	#pragma region User
	void SetUsername(const String& username);
	void SetCredits(int credits);
	void SetPlayingState(bool isPlaying);
	#pragma endregion setters

	#pragma region User
	String GetUsername() const noexcept;
	uint64_t GetCredits() const noexcept;
	#pragma endregion getters

	#pragma region User
	bool IsPlaying() const;
	
	void AddMatchPoints(uint16_t matchPoint);
	#pragma endregion functionality

	#pragma region User
	User& operator=(const User& otherUser) noexcept;
	User& operator=(User&& otherUser) noexcept;
	bool operator==(const User& otherUser) const noexcept;
	#pragma endregion overloaded operators

private:
	String m_username;

	uint64_t m_credits;

	uint16_t m_averagePoints;
	
	Int16Vector m_matchesPoints;
	
	bool m_isPlaying;
};