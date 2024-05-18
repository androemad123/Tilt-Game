#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
using namespace sf;

class Game {
public:
    Game(const std::string& filename) {
        readFromFile(filename);
        readTextures();
        createEnv();
    }

    void printGameInfo() const {
        std::cout << "Grid size: " << gridSize << std::endl;
        std::cout << "Grid layout:" << std::endl;
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Coordinates: (" << x  << ")" << std::endl;
    }

    void createEnv() {
        background.setSize(Vector2f(gridSizef, gridSizef));
        background.setTexture(&textureDot);

        shapeSelector.setSize(Vector2f(gridSizef, gridSizef));
        shapeSelector.setFillColor(Color::Transparent);
        shapeSelector.setOutlineThickness(3.f / 2);
        shapeSelector.setOutlineColor(Color::Green);

        gameTile.resize(gridSize, std::vector<RectangleShape>(gridSize));

        for (int x = 0; x < gridSize; x++) {
            for (int y = 0; y < gridSize; y++) {
                gameTile[x][y].setSize(Vector2f(gridSizef, gridSizef));
              //  gameTile[x][y].setFillColor(Color::White);
                gameTile[x][y].setOutlineThickness(1.f);
                gameTile[x][y].setOutlineColor(Color::Black);
                gameTile[x][y].setPosition(x * gridSizef, y * gridSizef);
            }
        }
    }
    void Move(RenderWindow& window, Event& event) {
        if (event.type == Event::KeyPressed) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
                for (int row = 0; row < gridSize; row++) { // Iterate through each row
                    int pointToReplace = -1; // Initialize pointToReplace for each row
                    for (int col = gridSize - 1; col >= 0; col--) { // Iterate through each column from right to left
                        if (grid[row][col] == '.') {
                            gameTile[row][col].setTexture(&textureDot);

                            if (pointToReplace == -1) {
                                pointToReplace = col; // Record this column as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';
                                gameTile[row][col].setTexture(&textureDot);
                                grid[row][pointToReplace] = 'o';
                                gameTile[row][pointToReplace].setTexture(&textureO);

                                pointToReplace--; // Move to the next column to the left
                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // Left
                for (int row = 0; row < gridSize; row++) { // Iterate through each row
                    int pointToReplace = -1; // Initialize pointToReplace for each row
                    for (int col = 0; col < gridSize; col++) { // Iterate through each column from left to right
                        if (grid[row][col] == '.') {
                            gameTile[row][col].setTexture(&textureDot);

                            if (pointToReplace == -1) {
                                pointToReplace = col; // Record this column as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';
                                gameTile[row][col].setTexture(&textureDot);

                                grid[row][pointToReplace] = 'o';
                                gameTile[row][pointToReplace].setTexture(&textureO);

                                pointToReplace++; // Move to the next column to the right
                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
                for (int col = 0; col < gridSize; col++) { // Iterate through each column
                    int pointToReplace = -1; // Initialize pointToReplace for each column
                    for (int row = 0; row < gridSize; row++) { // Iterate through each row from top to bottom
                        if (grid[row][col] == '.') {
                            gameTile[row][col].setTexture(&textureDot);

                            if (pointToReplace == -1) {
                                pointToReplace = row; // Record this row as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';
                                gameTile[row][col].setTexture(&textureDot);

                                grid[pointToReplace][col] = 'o';
                                gameTile[pointToReplace][col].setTexture(&textureO);

                                pointToReplace++; // Move to the next row down
                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
                for (int col = 0; col < gridSize; col++) { // Iterate through each column
                    int pointToReplace = -1; // Initialize pointToReplace for each column
                    for (int row = gridSize - 1; row >= 0; row--) { // Iterate through each row from bottom to top
                        if (grid[row][col] == '.') {
                            if (pointToReplace == -1) {
                                pointToReplace = row; // Record this row as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';
                                gameTile[row][col].setTexture(&textureDot);

                                grid[pointToReplace][col] = 'o';
                                gameTile[pointToReplace][col].setTexture(&textureO);

                                pointToReplace--; // Move to the next row up
                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            for (int col = 0; col < gridSize; col++) {
                for (int row = 0; row < gridSize; row++) {
                    gameTile[col][row].setTexture(nullptr);
                }
            }
        }

    }
    void drawEnv(RenderWindow& window) {
        mousePovWindows = Mouse::getPosition(window);
        mousePovView = window.mapPixelToCoords(mousePovWindows);
        if (mousePovView.x >= 0.f) {
            mousePosGrid.x = static_cast<unsigned>(mousePovView.x / gridSizef);
        }
        if (mousePovView.y >= 0.f) {
            mousePosGrid.y = static_cast<unsigned>(mousePovView.y / gridSizef);
        }
        shapeSelector.setPosition(mousePosGrid.x * gridSizef, mousePosGrid.y * gridSizef);

        for (int col = 0; col < gridSize; col++) {
            for (int row = 0; row < gridSize; row++) {
                background.setPosition(col * gridSizef, row * gridSizef);
                window.draw(background);
            }
        }
        for (int col = 0; col < gridSize; col++) {
            for (int row = 0; row < gridSize; row++) {
                if (gridnew[row][col] == '#') {
                    gameTile[col][row].setTexture(&textureHash);
                }
                else if (gridnew[row][col] == '.') {
                    gameTile[col][row].setTexture(&textureDot);
                }
                else if (gridnew[row][col] == 'o') {
                    gameTile[col][row].setTexture(&textureO);
                }
                else
                {
                    gameTile[col][row].setTexture(nullptr);

                }
                window.draw(gameTile[col][row]);
            }
        }
        window.draw(shapeSelector);
    }
    void writeToFile(const std::string& filename) const {
        std::ofstream outputFile(filename, std::ofstream::trunc); // Open the file in truncation mode

        if (!outputFile) {
            std::cerr << "Unable to open file for writing: " << filename << std::endl;
            exit(1);
        }

        outputFile << gridSize << std::endl;

        for (const auto& row : grid) {
            for (const auto& cell : row) {
                outputFile << cell;
            }
            outputFile << std::endl;
        }

        outputFile << x << " " << y << std::endl;

        outputFile.close();
    }

    void readFromFileToNewGrid(const std::string& filename) {
        std::ifstream inputFile(filename);

        if (!inputFile) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            exit(1);
        }

        inputFile >> gridSize;
        gridnew.resize(gridSize, std::vector<char>(gridSize));

        char tempChar;
        std::string line;

        for (int i = 0; i < gridSize; ++i) {
            inputFile >> std::ws;
            std::getline(inputFile, line);
            std::istringstream iss(line);
            for (int j = 0; j < gridSize; ++j) {
                iss >> tempChar;
                if (tempChar == ',') {
                    --j;
                }
                else {
                    gridnew[i][j] = tempChar;
                }
            }
        }

        inputFile >> x >> y;
        inputFile.close();
    }


private:
    const float ACCELERATION = 10.0f; 
    const float MAX_VELOCITY = 200.0f;
    RectangleShape background, shapeSelector;
    int gridSize;
    Vector2f velocity;
    vector<vector<RectangleShape>> gameTile;
    Vector2f mousePovView;
    Vector2i mousePovWindows;
    Vector2u mousePosGrid;
    float gridSizef = 70;
    sf::Texture textureHash, textureDot, textureO;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> gridnew;

    string x, y;

    void readFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);

        if (!inputFile) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            exit(1);
        }

        inputFile >> gridSize;
        grid.resize(gridSize, std::vector<char>(gridSize));

        char tempChar;
        std::string line;

        for (int i = 0; i < gridSize; ++i) {
            inputFile >> std::ws;
            std::getline(inputFile, line);
            std::istringstream iss(line);
            for (int j = 0; j < gridSize; ++j) {
                iss >> tempChar;
                if (tempChar == ',') {
                    --j;
                }
                else {
                    grid[i][j] = tempChar;
                }
            }
        }

        inputFile >> x;
        inputFile.close();
    }

    void readTextures() {
        if (!textureHash.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Sprites/Fire.png")) {
            std::cerr << "Unable to load texture: Fire.png" << std::endl;
            exit(1);
        }
        if (!textureDot.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Sprites/BackG_1.png")) {
            std::cerr << "Unable to load texture: BackG_1.png" << std::endl;
            exit(1);
        }
        if (!textureO.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Sprites/circle.png")) {
            std::cerr << "Unable to load texture: circle.png" << std::endl;
            exit(1);
        }       
    }
};


