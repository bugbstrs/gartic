export module Scene;

import <typeindex>;

import InputManager;
import ConsoleManager;

export class Scene
{
public:
	#pragma region Scene
	Scene(ConsoleManager* console, InputManager* inputManager);
	
	virtual ~Scene() = default;
	#pragma endregion constructors & destructor

	#pragma region Scene
	std::type_info* SetActive();
	#pragma endregion activate
protected:
	ConsoleManager* m_console;
	InputManager*   m_input;
	std::type_info* m_nextScene;

	virtual void Display() const = 0;
	virtual void Start()		 = 0;
	virtual void Update()		 = 0;
};