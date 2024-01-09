#include "LobbyTable.h"
#include <random>
#include "UserCredentials.h"

LobbyTable::LobbyTable(QWidget *parent)
	: QTableWidget(parent)
{
	avatars[0] = { QIcon(":/image/alien"), QColor("#32CD32"), false, QIcon(":/settings/check_alien") };
	avatars[1] = { QIcon(":/image/astronaut"), QColor("#FFA500"), false, QIcon(":/settings/check_astronaut") };
	avatars[2] = { QIcon(":/image/policeman"), QColor("#1E90FF"), false, QIcon(":/settings/check_policeman") };
	avatars[3] = { QIcon(":/image/robot"), QColor("#FF4500"), false, QIcon(":/settings/check_robot") };
	avatars[4] = { QIcon(":/image/doctor"), QColor("#00BFFF"), false, QIcon(":/settings/check_doctor") };
	avatars[5] = { QIcon(":/image/king"), Qt::yellow, false, QIcon(":/settings/check_king") };
	avatars[6] = { QIcon(":/image/ninja"), QColor("#C0C0C0"), false, QIcon(":/settings/check_ninja") };
	avatars[7] = { QIcon(":/image/cowboy"), QColor("#A0522D"), false, QIcon(":/settings/check_cowboy") };
	avatars[8] = { QIcon(":/image/injured"), QColor("#8a2be2"), false, QIcon(":/settings/check_injured") };
	avatars[9] = { QIcon(":/image/chef"), QColor("#696969"), false, QIcon(":/settings/check_chef") };
	avatars[10] = { QIcon(":/image/helmet"), QColor("#3CB371"), false, QIcon(":/settings/check_helmet") };
	avatars[11] = { QIcon(":/image/nurse"), QColor("#cb4d7e"), false, QIcon(":/settings/check_nurse") };

	nameFont.setFamily("Consolas");
	nameFont.setPixelSize(24);

	yourNameFont.setFamily("Consolas");
	yourNameFont.setPixelSize(30);
	yourNameFont.setBold(true);
}

LobbyTable::~LobbyTable()
{}

void LobbyTable::AddPlayer(const std::string & name)
{
	int rowPosition = rowCount();
	insertRow(rowPosition);
	for (auto& avatar : avatars) {
		if (!std::get<2>(avatar)) {
			QTableWidgetItem* item = new QTableWidgetItem(std::get<0>(avatar), QString::fromUtf8(name));
			item->setBackground(std::get<1>(avatar));
			if (name == UserCredentials::GetUsername())
				item->setFont(yourNameFont);
			else
				item->setFont(nameFont);
			takenAvatars.push_back({ std::get<0>(avatar), QString::fromUtf8(name), std::get<1>(avatar), std::get<3>(avatar)});
			std::get<2>(avatar) = true;
			++currentIndex;
			setItem(rowPosition, 0, item);
			break;
		}
	}
}

int LobbyTable::GetPlayersNumber() const
{
	return rowCount();
}

void LobbyTable::ClearLobby()
{
	currentIndex = 0;
	for (auto& avatar : avatars)
		std::get<2>(avatar) = false;
	takenAvatars.clear();
	clearContents();
	setRowCount(0);
}

std::vector<std::tuple<QIcon, QString, QColor, QIcon>> LobbyTable::GetTakenAvatars()
{
	return takenAvatars;
}
