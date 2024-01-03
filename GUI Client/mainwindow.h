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
    void OnJoinLobbyButtonReleased() noexcept;
    void OnQuitButtonReleased() noexcept;
    void OnStatsButtonReleased() noexcept;
    void OnGoToLogInButtonReleased() noexcept;
    void OnGoToSignUpButtonReleased() noexcept;

    //Join Lobby scene
    void OnLobbyCodeAccepted(std::string codeText) noexcept;
    void OnGoToMenuFromJoinLobbyButtonReleased() noexcept;

    //Lobby scene
    void OnStartGameButtonReleased() noexcept;
    void OnExitLobbyButtonReleased() noexcept;

    //Drawing scene
    void OnLeaveGameButtonReleased() noexcept;

    //Stats scene
    void OnBackToMenuButtonReleased() noexcept;

    //Sign Up scene
    void OnGoToLogInFromSignUpButtonReleased() noexcept;
    void OnSignUpSucceded() noexcept;

    //Log In scene
    void OnLogInCredentialsAccepted() noexcept;
    void OnGoToSignUpFromLogInButtonReleased() noexcept;

private:
    std::unique_ptr<Ui::MainWindow> ui;
    bool isUserLoggedIn{ false };
    std::string username;
    std::string password;
};
#endif // MAINWINDOW_H