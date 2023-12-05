export module Scene;

export import <vector>;
import <typeindex>;

export import SelectableObject;
export import ConsoleManager;
export import InputManager;
export import GUIObject;
export import User;

export class Scene
{
public:
    #pragma region Scene
    Scene(ConsoleManager* console, InputManager* inputManager);
    
    virtual ~Scene();
    #pragma endregion constructors & destructor

    #pragma region Scene
    std::type_info* SetActive();
    #pragma endregion activate
protected:
    ConsoleManager* m_console;
    InputManager*   m_input;
    std::type_info* m_nextScene;

    std::vector<SelectableObject*> m_selectableObjects;
    std::vector<GUIObject*>        m_objects;

    virtual void Display () const = 0;
    virtual void Input   () const = 0;
    virtual void Start   ()       = 0;
    virtual void Update  ()       = 0;
};