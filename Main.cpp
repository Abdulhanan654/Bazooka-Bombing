#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "HighScores.h"
#include "laser.h"
// for login page
enum class GameState {
    Login,
    Game
};

// Function to generate random positions
sf::Vector2f getRandomPosition(const sf::Vector2u& screenSize) {
    float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (screenSize.x - 300);
    float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (screenSize.y - 400);
    return sf::Vector2f(x, y);
}

// Function to increase the player's score
void increaseScore(int& score, int points) {
    score += points;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(900, 700), "BZAOOKA BOMBING", sf::Style::Resize | sf::Style::Close );

    // Load the character texture
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("Textures/character8.png")) {
        return EXIT_FAILURE;
    }

    // Load the enemy texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("Textures/enemy6.png")) {
        return EXIT_FAILURE;
    }

    // Load the dummy enemy texture
    sf::Texture dummyEnemyTexture;
    if (!dummyEnemyTexture.loadFromFile("Textures/bot2.png")) {
        return EXIT_FAILURE;
    }

    // Load the bullet texture
    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("Textures/bullet2.png")) {
        return EXIT_FAILURE;
    }

    // Load the login background texture
    sf::Texture loginBackgroundTexture;
    if (!loginBackgroundTexture.loadFromFile("Textures/background3.jpg")) {
        return EXIT_FAILURE;
    }

    // Load the game background texture
    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("Textures/Artboard 1.jpg")) {
        return EXIT_FAILURE;
    }

    // load the laser texture
    sf::Texture laserTexture;
    if (!laserTexture.loadFromFile("Textures/laser2.png")) {
        return EXIT_FAILURE;
    }

    // Load the background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("MI.mp3")) {
        // Replace "path_to_your_audio_file.ogg" with the actual path to your audio file
        std::cerr << "Failed to load audio file." << std::endl;
        return EXIT_FAILURE;
    }

    // Set the music to loop and play it
    backgroundMusic.setLoop(true);
    backgroundMusic.play();


    // Create a sprite for the login background
    sf::Sprite loginBackgroundSprite;
    loginBackgroundSprite.setTexture(loginBackgroundTexture);

    // Create a sprite for the game background
    sf::Sprite gameBackgroundSprite;
    gameBackgroundSprite.setTexture(gameBackgroundTexture);


    // Create a SpecialLaser object
    SpecialLaser specialLaser(laserTexture);

    // Load the font for displaying text
    sf::Font font;
    if (!font.loadFromFile("Fonts/Dosis-Bold.ttf")) {
        return EXIT_FAILURE;
    }

    // Create a sprite for the background
    sf::Sprite background;

    // Create a character
    sf::Sprite character(characterTexture);
    character.setPosition(80, 600); //80 420 for full screen

    // Create a list of enemies with fixed positions and random spawn times
    std::vector<sf::Sprite> enemies;
    std::vector<sf::Clock> enemyTimers;

    // Create a list of dummy enemies
    std::vector<sf::Sprite> dummyEnemies;
    sf::Clock dummyEnemySpawnTimer;

    // Create a list of bullets
    std::vector<sf::Sprite> bullets;

    // Define a time limit between enemy movements
    sf::Clock clock;
    sf::Time timeSinceLastMovement = sf::Time::Zero;
    sf::Time enemySpawnTime = sf::seconds(3.0f); // Enemy spawns every 4 seconds

    // Character movement speed
    float characterSpeed = 50.0f;

    // Create a text object for displaying the score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10, 10);

    // Create a text object for displaying the health
    sf::Text healthText;
    healthText.setFont(font);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Blue);
    healthText.setPosition(10, 40);

    // Create a text object for displaying the Game over
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString(" Game Over!");
    gameOverText.setPosition(250, 300);

   
    // Game score
    int score = 0;

    // Character health
    int health = 15;

    // Create a sprite for the laser
    sf::Sprite laser(laserTexture);
    laser.setPosition(0, 0); // Set initial position (you can adjust this)

           // code for login page    

    //for login page 

    GameState gameState = GameState::Login;

    sf::Text usernameLabel;
    sf::RectangleShape usernameInputBox;
    sf::Text startButton;
    sf::Text enteredUsername;
    bool isUsernameActive = false;

    usernameLabel.setString("Username:");
    usernameLabel.setFont(font);
    usernameLabel.setCharacterSize(20);
    usernameLabel.setPosition(140, 310);

    usernameInputBox.setSize(sf::Vector2f(200, 30));
    usernameInputBox.setPosition(160, 350);
    usernameInputBox.setOutlineColor(sf::Color::Black);
    usernameInputBox.setOutlineThickness(2);

    startButton.setString("Start");
    startButton.setFont(font);
    startButton.setCharacterSize(20);
    startButton.setPosition(370, 400);

    enteredUsername.setFont(font);
    enteredUsername.setCharacterSize(20);
    enteredUsername.setPosition(160, 350);
    enteredUsername.setFillColor(sf::Color::Black);

    // Game loop

    sf::Clock laserActivationTimer;
    const sf::Time laserActivationDuration = sf::seconds(3.0f);
    bool isLaserActivated = false;

    while (window.isOpen())
    {
        sf::Event event;


        while (window.pollEvent(event))
        {


            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle events for the login state

            if (gameState == GameState::Login)
            {


                if (event.type == sf::Event::MouseButtonReleased)
                {
                    // Handle mouse button release events
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Check if the Start button is clicked
                    if (startButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        std::cout << "Starting with username: " << enteredUsername.getString().toAnsiString() << std::endl;

                        if (!enteredUsername.getString().isEmpty()) {
                            gameState = GameState::Game;
                            // Perform any necessary setup for the game
                        }
                    }

                           // Check if the username input box is clicked
                    if (usernameInputBox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        isUsernameActive = true;
                    }
                    else {
                        isUsernameActive = false;
                    }
                }

                // Handle text input events for the username

                if (event.type == sf::Event::TextEntered && isUsernameActive) {
                    if (event.text.unicode == 8 && !enteredUsername.getString().isEmpty()) 
                    {
                        // Backspace is pressed, remove the last character
                        enteredUsername.setString(enteredUsername.getString().substring(0, enteredUsername.getString().getSize() - 1));
                    }

                    else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                    { 
                        // Add the entered character to the username
                        enteredUsername.setString(enteredUsername.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }
            else if (gameState == GameState::Game)
            {             // Handle events for the game state

                // Check for key press to spawn bullets
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    sf::Sprite bullet(bulletTexture);
                    bullet.setPosition(character.getPosition());
                    bullets.push_back(bullet);
                }

                        // Check for movement keys
                if (event.type == sf::Event::KeyPressed) 
                {
                    if (event.key.code == sf::Keyboard::Left && character.getPosition().x > 0) {
                        character.move(-characterSpeed, 0);
                    }

                    if (event.key.code == sf::Keyboard::Right && character.getPosition().x + character.getGlobalBounds().width < window.getSize().x) {
                        character.move(characterSpeed, 0);
                    }
                }
                          // Check for laser activation
                if (score % 5 == 0 && !specialLaser.isActive() && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                {
                    std::cout << "Laser activated!" << std::endl;
                    specialLaser.activate(character.getPosition());
                }

                    // Check for the escape key to close the window in both states
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }


        }

        // high score is defined here
        HighScores highScores;
        highScores.setHighscores(); // Read high scores from the file

        if (gameState == GameState::Game)
        {
            // Handle game-related logic

            timeSinceLastMovement += clock.restart();


            // Spawn enemies at regular intervals

            if (timeSinceLastMovement > enemySpawnTime) {
                sf::Vector2f randomPosition = getRandomPosition(window.getSize());
                sf::Sprite enemy(enemyTexture);
                enemy.setPosition(randomPosition);
                enemies.push_back(enemy);
                enemyTimers.push_back(sf::Clock());
                timeSinceLastMovement = sf::Time::Zero;
            }




            // Check if laser is activated and update it
            if (specialLaser.isActive()) {
                specialLaser.update(clock.restart().asSeconds(), character.getPosition());

                // Check for collisions between laser and enemies
                std::vector<size_t> enemiesToRemove;

                for (size_t i = 0; i < enemies.size(); ++i)
                {
                    if (specialLaser.getSprite().getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                    {
                        // Collision detected, increase the player's score
                        increaseScore(score, 1);

                        // Add the enemy index to the removal list
                        enemiesToRemove.push_back(i);
                    }
                }

                // Remove the enemies after the loop
                for (const auto& index : enemiesToRemove) {
                    enemyTimers.erase(enemyTimers.begin() + index);
                    enemies.erase(enemies.begin() + index);
                }
            }

            // Move the dummy enemy
            for (auto& dummyEnemy : dummyEnemies)
            {
                dummyEnemy.move(0, -1);  //adjust the speed of dummy enemy,-0.2 for full screen 
            }

            // Move the bullets
            for (auto& bullet : bullets)
            {
                bullet.move(0, -3); // Adjust the speed of the bullets -1 for full screen 
            }

            // Check for collisions between bullets and enemies

            for (auto bullet = bullets.begin(); bullet != bullets.end();)
            {
                bool bulletRemoved = false;

                for (size_t i = 0; i < enemies.size(); ++i)
                {
                    if (bullet->getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                    {
                        // Collision detected, remove the enemy
                        enemies.erase(enemies.begin() + i);
                        enemyTimers.erase(enemyTimers.begin() + i);

                        // Increase the player's score

                        increaseScore(score, 1);
                        bulletRemoved = true;
                        break;
                    }
                }

                // Remove the bullet if it hit an enemy or went off-screen
                if (bulletRemoved || bullet->getPosition().y < 0) {
                    bullet = bullets.erase(bullet);
                }
                // If no collision occurred, move to the next bullet
                else
                {
                    ++bullet;
                }
            }

            //check if bullet hit dummy target
            for (auto bullet = bullets.begin(); bullet != bullets.end();) {
                bool bulletRemoved = false;

                for (size_t i = 0; i < dummyEnemies.size(); ++i) {
                    if (bullet->getGlobalBounds().intersects(dummyEnemies[i].getGlobalBounds())) {
                        dummyEnemies.erase(dummyEnemies.begin() + i);

                        // Decrease player's score and health if dummy is hit
                        score -= 2;
                        health -= 2;
                        bulletRemoved = true;
                        break;
                    }
                }


                // Remove the bullet if it hit an enemy or went off-screen
                if (bulletRemoved || bullet->getPosition().y < 0)
                {
                    bullet = bullets.erase(bullet);
                }
                else
                {
                    // If no collision occurred, move to the next bullet
                    ++bullet;
                }
            }


            // Check if enemies should disappear after 3 seconds

            for (size_t i = 0; i < enemies.size(); ++i) {
                if (enemyTimers[i].getElapsedTime().asSeconds() > 3.0f) //3 for full screen
                {
                    enemies.erase(enemies.begin() + i);
                    enemyTimers.erase(enemyTimers.begin() + i);
                    health -= 1;
                }
            }

            //check for dummy enemies comes after every 5 second

            if (dummyEnemySpawnTimer.getElapsedTime().asSeconds() > 5.0f)//5 for full screen
            {
                sf::Vector2f randomPosition = getRandomPosition(window.getSize());
                sf::Sprite dummyEnemy(dummyEnemyTexture);
                dummyEnemy.setPosition(randomPosition);
                dummyEnemies.push_back(dummyEnemy);
                dummyEnemySpawnTimer.restart();
            }


            // Update and display the score and health
            scoreText.setString("Score: " + std::to_string(score));
            healthText.setString("Health: " + std::to_string(health));


            // Draw everything
            window.clear();
            window.draw(gameBackgroundSprite);
            window.draw(gameBackgroundSprite);

            for (const auto& enemy : enemies) {
                window.draw(enemy);
            }

            for (const auto& dummyEnemy : dummyEnemies) {
                window.draw(dummyEnemy);
            }

            for (const auto& bullet : bullets) {
                window.draw(bullet);
            }

            window.draw(character);
            specialLaser.draw(window);

            // Draw the objects
            window.draw(scoreText);
            window.draw(healthText);

           

            window.display();

            // Check if the player's health is zero and end the game if needed
            if (health <= 0) {
                std::cout << "Game Over! Your final score: " << score << std::endl;
                highScores.UpdateHighScore(score);

                // Draw "Game Over" text
                window.draw(gameOverText);

                window.display();

                // Wait for a moment before closing the window (optional)
                sf::sleep(sf::seconds(5.0f));

                window.close();
            }
        }
        else {

            // draw for login page 
            window.clear();
            window.draw(loginBackgroundSprite);
            window.draw(usernameLabel);
            window.draw(usernameInputBox);
            window.draw(startButton);
            window.draw(enteredUsername);



            window.display();
        }

    }



    return 0;
}