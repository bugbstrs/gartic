#include "LobbyTable.h"
#include <random>

LobbyTable::LobbyTable(QWidget *parent)
	: QTableWidget(parent)
{
	avatars[0] = { QIcon(":/image/alien"), QColor("#32CD32") };
	avatars[1] = { QIcon(":/image/astronaut"), QColor("#FFA500") };
	avatars[2] = { QIcon(":/image/policeman"), QColor("#1E90FF") };
	avatars[3] = { QIcon(":/image/robot"), QColor("#FF4500") };
	avatars[4] = { QIcon(":/image/doctor"), QColor("#00BFFF") };
	avatars[5] = { QIcon(":/image/king"), Qt::yellow };
	avatars[6] = { QIcon(":/image/ninja"), QColor("#C0C0C0") };
	avatars[7] = { QIcon(":/image/cowboy"), QColor("#A0522D") };
	avatars[8] = { QIcon(":/image/injured"), QColor("#8a2be2") };
	avatars[9] = { QIcon(":/image/chef"), QColor("#696969") };
	avatars[10] = { QIcon(":/image/helmet"), QColor("#3CB371") };
	avatars[11] = { QIcon(":/image/nurse"), QColor("#cb4d7e") };

	/*std::random_device rd;
	std::default_random_engine rng(rd());
	std::shuffle(std::begin(avatars), std::end(avatars), rng);*/

	nameFont.setFamily("Consolas");
	nameFont.setPixelSize(24);
}

LobbyTable::~LobbyTable()
{}

void LobbyTable::AddPlayer(const std::string & name)
{
	int rowPosition = rowCount();
	insertRow(rowPosition);
	QTableWidgetItem* item = new QTableWidgetItem(avatars[currentIndex].first, QString::fromUtf8(name));
	item->setBackground(avatars[currentIndex].second);
	item->setFont(nameFont);
	takenAvatars.push_back({avatars[currentIndex].first, QString::fromUtf8(name), avatars[currentIndex].second});
	++currentIndex;
	setItem(rowPosition, 0, item);
}

int LobbyTable::GetPlayersNumber() const
{
	return rowCount();
}

void LobbyTable::ClearLobby()
{
	/*std::random_device rd;
	std::default_random_engine rng(rd());
	std::shuffle(std::begin(avatars), std::end(avatars), rng);*/
	
	currentIndex = 0;
	takenAvatars.clear();
	clearContents();
	setRowCount(0);
}

std::vector<std::tuple<QIcon, QString, QColor>> LobbyTable::GetTakenAvatars()
{
	return takenAvatars;
}
