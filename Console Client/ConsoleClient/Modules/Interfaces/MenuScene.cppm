export module MenuScene;

export import Scene;

export import <string>;

using String = std::string;

export class MenuScene : public Scene
{
public:
    // Constructors
    MenuScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~MenuScene() = default;

private:
    SelectableObject* m_selected;
    String            m_password;
    String            m_username;

    void Display() const override;
    void Input  () const override;
    void Start  ()       override;
    void Update ()       override;
};