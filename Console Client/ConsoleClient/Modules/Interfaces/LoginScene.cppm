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
	String m_username;
	String m_password;

	enum class Options
	{
		USER,
		PASSWORD,
		LOGIN,
		REGISTER
	};
	Options m_option;
	int m_textpos;

	void Start() override;
	void Update() override;
	void Display() const override;
	bool Login() const;
	bool Register() const;
};