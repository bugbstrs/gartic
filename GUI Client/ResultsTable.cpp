#include "ResultsTable.h"
#include <algorithm>
#include "UserCredentials.h"

ResultsTable::ResultsTable(QWidget *parent)
	: QTableWidget(parent)
{
	m_nameFont.setFamily("Consolas");
	m_nameFont.setPixelSize(32);

	m_pointsFont.setFamily("Consolas");
	m_pointsFont.setPixelSize(42);

	m_yourNameFont.setFamily("Consolas");
	m_yourNameFont.setPixelSize(36);
	m_yourNameFont.setBold(true);
}

ResultsTable::~ResultsTable()
{}

void ResultsTable::SetPlayers(std::vector <std::tuple<QIcon, QString, int, QColor>> players) noexcept
{
	std::sort(players.begin(), players.end(), [](const std::tuple<QIcon, QString, int, QColor>& a, const std::tuple<QIcon, QString, int, QColor>& b) {
		return std::get<2>(a) > std::get<2>(b);
	});
	for (std::tuple<QIcon, QString, int, QColor>& player : players) {
		QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(player), std::get<1>(player));
		QTableWidgetItem* score = new QTableWidgetItem(QString::number(std::get<2>(player)));

		name->setBackground(std::get<3>(player));
		if (std::get<1>(player) == QString::fromUtf8(UserCredentials::GetUsername()))
			name->setFont(m_yourNameFont);
		else
			name->setFont(m_nameFont);
		name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

		score->setBackground(std::get<3>(player));
		score->setFont(m_pointsFont);
		score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

		int rowPosition = rowCount();
		insertRow(rowPosition);
		setItem(rowPosition, 0, name);
		setItem(rowPosition, 1, score);
	}
}
