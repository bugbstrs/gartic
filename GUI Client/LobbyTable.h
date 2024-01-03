#pragma once

#include <QTableWidget>
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
	std::vector<std::tuple<QIcon, QString, QColor>> GetTakenAvatars();

	//Functionality
	void AddPlayer(const std::string& name);
	int GetPlayersNumber() const;
	void ClearLobby();

private:
	static constexpr std::size_t kNumberOfIcons = 12;
	int currentIndex = 0;
	QFont nameFont{};
	std::array<std::pair<QIcon, QColor>, kNumberOfIcons> avatars{};
	std::vector<std::tuple<QIcon, QString, QColor>> takenAvatars;
};
