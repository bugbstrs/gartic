#pragma once

#include <QTableWidget>
#include <unordered_map>

class LobbyTable  : public QTableWidget
{
	Q_OBJECT

public:
	LobbyTable(QWidget *parent);
	~LobbyTable();

	void AddPlayer(const std::string& name);

private:
	QFont nameFont{};
	std::vector<std::pair<QIcon*, QColor>>availableIcons{};
	std::unordered_map<std::string, QTableWidgetItem*> players{};
};
