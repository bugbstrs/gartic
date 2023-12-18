#pragma once

#include <QTableWidget>
#include <unordered_map>

class ScoreboardTable  : public QTableWidget
{
	Q_OBJECT

public:
	ScoreboardTable(QWidget *parent = nullptr);
	~ScoreboardTable();

	void AddPlayer(const std::string& name, int points);

private:
	std::vector<std::pair<QIcon*, QColor>>availableIcons;
	QFont nameFont;
	QFont pointsFont;
	std::unordered_map<std::string, std::pair<QTableWidgetItem*, QTableWidgetItem*>> players;
};
