module LoginScene;

import <string>;

std::string LoginScene::m_username = "";
std::string LoginScene::m_password = "";
LoginScene::Options LoginScene::m_option;
SceneType LoginScene::m_nextScene;

SceneType LoginScene::SetActive()
{
	Start();
	Update();
	return m_nextScene;
}

void LoginScene::Start()
{
	m_username = "";
	m_password = "";
	m_nextScene = NOT_A_SCENE;
	ConsoleManager::SetConsoleScale(60, 15);
	Display();
}

void LoginScene::Update()
{
	while (m_nextScene == NOT_A_SCENE)
	{
		Display();
	}
}

void LoginScene::Display()
{
	//Title
	ConsoleManager::ClearScreen();
	ConsoleManager::SetColor(Cyan, Magenta);
	ConsoleManager::WriteHorizontal("GARTIC", 30, 2);
	//Username Field
	ConsoleManager::SetColor(Black, White);
	ConsoleManager::WriteHorizontal("User:", 20, 5);
	ConsoleManager::SetColor(Gray, Black);
	std::cout << "                  ";
	//Password Field
	ConsoleManager::SetColor(Black, White);
	ConsoleManager::WriteHorizontal("Password:", 18, 6);
	ConsoleManager::SetColor(Gray, Black);
	std::cout << "                  ";
	//Login Button
	ConsoleManager::SetColor(DarkGray, Green);
	ConsoleManager::WriteHorizontal("Login", 25, 10);
	//Register Button
	ConsoleManager::SetColor(DarkGray, Cyan);
	ConsoleManager::WriteHorizontal("Register", 36, 10);
}

bool LoginScene::Login()
{
	//Init User
	return true;
}

bool LoginScene::Register()
{
	//Init User
	return false;
}