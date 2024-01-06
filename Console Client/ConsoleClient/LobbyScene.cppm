export module LobbyScene;

import Scene;
import Label;
import Button;
import SpinBox;
import CheckBox;
import MenuScene;
import GameScene;
import VerticalLayout;

using Color = ColorType;

export class LobbyScene : public Scene
{
public:
    // Constructors
    LobbyScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~LobbyScene() = default;

private:
    SelectableObject* m_selected;
    VerticalLayout*   m_users;
    SpinBox*          m_rounds;
    SpinBox*          m_drawTime;
    SpinBox*          m_wordCount;
    Label*            m_codeLabel;
    Button*           m_startButton;
    CheckBox*         m_customRounds;
    bool              m_isLeader;

    void StartGame  ();
    void GetUsers   ();
    void GetSettings();
    void SetSettings();
    void SetAsLeader();
    void HasStarted ();
    void Back       ();
    void Input      () const override;
    void Start      ()       override;
    void Update     ()       override;
};