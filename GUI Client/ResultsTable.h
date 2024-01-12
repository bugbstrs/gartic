#pragma once

#include <QTableWidget>

class ResultsTable  : public QTableWidget
{
	Q_OBJECT

public:

	ResultsTable(QWidget *parent);
	~ResultsTable();

	void SetPlayers(std::vector <std::tuple<QIcon, QString, int, QColor>> players);

private:
	QFont nameFont{};
	QFont pointsFont{};
	QFont yourNameFont{};
	//std::vector <std::tuple<QIcon, QString, int>> m_players;
};
