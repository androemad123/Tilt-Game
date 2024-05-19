#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;
#define Max_main_menu 4

class MainMenu
{
public: MainMenu(float width, float hight);
	  void Draw(RenderWindow& window);
	  void moveUp();
	  void moveDown();
	  int MainMenuPressed() {
		  return MainMenuSelected;
	  }
	  ~MainMenu();
private:
	int MainMenuSelected;
	Font font_menu;
	Text MainMenuTxt[Max_main_menu];
	Texture BackGroundTex;
	Sprite BackGroudnSpr;


};

