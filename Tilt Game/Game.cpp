#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        setupAudio();
        setupRestartButton();
        setupText();

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
        std::cout << "Coordinates: (" << x<<", " << y << ")" << std::endl;
    }
    void createEnv() {
        background.setSize(Vector2f(gridSizef, gridSizef));
        background.setTexture(&textureDot);

        gameTile.resize(gridSize, std::vector<RectangleShape>(gridSize));
        for (int x = 0; x < gridSize; x++) {
            for (int y = 0; y < gridSize; y++) {
                gameTile[x][y].setSize(Vector2f(gridSizef, gridSizef));
              //  gameTile[x][y].setFillColor(Color::White);
                gameTile[x][y].setOutlineThickness(1.f);
                gameTile[x][y].setOutlineColor(Color::Black);
                gameTile[x][y].setPosition(x * gridSizef+150, y * gridSizef+150);
            }
        }
    }
    void handleMouseClick(RenderWindow& window, Event& event) {
        Vector2i mousePos = Mouse::getPosition(window);
        if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            restartButton.setScale(2,3.33);
            //restartButton.rotate(90.f);
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    restartGame();
                }
            }
        }
        else
        {
            restartButton.setScale(1.7, 2.833);

        }
    }
    void setupText() {
        winText.setFont(font);
        winText.setCharacterSize(90);
        winText.setFillColor(Color::White);
        winText.setPosition(800, 300);
        movecountTxt.setFont(font);
        movecountTxt.setCharacterSize(50);
        movecountTxt.setFillColor(Color::White);
        movecountTxt.setPosition(700, 70); // Position the text below the restart button
        moveTxt.setFont(font);
        moveTxt.setCharacterSize(40);
        moveTxt.setFillColor(Color::White);
        moveTxt.setPosition(700, 120); // Position the text below the restart button

        updateMoveText(); // Initialize the move text
    }
    void updateMoveText() {
        movecountTxt.setString("Moves Count : " + std::to_string(movecount));
        moveTxt.setString(move);
    }
    void restartGame() {
        // Reset the grid and other game state variables
        move = "";
        movecount = 0;
        readFromFile("C:/Users/user/source/repos/reading_TiltGame/Sample Tests/case2.txt");
        createEnv();
    }
    void Move(RenderWindow& window, Event& event) {
        if (event.type == Event::KeyPressed) {
            bool moved = false;
            startCameraShake(0.2f, window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
                move = move + "Right \n";
                for (int row = 0; row < gridSize; row++) { // Iterate through each row
                    int pointToReplace = -1; // Initialize pointToReplace for each row
                    for (int col = gridSize - 1; col >= 0; col--) { // Iterate through each column from right to left
                        if (grid[row][col] == '.') {

                            if (pointToReplace == -1) {
                                pointToReplace = col; // Record this column as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';
                                grid[row][pointToReplace] = 'o';

                                pointToReplace--; // Move to the next column to the left
                                moved = true;

                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // Left
                move = move + "Left \n";
                startCameraShake(0.2f, window);

                for (int row = 0; row < gridSize; row++) { // Iterate through each row
                    int pointToReplace = -1; // Initialize pointToReplace for each row
                    for (int col = 0; col < gridSize; col++) { // Iterate through each column from left to right
                        if (grid[row][col] == '.') {

                            if (pointToReplace == -1) {
                                pointToReplace = col; // Record this column as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';

                                grid[row][pointToReplace] = 'o';

                                pointToReplace++; // Move to the next column to the right
                                moved = true;

                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
                move = move + "Up \n";
                startCameraShake(0.2f, window);

                for (int col = 0; col < gridSize; col++) { // Iterate through each column
                    int pointToReplace = -1; // Initialize pointToReplace for each column
                    for (int row = 0; row < gridSize; row++) { // Iterate through each row from top to bottom
                        if (grid[row][col] == '.') {

                            if (pointToReplace == -1) {
                                pointToReplace = row; // Record this row as the point to replace
                            }
                        }
                        else if (grid[row][col] == 'o') {
                            if (pointToReplace != -1) {
                                grid[row][col] = '.';

                                grid[pointToReplace][col] = 'o';

                                pointToReplace++; // Move to the next row down
                                moved = true;

                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
                move = move + "Down \n";
                startCameraShake(0.2f, window);

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

                                grid[pointToReplace][col] = 'o';

                                pointToReplace--; // Move to the next row up
                                moved = true;

                            }
                        }
                        else {
                            pointToReplace = -1;
                        }
                    }
                }
            }

            if (moved) {
                movecount++;
                updateMoveText();
                moveSound.play();
            }
        }

    }
    void drawEnv(RenderWindow& window) {
      
        for (int col = 0; col < gridSize; col++) {
            for (int row = 0; row < gridSize; row++) {
                if (row==y && col ==x)
                {
                    gameTile[col][row].setFillColor(Color::Yellow);
                    continue;
                }
                else if (grid[row][col] == '#') {
                    gameTile[col][row].setFillColor(Color::Blue);
                }
                else if (grid[row][col] == '.') {
                    gameTile[col][row].setFillColor(Color::Red);
                }
                else if (grid[row][col] == 'o') {
                    gameTile[col][row].setFillColor(Color::Green);
                }
                if (grid[col][row]=='o'&&row==x&&col==y)
                {
                    winner = "YOU WIN!";
                    winText.setString(winner);
                    window.draw(winText);
                }
               
                window.draw(gameTile[col][row]);
            }
        }
        window.draw(restartButton);
        window.draw(movecountTxt);
        window.draw(moveTxt);
        updateCameraShake(window);

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

        outputFile << x << " " << std::endl;

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

        inputFile >> x;
        inputFile.close();
    }
    void startCameraShake(float duration, RenderWindow& window) {
        isShaking = true;
        shakeDuration = duration;
        shakeClock.restart();
        originalView = window.getView();
    }

    void updateCameraShake(RenderWindow& window) {
        if (isShaking) {
            if (shakeClock.getElapsedTime().asSeconds() < shakeDuration) {
                float offsetX = ((rand() % 100) / 50.f - 1) * shakeMagnitude;
                float offsetY = ((rand() % 100) / 50.f - 1) * shakeMagnitude;
                View shakeView = originalView;
                shakeView.move(offsetX, offsetY);
                window.setView(shakeView);
            }
            else {
                isShaking = false;
                window.setView(originalView); // Reset the view to its original state
            }
        }
    }


private:
    
    RectangleShape background, restartButton;
    vector<vector<RectangleShape>> gameTile;
  
    float gridSizef = 70, shakeDuration = 0.f, shakeMagnitude = 5.f;
    sf::Texture textureHash, textureDot, textureO, restartButtonTexture;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<char>> gridnew;
    sf::Music backgroundMusic; // Background music object
    sf::SoundBuffer moveBuffer; // Buffer for move sound effect
    sf::Sound moveSound; // Sound object for move sound effect
    string cord,move,winner;
    int x,y, movecount = 0, gridSize;
    sf::Font font; // Font for the text
    sf::Text movecountTxt,winText, moveTxt; // Text for displaying moves
    bool isShaking = false;
    Clock shakeClock;
    View originalView;

    void setCoordinatesFromString(const std::string& coordString) {
        std::string coords = coordString;
        coords.erase(std::remove(coords.begin(), coords.end(), ' '), coords.end());
        std::stringstream ss(coords);
        std::string temp;

        std::getline(ss, temp, ',');
        x = std::stoi(temp);

        std::getline(ss, temp, ',');
        y = std::stoi(temp);
    }
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

        inputFile >> cord;
        setCoordinatesFromString(cord);
        inputFile.close();
    }
    void setupAudio() {
        if (!backgroundMusic.openFromFile("C:/Users/user/Desktop/Tilt_Game/Music/MainThem.mp3")) {
            std::cerr << "Unable to load audio file" << std::endl;
            exit(1);
        }
        backgroundMusic.setLoop(true);  // Set the music to loop
        backgroundMusic.play();         // Start playing the music
        backgroundMusic.setVolume(50.f);

        if (!moveBuffer.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Music/Collision.mp3")) {
            std::cerr << "Unable to load move sound!" << std::endl;
            exit(1);
        }
        moveSound.setBuffer(moveBuffer);
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
        if (!restartButtonTexture.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Sprites/restart.png")) {
            std::cerr << "Unable to load restart button texture!" << std::endl;
            exit(1);
        }
        if (!font.loadFromFile("C:/Users/user/Desktop/Tilt_Game/Fonts/Jacquard12-Regular.ttf")) {
            std::cerr << "Unable to load font!" << std::endl;
            exit(1);
        }
    }
    void setupRestartButton() {

        restartButton.setSize(Vector2f(100, 50)); // Set the size of the restart button
        restartButton.setTexture(&restartButtonTexture);
        restartButton.setPosition(1000, 100); // Position the button at the top-left corner
    }
};


