#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "MainMenu.h"
#include "Game.cpp"
using namespace std;
using namespace sf;

int Dimensions;
std::vector<std::vector<char>> board;
std::pair<int, int> target;

// Function to read the board from a file

int main()
{
    VideoMode DeskTop_D = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(DeskTop_D.width / 1.5, DeskTop_D.height / 1.5), "SFML works!");
    const int numFiles = 6;
    string filename = "C:/Users/user/source/repos/reading_TiltGame/Sample Tests/case2.txt";
    string fileoutPut = "C:/Users/user/Desktop/Tilt_Game/TestCases/inputToOutPut.txt";
    Game game(filename);
    MainMenu mainmenu(window.getSize().x, window.getSize().y);
    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type ==Event::KeyReleased)
            {
                if (event.key.code == Keyboard::W) {
                    mainmenu.moveUp();
                    break;
                }
                if (event.key.code == Keyboard::S) {
                    mainmenu.moveDown();
                    break;
                }
                if (event.key.code==Keyboard::Return)
                {
                    RenderWindow Play(VideoMode(DeskTop_D.width / 1.5, DeskTop_D.height / 1.5), "Tilt Game");
                    RenderWindow Options(VideoMode(DeskTop_D.width / 1.5, DeskTop_D.height / 1.5), "SFML works!");
                    RenderWindow About(VideoMode(DeskTop_D.width / 1.5, DeskTop_D.height / 1.5), "SFML works!");
                    int x = mainmenu.MainMenuPressed();
                    if (x==0)
                    {
                        Options.close();
                        About.close();
                        while (Play.isOpen())
                        {

                            Event Pevent;
                            while (Play.pollEvent(Pevent))
                            {
                                if (Pevent.type == Event::Closed)
                                {
                                    Play.close();
                                }
                                game.Move(Play, Pevent);
                                game.printGameInfo();
                                game.writeToFile(fileoutPut);
                                game.readFromFileToNewGrid(fileoutPut);

                            }
                            Play.clear();
                            game.drawEnv(Play);
                            Play.display();
                        }
                       
                    }
                    if (x==1)
                    {
                        Play.close();
                        About.close();
                        while (Options.isOpen())
                        {

                            Event Oevent;
                            while (Options.pollEvent(Oevent))
                            {
                                if (Oevent.type == Event::Closed)
                                {
                                    Options.close();
                                }

                            }
                            Options.clear();
                            Options.display();
                        }
                    }
                    if (x == 2)
                    {
                        while (About.isOpen())
                        {

                            Event event;
                            while (About.pollEvent(event))
                            {
                                if (event.type == Event::Closed)
                                {
                                    About.close();
                                }

                            }
                            Play.close();
                            About.clear();
                            Options.clear();
                            About.display();
                        }
                    }
                    if (x==3)
                    {
                        window.close();
                    }
                    
                }
            }

        }
        window.clear();
        mainmenu.Draw(window);
       
        window.display();
    }

    return 0;
}
