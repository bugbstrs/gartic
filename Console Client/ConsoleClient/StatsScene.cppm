export module StatsScene;

export import Scene;

export import <string>;

using String = std::string;

export class StatsScene : public Scene
{
public:
    // Constructors
    StatsScene(ConsoleManager* console, InputManager* inputManager);

    // Destructor
    ~StatsScene() = default;

private:
    SelectableObject* m_selected;
    
    void GetStatistics ();
    void Back          ();
    void Input         () const override;
    void Start         ()       override;
    void Update        ()       override;
};