#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }
    , ui{ std::make_unique<Ui::MainWindow>() }
{
    ui->setupUi(this);
    isUserLoggedIn = false;
    eraserEnabled = false;
    eraserCursor = QCursor(QPixmap(":/image/eraser_cursor").scaled(25, 25));
    fillCursor = QCursor(QPixmap(":/image/fill").scaled(25, 25));
    pencilCursor = Qt::CrossCursor;

    //Main menu scene connections
    QObject::connect(ui->playButton, &QPushButton::released, this, &MainWindow::OnPlayButtonReleased);
    QObject::connect(ui->quitButton, &QPushButton::released, this, &MainWindow::OnQuitButtonReleased);
    QObject::connect(ui->statsButton, &QPushButton::released, this, &MainWindow::OnStatsButtonReleased);
    QObject::connect(ui->goToLogInButton, &QPushButton::released, this, &MainWindow::OnGoToLogInButtonReleased);
    QObject::connect(ui->goToSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpButtonReleased);

    //Game scene connections
    QObject::connect(ui->leaveGameButton, &QPushButton::released, this, &MainWindow::OnLeaveGameButtonReleased);
    QObject::connect(ui->eraserButton, &QPushButton::released, this, &MainWindow::OnEraserButtonReleased);
    QObject::connect(ui->pencilButton, &QPushButton::released, this, &MainWindow::OnPencilEnabled);
    QObject::connect(ui->toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &MainWindow::OnColorChanged);
    QObject::connect(ui->fillButton, &QPushButton::released, this, &MainWindow::OnFillEnabled);

    //Stats scene connections
    QObject::connect(ui->backToMenuButton, &QPushButton::released, this, &MainWindow::OnBackToMenuButtonReleased);

    //Sign Up scene
    QObject::connect(ui->goToLogInFromSignUpButton, &QPushButton::released, this, &MainWindow::OnGoToLogInFromSignUpButtonReleased);

    //Log In scene
    QObject::connect(ui->goToSignUpFromLogInButton, &QPushButton::released, this, &MainWindow::OnGoToSignUpFromLogInButtonReleased);
}

MainWindow::~MainWindow() {
}


//Main menu events
void MainWindow::OnPlayButtonReleased() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::OnQuitButtonReleased() { QCoreApplication::quit(); }
void MainWindow::OnStatsButtonReleased() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::OnGoToLogInButtonReleased() { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::OnGoToSignUpButtonReleased() { ui->stackedWidget->setCurrentIndex(3); }

//Game scene events
void MainWindow::OnLeaveGameButtonReleased() { 
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    ui->stackedWidget->setCurrentIndex(0); 
}
void MainWindow::OnEraserButtonReleased() { 
    QApplication::setOverrideCursor(eraserCursor); 
    eraserEnabled = true;
}
void MainWindow::OnFillEnabled() { 
    QApplication::setOverrideCursor(fillCursor); 
    eraserEnabled = false;
}
void MainWindow::OnColorChanged()
{
    if (eraserEnabled)
        QApplication::setOverrideCursor(pencilCursor);

}
void MainWindow::OnPencilEnabled() { 
    QApplication::setOverrideCursor(pencilCursor);
    eraserEnabled = false;
}

// Stats scene events
void MainWindow::OnBackToMenuButtonReleased() { ui->stackedWidget->setCurrentIndex(0); }

//Sign Up scene
void MainWindow::OnGoToLogInFromSignUpButtonReleased() { ui->stackedWidget->setCurrentIndex(4); }

//Log in scene
void MainWindow::OnGoToSignUpFromLogInButtonReleased() { ui->stackedWidget->setCurrentIndex(3); }

