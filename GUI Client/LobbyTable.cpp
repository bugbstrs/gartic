#include "LobbyTable.h"
#include <random>
#include "UserCredentials.h"

LobbyTable::LobbyTable(QWidget *parent)
	: QTableWidget(parent)
{
	m_avatars[0] = { QIcon(":/image/alien"), QColor("#32CD32"), false, QIcon(":/settings/check_alien") };
	m_avatars[1] = { QIcon(":/image/astronaut"), QColor("#FFA500"), false, QIcon(":/settings/check_astronaut") };
	m_avatars[2] = { QIcon(":/image/policeman"), QColor("#1E90FF"), false, QIcon(":/settings/check_policeman") };
	m_avatars[3] = { QIcon(":/image/robot"), QColor("#FF4500"), false, QIcon(":/settings/check_robot") };
	m_avatars[4] = { QIcon(":/image/doctor"), QColor("#00BFFF"), false, QIcon(":/settings/check_doctor") };
	m_avatars[5] = { QIcon(":/image/king"), Qt::yellow, false, QIcon(":/settings/check_king") };
	m_avatars[6] = { QIcon(":/image/ninja"), QColor("#C0C0C0"), false, QIcon(":/settings/check_ninja") };
	m_avatars[7] = { QIcon(":/image/cowboy"), QColor("#A0522D"), false, QIcon(":/settings/check_cowboy") };
	m_avatars[8] = { QIcon(":/image/injured"), QColor("#8a2be2"), false, QIcon(":/settings/check_injured") };
	m_avatars[9] = { QIcon(":/image/chef"), QColor("#696969"), false, QIcon(":/settings/check_chef") };
	m_avatars[10] = { QIcon(":/image/helmet"), QColor("#3CB371"), false, QIcon(":/settings/check_helmet") };
	m_avatars[11] = { QIcon(":/image/nurse"), QColor("#cb4d7e"), false, QIcon(":/settings/check_nurse") };

	m_nameFont.setFamily("Consolas");
	m_nameFont.setPixelSize(24);

	m_yourNameFont.setFamily("Consolas");
	m_yourNameFont.setPixelSize(30);
	m_yourNameFont.setBold(true);
}

LobbyTable::~LobbyTable()
{}

void LobbyTable::AddPlayer(const std::string & name) noexcept
{
	int rowPosition = rowCount();
	insertRow(rowPosition);
	for (auto& avatar : m_avatars) {
		if (!std::get<2>(avatar)) {
			QTableWidgetItem* item = new QTableWidgetItem(std::get<0>(avatar), QString::fromUtf8(name));
			item->setBackground(std::get<1>(avatar));
			if (name == UserCredentials::GetUsername())
				item->setFont(m_yourNameFont);
			else
				item->setFont(m_nameFont);
			m_takenAvatars.push_back({ std::get<0>(avatar), QString::fromUtf8(name), std::get<1>(avatar), std::get<3>(avatar)});
			std::get<2>(avatar) = true;
			++m_currentIndex;
			setItem(rowPosition, 0, item);
			break;
		}
	}
}

int LobbyTable::GetPlayersNumber() const noexcept
{
	return rowCount();
}

void LobbyTable::ClearLobby() noexcept
{
	m_currentIndex = 0;
	for (auto& avatar : m_avatars)
		std::get<2>(avatar) = false;
	m_takenAvatars.clear();
	clearContents();
	setRowCount(0);
}

std::vector<std::tuple<QIcon, QString, QColor, QIcon>> LobbyTable::GetTakenAvatars() const noexcept
{
	return m_takenAvatars;
}
