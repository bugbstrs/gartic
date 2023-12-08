export module LobbyScene;

import Scene;
import MenuScene;

export class LobbyScene : public Scene
{
public:
    // Constructors
    LobbyScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~LobbyScene() = default;

private:
    SelectableObject* m_selected;

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