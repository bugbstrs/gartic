#pragma once

#include <QTableWidget>

class MatchHistoryTable : public QTableWidget
{
	Q_OBJECT

public:
	//Constructor
	MatchHistoryTable(QWidget *parent = nullptr);

	//Destructor
	~MatchHistoryTable();

protected:
	void showEvent(QShowEvent* event) override;

private:
	struct Row {
		Row(const std::string& ranking, const std::string& points) :
			ranking(QString::fromUtf8(ranking)),
			points(QString::fromUtf8(points))
		{}

		QString ranking;
		QString points;
	};

private:
	QString GetRowInfoForColumnWithIndex(uint16_t index, const Row& row) const noexcept;
	void GetMatchHistoryFromDatabase() noexcept;

private:
	const int m_columnsNumber = 2;
	std::vector <Row> matches{};
};
