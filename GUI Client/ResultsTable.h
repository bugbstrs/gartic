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
	QFont m_nameFont{};
	QFont m_pointsFont{};
	QFont m_yourNameFont{};
	//std::vector <std::tuple<QIcon, QString, int>> m_players;
};
