#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>
#include "UserCredentials.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }
    , ui{ std::make_unique<Ui::MainWindow>() }
{
    ui->setupUi(this);
    qApp->setStyleSheet("QScrollBar:vertical {"
        "    border: 1px solid #999999;"
        "    background: #999999; /* Set to black */"
        "    width: 15px; /* adjust as needed */"
        "    margin: 0px 0px 0px 0px;"
        "    border-radius: 5px; /* Adjust the radius as needed */"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #0059b3;"
        "    min-height: 20px; /* adjust as needed */"
        "    border-radius: 5px; /* Adjust the radius as needed */"
        "}"
        "QScrollBar::add-line:vertical {"
        "    height: 0px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "}");
    //Main menu scene connections
    QObject::connect(ui->createLobbyButton, &QPushButton::released, this, &MainWindow::OnCreateLobbyButtonReleased);
    QObject::connect(ui->joinLobbyButton, &QPushButton::released, this, &MainWindow::OnJoinLobbyButtonReleased);
    QObject::connect(ui->quitButton, &QPushButton::released, this, &MainWindow::OnQuitButtonReleased);
    QObject::connect(ui->statsButton, &QPushButton::released, this, &MainWindow::OnStatsButtonReleased);
    QObject::connect(ui->goToLogInButton, &QPushButton::released, this, &MainWindow::OnGoToLogInButtonReleased);
    QObject::connect(ui->goToSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpButtonReleased);

    //Join Lobby scene
    QObject::connect(ui->joinLobbyFrame, &JoinLobbyFrame::OnLobbyCodeAccepted, this, &MainWindow::OnLobbyCodeAccepted);
    QObject::connect(ui->backToMenuFromJoinButton, &QPushButton::released, this, &MainWindow::OnGoToMenuFromJoinLobbyButtonReleased);

    //Lobby scene
    QObject::connect(ui->lobbyFrame, &LobbyFrame::OnGameStarted, this, &MainWindow::OnStartGameCommand);
    QObject::connect(ui->lobbyFrame, &LobbyFrame::OnLobbyLeft, this, &MainWindow::OnExitLobbyButtonReleased);

    //Game scene connections
    QObject::connect(ui->leaveGameButton, &QPushButton::released, this, &MainWindow::OnLeaveGameButtonReleased);
    QObject::connect(ui->gameplayWidget, &GameplayWidget::OnGameFinished, this, &MainWindow::OnGameEnded);
    QObject::connect(ui->goToMenuFromResultsButton, &QPushButton::released, this, &MainWindow::OnBackToMenuFromGameResults);

    //Stats scene connections
    QObject::connect(ui->backToMenuButton, &QPushButton::released, this, &MainWindow::OnBackToMenuButtonReleased);

    //Sign Up scene
    QObject::connect(ui->goToLogInFromSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpFromLogInButtonReleased);
    QObject::connect(ui->signUpViewFrame, &SignUpManager::OnSignUpCredentialsAccepted, this, &MainWindow::OnSignUpSucceded);

    //Log In scene
    QObject::connect(ui->goToSignUpFromLogInButton, &QPushButton::released, this, &MainWindow::OnGoToLogInFromSignUpButtonReleased);
    QObject::connect(ui->LogInViewFrame, &LogInManager::OnLogInCredentialsAccepted, this, &MainWindow::OnLogInCredentialsAccepted);
}

MainWindow::~MainWindow() {}


//Main menu events
void MainWindow::OnCreateLobbyButtonReleased() noexcept { 
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/createlobby" },
        cpr::Parameters{
            {"username", UserCredentials::GetUsername()},
            {"password", UserCredentials::GetPassword()}
        }
    );

    auto code = cpr::Get(
        cpr::Url{ "http://localhost:18080/fetchcode" },
        cpr::Parameters{
            {"username", UserCredentials::GetUsername()},
            {"password", UserCredentials::GetPassword()}
        }
    );
    auto codeText = crow::json::load(code.text);

    auto users = cpr::Get(
        cpr::Url{ "http://localhost:18080/fetchusers" },
        cpr::Parameters{
            {"username", UserCredentials::GetUsername()},
            {"password", UserCredentials::GetPassword()}
        }
    );
    auto usersVector = crow::json::load(users.text);

    if (response.status_code == 200 && code.status_code == 200 && users.status_code == 200) {
        ui->lobbyFrame->SetLeaderStatus(true);
        ui->stackedWidget->setCurrentWidget(ui->LobbyScene);
        ui->lobbyTable->AddPlayer(std::string(usersVector["users"][0]));
        ui->lobbyFrame->SetCode(QString::fromUtf8(std::string(codeText["code"])));
    }
}
void MainWindow::OnJoinLobbyButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->JoinLobbyScene); }
void MainWindow::OnQuitButtonReleased() noexcept { QCoreApplication::quit(); }
void MainWindow::OnStatsButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->StatsScene); }
void MainWindow::OnGoToLogInButtonReleased() noexcept{ ui->stackedWidget->setCurrentWidget(ui->LogInScene); }
void MainWindow::OnGoToSignUpButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->SignUpScene); }


