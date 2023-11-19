export module Scene;

import <typeindex>;

import InputManager;
import ConsoleManager;

export class Scene
{
public:
	// Constructors
	Scene(ConsoleManager* console, InputManager* inputManager);

	// Destructor
    virtual ~Scene() = default;

	// Activate
    std::type_info* SetActive();

protected:
	std::type_info* m_nextScene;
	ConsoleManager* m_console;
	InputManager* m_input;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Display() const = 0;
};