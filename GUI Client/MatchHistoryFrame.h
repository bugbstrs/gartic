#pragma once

#include <QFrame>
#include <qlineedit.h>
#include "MatchHistoryTable.h"

class MatchHistoryFrame  : public QFrame
{
	Q_OBJECT

public:
	MatchHistoryFrame(QWidget *parent);
	~MatchHistoryFrame();

	void showEvent(QShowEvent* event) override;
private:
	bool m_firstShow{ true };
	QLineEdit* m_averageScore;
	QLineEdit* m_bestScore;
	MatchHistoryTable* m_matchHistoryTable;
};
