#pragma once

#include <Qt6/QtWidgets/QTableWidget>

class ResultsTable  : public QTableWidget
{
	Q_OBJECT

public:

	ResultsTable(QWidget *parent);
	~ResultsTable();

	void SetPlayers(std::vector <std::tuple<QIcon, QString, int, QColor>> players) noexcept;

private:
	QFont m_nameFont{};
	QFont m_pointsFont{};
	QFont m_yourNameFont{};
};
