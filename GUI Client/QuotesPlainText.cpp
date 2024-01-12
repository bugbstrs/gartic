#include "QuotesPlainText.h"
#include "UserCredentials.h"
#include <crow.h>

QuotesPlainText::QuotesPlainText(QWidget *parent)
	: QPlainTextEdit(parent)
{}

QuotesPlainText::~QuotesPlainText()
{}

void QuotesPlainText::showEvent(QShowEvent * event)
{
	//De apelat ruta si transformat in QString (cu fromUtf8()) ca altfel plange daca i dai std::string la setPlainText

	auto quote = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchquote" },
		cpr::Parameters{
			{"username", UserCredentials::GetUsername()},
			{"password", UserCredentials::GetPassword()}
		}
	);

	auto quoteText = crow::json::load(quote.text);

	setPlainText(QString::fromUtf8(std::string(quoteText["quote"])));
}
