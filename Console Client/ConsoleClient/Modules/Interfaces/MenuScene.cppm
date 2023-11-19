export module MenuScene;

export import Scene;

export class MenuScene : public Scene
{
public:
    // Constructors
    MenuScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~MenuScene() = default;

private:
    enum class Options
    {
        PLAY,
        STATS,
        LOGOUT
    };
    Options m_option;

    void Display() const override;
    void Start()   override;
    void Update()  override;
};