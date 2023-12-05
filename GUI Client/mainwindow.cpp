#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUserLoggedIn = false;
    //Main menu scene connections
    QObject::connect(ui->playButton, &QPushButton::released, this, &MainWindow::OnPlayButtonReleased);
    QObject::connect(ui->quitButton, &QPushButton::released, this, &MainWindow::OnQuitButtonReleased);
    QObject::connect(ui->statsButton, &QPushButton::released, this, &MainWindow::OnStatsButtonReleased);
    QObject::connect(ui->goToLogInButton, &QPushButton::released, this, &MainWindow::OnGoToLogInButtonReleased);
    QObject::connect(ui->goToSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpButtonReleased);

    //Game scene connections
    QObject::connect(ui->leaveGameButton, &QPushButton::released, this, &MainWindow::OnLeaveGameButtonReleased);

    //Stats scene connections
    QObject::connect(ui->backToMenuButton, &QPushButton::released, this, &MainWindow::OnBackToMenuButtonReleased);

    //Sign Up scene
    QObject::connect(ui->goToLogInFromSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToLogInFromSignUpButtonReleased);

    //Log In scene
    QObject::connect(ui->goToSignUpFromLogInButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpFromLogInButtonReleased);
}

MainWindow::~MainWindow() {
    delete ui;
}


//Main menu events
void MainWindow::OnPlayButtonReleased() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::OnQuitButtonReleased() { QCoreApplication::quit(); }
void MainWindow::OnStatsButtonReleased() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::OnGoToLogInButtonReleased() { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::OnGoToSignUpButtonReleased() { ui->stackedWidget->setCurrentIndex(3); }

//Game scene events
void MainWindow::OnLeaveGameButtonReleased() { ui->stackedWidget->setCurrentIndex(0); }

// Stats scene events
void MainWindow::OnBackToMenuButtonReleased() { ui->stackedWidget->setCurrentIndex(0); }


//Sign Up scene
void MainWindow::OnGoToLogInFromSignUpButtonReleased() { ui->stackedWidget->setCurrentIndex(4); }

//Log in scene
void MainWindow::OnGoToSignUpFromLogInButtonReleased() { ui->stackedWidget->setCurrentIndex(3); }

