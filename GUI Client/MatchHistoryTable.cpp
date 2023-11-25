#include "MatchHistoryTable.h"

MatchHistoryTable::MatchHistoryTable(QWidget *parent)
	: QTableWidget(parent)
{
	GetMatchHistoryFromDatabase();
}

MatchHistoryTable::~MatchHistoryTable()
{}

void MatchHistoryTable::showEvent(QShowEvent * event)
{
	setColumnCount(3);
	setRowCount(2);
	for (int row = 0; row < 2; ++row) {
		for (int col = 0; col < 3; ++col) {
			QTableWidgetItem* item = new QTableWidgetItem(GetRowInfoForColumnWithIndex(col, matches[row]));
			item->setTextAlignment(Qt::AlignCenter);
			setItem(row, col, item);
		}
	}
}

QString MatchHistoryTable::GetRowInfoForColumnWithIndex(uint8_t index, const Row& row)
{
	if (index == 0)
		return row.ranking;
	else if (index == 1)
		return row.points;
	else return row.date;
}

void MatchHistoryTable::GetMatchHistoryFromDatabase()
{
	for (int row = 0; row < 2; ++row) {
		matches.push_back(Row("1st", "574", "03/03/2023"));
		matches.push_back(Row("4th", "371", "03/03/2021"));
	}
}
