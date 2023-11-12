export module Scene;

import <typeindex>;

import ConsoleManager;

export class Scene
{
public:
	// Constructors
	Scene(ConsoleManager* console);

	// Destructors
    virtual ~Scene();

	// Activate
    std::type_info* SetActive();

protected:
	std::type_info* m_nextScene;
	ConsoleManager* m_console;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Display() const = 0;
};