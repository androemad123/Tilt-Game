#include "MainMenu.h"
MainMenu::MainMenu(float width, float hight) {
	if (!font_menu.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Fonts/Jacquard12-Regular.ttf")) {
		cout << " cant find a font";
	}
	if (!BackGroundTex.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Sprites/backGroundMain.jpg")) {
		cout << " cant find backGround pic";
	}
	BackGroudnSpr.setTexture(BackGroundTex);
	BackGroudnSpr.setScale(sf::Vector2f(0.22f, 0.25f));
	for (int i = 0; i < Max_main_menu; i++)
	{
		MainMenuTxt[i].setFont(font_menu);
		MainMenuTxt[i].setFillColor(Color::White);
		MainMenuTxt[i].setCharacterSize(90);
	}
	//Play button
	MainMenuTxt[0].setString("Play");
	MainMenuTxt[0].setPosition(300, 200);
	//options button
	MainMenuTxt[1].setString("Options");
	MainMenuTxt[1].setPosition(300, 300);
	//About buttton
	MainMenuTxt[2].setString("About");
	MainMenuTxt[2].setPosition(300, 400);
	// Exit button
	MainMenuTxt[3].setString("Exit");
	MainMenuTxt[3].setPosition(300, 500);
	
	MainMenuSelected = - 1;
}
MainMenu::~MainMenu() {};
void MainMenu::Draw(RenderWindow& window) {
	window.draw(BackGroudnSpr);
	for (int i = 0; i < Max_main_menu; ++i) {
		if (MainMenuTxt[i].getString().isEmpty()) {
			std::cerr << "Uninitialized text item at index " << i << std::endl;
			continue;
		}
		window.draw(MainMenuTxt[i]);
	}
}
void MainMenu::moveUp() {
	if (MainMenuSelected - 1 >= 0)
	{
		MainMenuTxt[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 2;
		}

		MainMenuTxt[MainMenuSelected].setFillColor(Color::Red);

	}
}
void MainMenu::moveDown() {
	if (MainMenuSelected + 1 <= Max_main_menu)
	{
		MainMenuTxt[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 4)
		{
			MainMenuSelected = 0;
		}

		MainMenuTxt[MainMenuSelected].setFillColor(Color::Red);

	}
}
