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

    //Join Lobby scene
    void OnLobbyCodeAccepted(std::string codeText) noexcept;
    void OnGoToMenuFromJoinLobbyButtonReleased() noexcept;

    //Lobby scene
    void OnStartGameCommand() noexcept;
    void OnExitLobbyButtonReleased() noexcept;

    //Drawing scene
    void OnLeaveGameButtonReleased() noexcept;
    void OnGameEnded() noexcept;

    //Game results scene
    void OnBackToMenuFromGameResults() noexcept;

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
};
#endif // MAINWINDOW_H