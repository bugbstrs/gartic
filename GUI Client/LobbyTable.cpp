#include "LobbyTable.h"
#include <random>

LobbyTable::LobbyTable(QWidget *parent)
	: QTableWidget(parent)
{
	availableIcons.reserve(12);
	availableIcons.emplace_back(new QIcon(":/image/alien"), QColor("#32CD32"));
	availableIcons.emplace_back(new QIcon(":/image/astronaut"), QColor("#FFA500"));
	availableIcons.emplace_back(new QIcon(":/image/king"), Qt::yellow);
	availableIcons.emplace_back(new QIcon(":/image/ninja"), QColor("#C0C0C0"));
	availableIcons.emplace_back(new QIcon(":/image/policeman"), QColor("#1E90FF"));
	availableIcons.emplace_back(new QIcon(":/image/robot"), QColor("#FF4500"));
	availableIcons.emplace_back(new QIcon(":/image/cowboy"), QColor("#A0522D"));
	availableIcons.emplace_back(new QIcon(":/image/injured"), QColor("#8a2be2"));
	availableIcons.emplace_back(new QIcon(":/image/doctor"), QColor("#00BFFF"));
	availableIcons.emplace_back(new QIcon(":/image/chef"), QColor("#696969"));
	availableIcons.emplace_back(new QIcon(":/image/helmet"), QColor("#3CB371"));
	availableIcons.emplace_back(new QIcon(":/image/nurse"), QColor("#cb4d7e"));
	nameFont.setFamily("Consolas");
	nameFont.setPixelSize(24);
}

LobbyTable::~LobbyTable()
{}

void LobbyTable::AddPlayer(const std::string & name)
{
	auto getRandomIndex = [this]() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, availableIcons.size() - 1);
		return distribution(gen);
	};

	int randomIconIndex = getRandomIndex();

	players.insert({ name, {new QTableWidgetItem(*availableIcons[randomIconIndex].first, QString::fromUtf8(name))} });
	players[name]->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	int rowPosition = rowCount();
	insertRow(rowPosition);
	players[name]->setBackground(availableIcons[randomIconIndex].second);
	players[name]->setFont(nameFont);
	setItem(rowPosition, 0, players[name]);
	delete availableIcons[randomIconIndex].first;
	availableIcons.erase(availableIcons.begin() + randomIconIndex);
}