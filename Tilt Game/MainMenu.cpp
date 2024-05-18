#include "MainMenu.h"
MainMenu::MainMenu(float width, float hight) {
	if (!font_menu.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Fonts/Jacquard12-Regular.ttf")) {
		cout << " cant find a font";
	}
	for (int i = 0; i < Max_main_menu; i++)
	{
		MainMenuTxt[i].setFont(font_menu);
		MainMenuTxt[i].setFillColor(Color::White);
		MainMenuTxt[i].setCharacterSize(70);
	}
	//Play button
	MainMenuTxt[0].setString("Play");
	MainMenuTxt[0].setPosition(400, 200);
	//options button
	MainMenuTxt[1].setString("Options");
	MainMenuTxt[1].setPosition(400, 300);
	//About buttton
	MainMenuTxt[2].setString("About");
	MainMenuTxt[2].setPosition(400, 400);
	// Exit button
	MainMenuTxt[3].setString("Exit");
	MainMenuTxt[3].setPosition(400, 500);
	
	MainMenuSelected = - 1;
}
MainMenu::~MainMenu() {};
void MainMenu::Draw(RenderWindow& window) {
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
