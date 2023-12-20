#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    //Main menu buttons
    void OnCreateLobbyButtonReleased() noexcept;
    void OnQuitButtonReleased() noexcept;
    void OnStatsButtonReleased() noexcept;
    void OnGoToLogInButtonReleased() noexcept;
    void OnGoToSignUpButtonReleased() noexcept;

    //Lobby scene
    void OnStartGameButtonReleased() noexcept;
    void OnExitLobbyButtonReleased() noexcept;

    //Drawing scene
    void OnLeaveGameButtonReleased() noexcept;

    //Stats scene
    void OnBackToMenuButtonReleased() noexcept;

    //Sign Up scene
    void OnGoToLogInFromSignUpButtonReleased() noexcept;

    //Log In scene
    void OnGoToSignUpFromLogInButtonReleased() noexcept;

private:
    std::unique_ptr<Ui::MainWindow> ui;
    bool isUserLoggedIn{ false };
};
#endif // MAINWINDOW_H