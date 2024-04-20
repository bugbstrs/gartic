#pragma once

#include <Qt6/QtWidgets/QTableWidget>
#include <unordered_map>
#include <array>

class LobbyTable  : public QTableWidget
{
	Q_OBJECT

public:
	//Constructor
	LobbyTable(QWidget *parent = nullptr);
	
	//Destructor
	~LobbyTable();

	//Getter
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> GetTakenAvatars() const noexcept;

	//Functionality
	void AddPlayer(const std::string& name) noexcept;
	int GetPlayersNumber() const noexcept;
	void ClearLobby() noexcept;

private:
	static constexpr std::size_t kNumberOfIcons = 12;
	int m_currentIndex = 0;
	QFont m_nameFont{};
	QFont m_yourNameFont{};
	std::array<std::tuple<QIcon, QColor, bool, QIcon>, kNumberOfIcons> m_avatars{};
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> m_takenAvatars;
};
