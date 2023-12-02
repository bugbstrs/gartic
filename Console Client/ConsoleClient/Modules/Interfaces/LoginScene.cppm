export module LoginScene;

import <string>;

import MenuScene;
export import Scene;

using String = std::string;

export class LoginScene : public Scene
{
public:
    // Constructors
    LoginScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~LoginScene() = default;

private:
    enum class Options
    {
        USER,
        PASSWORD,
        LOGIN,
        REGISTER
    };
    Options m_option;

    String m_password;
    String m_username;
    int    m_textpos;

    bool Login()    const;
    bool Register() const;
    void Display()  const override;
    void Input()    const override;
    void Start()          override;
    void Update()         override;
};