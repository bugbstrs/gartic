#include "MatchHistoryFrame.h"

MatchHistoryFrame::MatchHistoryFrame(QWidget *parent)
	: QFrame(parent)
{}

MatchHistoryFrame::~MatchHistoryFrame()
{}

void MatchHistoryFrame::showEvent(QShowEvent * event)
{
	if (firstShow) {
		m_bestScore = findChild<QLineEdit*>("bestScoreLineEdit");
		m_averageScore = findChild<QLineEdit*>("averageScoreLineEdit");
		m_matchHistoryTable = findChild<MatchHistoryTable*>("historyMatchesTable");

		m_bestScore->setText(QString::number(m_matchHistoryTable->GetBestScore()));
		m_averageScore->setText(QString::number(m_matchHistoryTable->GetAverageScore()));

		firstShow = false;
	}
}
