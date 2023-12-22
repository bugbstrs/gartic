#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    QObject::connect(ui->quitButton, &QPushButton::released, this, &MainWindow::OnQuitButtonReleased);
    QObject::connect(ui->statsButton, &QPushButton::released, this, &MainWindow::OnStatsButtonReleased);
    QObject::connect(ui->goToLogInButton, &QPushButton::released, this, &MainWindow::OnGoToLogInButtonReleased);
    QObject::connect(ui->goToSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpButtonReleased);

    //Lobby scene
    QObject::connect(ui->startGameButton, &QPushButton::released, this, &MainWindow::OnStartGameButtonReleased);
    QObject::connect(ui->exitLobbyButton, &QPushButton::released, this, &MainWindow::OnExitLobbyButtonReleased);

    //Game scene connections
    QObject::connect(ui->leaveGameButton, &QPushButton::released, this, &MainWindow::OnLeaveGameButtonReleased);

    //Stats scene connections
    QObject::connect(ui->backToMenuButton, &QPushButton::released, this, &MainWindow::OnBackToMenuButtonReleased);

    //Sign Up scene
    QObject::connect(ui->goToLogInFromSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToLogInFromSignUpButtonReleased);

    //Log In scene
    QObject::connect(ui->goToSignUpFromLogInButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpFromLogInButtonReleased);
}

MainWindow::~MainWindow() {}


//Main menu events
void MainWindow::OnCreateLobbyButtonReleased() noexcept { 
    ui->lobbyTable->AddPlayer("Gigel");
    ui->lobbyTable->AddPlayer("Frone");
    ui->lobbyTable->AddPlayer("Alex");
    ui->lobbyTable->AddPlayer("Andrei");
    ui->lobbyTable->AddPlayer("Bambi");
    ui->lobbyTable->AddPlayer("Turcu");
    ui->stackedWidget->setCurrentWidget(ui->LobbyScene); 
}
void MainWindow::OnQuitButtonReleased() noexcept { QCoreApplication::quit(); }
void MainWindow::OnStatsButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->StatsScene); }
void MainWindow::OnGoToLogInButtonReleased() noexcept{ ui->stackedWidget->setCurrentWidget(ui->LogInScene); }
void MainWindow::OnGoToSignUpButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->SignUpScene); }

void MainWindow::OnStartGameButtonReleased() noexcept { 
    ui->scoreboardTable->AddPlayersToScoreboard(std::move(ui->lobbyTable->GetTakenAvatars()));
    ui->stackedWidget->setCurrentWidget(ui->GameplayScene);
}

void MainWindow::OnExitLobbyButtonReleased() noexcept { ui->stackedWidget->setCurrentWidget(ui->MainMenuScene); }

//Game scene events
void MainWindow::OnLeaveGameButtonReleased() noexcept { 
    ui->stackedWidget->setCurrentWidget(ui->MainMenuScene); 
    ui->scoreboardTable->ClearScoreboard();
    ui->lobbyTable->ClearLobby();
}

// Stats scene events
void MainWindow::OnBackToMenuButtonReleased() noexcept { ui->stackedWidget->setCurrentIndex(0); }

//Sign Up scene
void MainWindow::OnGoToLogInFromSignUpButtonReleased() noexcept { ui->stackedWidget->setCurrentIndex(4); }

//Log in scene
void MainWindow::OnGoToSignUpFromLogInButtonReleased() noexcept { ui->stackedWidget->setCurrentIndex(3); }

