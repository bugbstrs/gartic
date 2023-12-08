export module LoginScene;

import <string>;

import Scene;
import MenuScene;

using String = std::string;

export class LoginScene : public Scene
{
public:
    // Constructors
    LoginScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~LoginScene() = default;

private:
    SelectableObject* m_selected;
    String            m_password;
    String            m_username;

    void Login    ();
    void Register ();
    void Display  () const override;
    void Input    () const override;
    void Start    ()       override;
    void Update   ()       override;
};