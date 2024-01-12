#include "ResultsTable.h"
#include <algorithm>
#include "UserCredentials.h"

ResultsTable::ResultsTable(QWidget *parent)
	: QTableWidget(parent)
{
	nameFont.setFamily("Consolas");
	nameFont.setPixelSize(20);

	pointsFont.setFamily("Consolas");
	pointsFont.setPixelSize(20);

	yourNameFont.setFamily("Consolas");
	yourNameFont.setPixelSize(16);
	yourNameFont.setBold(true);
}

ResultsTable::~ResultsTable()
{}

void ResultsTable::SetPlayers(std::vector <std::tuple<QIcon, QString, int, QColor>> players)
{
	for (std::tuple<QIcon, QString, int, QColor>& player : players) {
		QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(player), std::get<1>(player));
		QTableWidgetItem* score = new QTableWidgetItem(QString::number(std::get<2>(player)));

		name->setBackground(std::get<3>(player));
		if (std::get<1>(player) == QString::fromUtf8(UserCredentials::GetUsername()))
			name->setFont(yourNameFont);
		else
			name->setFont(nameFont);
		name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

		score->setBackground(std::get<3>(player));
		score->setFont(pointsFont);
		score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

		int rowPosition = rowCount();
		insertRow(rowPosition);
		setItem(rowPosition, 0, name);
		setItem(rowPosition, 1, score);
	}
}
