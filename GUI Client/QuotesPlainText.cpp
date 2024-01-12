#include "QuotesPlainText.h"

QuotesPlainText::QuotesPlainText(QWidget *parent)
	: QPlainTextEdit(parent)
{}

QuotesPlainText::~QuotesPlainText()
{}

void QuotesPlainText::showEvent(QShowEvent * event)
{
	//De apelat ruta si transformat in QString (cu fromUtf8()) ca altfel plange daca i dai std::string la setPlainText
	setPlainText("");
}
