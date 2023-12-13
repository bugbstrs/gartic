export module LobbyScene;

import Scene;
import SpinBox;
import CheckBox;
import MenuScene;
import VerticalLayout;

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
    CheckBox*         m_customRounds;

    void StartGame  ();
    void GetUsers   ();
    void GetSettings();
    void SetSettings();
    void HasStarted ();
    void Back       ();
    void Input      () const override;
    void Start      ()       override;
    void Update     ()       override;
};