//Join Lobby Scene
void MainWindow::OnLobbyCodeAccepted(std::string codeText) noexcept {
    auto joinLobby = cpr::Post(
        cpr::Url{ "http://localhost:18080/joinlobby" },
        cpr::Parameters{
            {"username", UserCredentials::GetUsername()},
            {"password", UserCredentials::GetPassword()},
            {"code", codeText}

        }
    );
    if (joinLobby.status_code == 404) {
        ui->gameAlreadyStartedLabel->show();
    }
    else {

        auto users = cpr::Get(
            cpr::Url{ "http://localhost:18080/fetchusers" },
            cpr::Parameters{
                {"username", UserCredentials::GetUsername()},
                {"password", UserCredentials::GetPassword()}
            }
        );
        auto usersVector = crow::json::load(users.text);
        for (int index = 0; index < usersVector["users"].size(); index++)
            ui->lobbyTable->AddPlayer(std::string(usersVector["users"][index]));

        ui->codeLineEdit->setText(QString::fromUtf8(codeText));
        ui->stackedWidget->setCurrentWidget(ui->LobbyScene);
    }
}
void MainWindow::OnGoToMenuFromJoinLobbyButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->MainMenuScene); }


//Lobby Scene
void MainWindow::OnStartGameCommand() noexcept {
    ui->scoreboardTable->AddPlayersToScoreboard(std::move(ui->lobbyTable->GetTakenAvatars()));
    ui->gameplayWidget->SetGameSettings(ui->lobbyFrame->GetGameSettings());
    ui->stackedWidget->setCurrentWidget(ui->GameplayScene);
}
void MainWindow::OnExitLobbyButtonReleased() noexcept { 
    ui->stackedWidget->setCurrentWidget(ui->MainMenuScene);
    ui->lobbyTable->ClearLobby();
    auto users = cpr::Get(
        cpr::Url{ "http://localhost:18080/leavelobby" },
        cpr::Parameters{
            {"username", UserCredentials::GetUsername()},
            {"password", UserCredentials::GetPassword()}
        }
    );
}


//Game Scene events
void MainWindow::OnLeaveGameButtonReleased() noexcept { 
    auto response{ cpr::Get(
        cpr::Url{ "http://localhost:18080/leavegame" },
        cpr::Parameters{
            {"password", UserCredentials::GetPassword()},
            {"username", UserCredentials::GetUsername()}
        }
    ) };
    if (response.status_code == 200) {
        ui->scoreboardTable->StopCheckingForPlayers(true);
        ui->chatFrame->StopCheckingForUpdates(true);
        ui->stackedWidget->setCurrentWidget(ui->MainMenuScene);
        ui->gameplayWidget->Clear();
        ui->lobbyTable->ClearLobby();
        ui->scoreboardTable->clear();
    }
}

void MainWindow::OnGameEnded() noexcept
{
    ui->stackedWidget->setCurrentWidget(ui->ResultsScene);
    ui->resultsTable->SetPlayers(ui->scoreboardTable->GetPlayersOrdered());
    /*std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> players = ui->scoreboardTable->GetPlayersOrdered();
    for (auto& player : players) {
        QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(player), std::get<1>(player));
        QTableWidgetItem* score = new QTableWidgetItem(QIcon(), QString::number(0));

        name->setBackground(std::get<2>(player));
        if (std::get<1>(player) == QString::fromUtf8(UserCredentials::GetUsername()))
            name->setFont(yourNameFont);
        else
            name->setFont(nameFont);
        name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        score->setBackground(std::get<2>(avatar));
        score->setFont(pointsFont);
        score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

        int rowPosition = rowCount();
        insertRow(rowPosition);
        setItem(rowPosition, 0, name);
        setItem(rowPosition, 1, score);

        players.push_back({ name, score });
    }*/
}

void MainWindow::OnBackToMenuFromGameResults() noexcept
{
    ui->stackedWidget->setCurrentWidget(ui->MainMenuScene);
}


// Stats scene events
void MainWindow::OnBackToMenuButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->MainMenuScene); }


//Sign Up scene
void MainWindow::OnGoToLogInFromSignUpButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->SignUpScene); }
void MainWindow::OnSignUpSucceded() noexcept { ui->stackedWidget->setCurrentWidget(ui->LogInScene); }
void MainWindow::OnLogInCredentialsAccepted() noexcept { ui->stackedWidget->setCurrentWidget(ui->MainMenuScene); }


//Log in scene
void MainWindow::OnGoToSignUpFromLogInButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->LogInScene); }

