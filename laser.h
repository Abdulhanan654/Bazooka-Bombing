// SpecialLaser.h
#pragma once

#include <SFML/Graphics.hpp>

// Class representing a special laser in the game
class SpecialLaser {
public:
    // Constructor: Initializes the special laser with a given texture
    SpecialLaser(const sf::Texture& texture);

    // Activate the special laser at the specified position
    void activate(const sf::Vector2f& position);
    void update(float deltaTime, const sf::Vector2f& characterPosition);

    // Draw the special laser on the window if it's active
    void draw(sf::RenderWindow& window);


    // Check if the special laser is currently active
    bool isActive() const;
    const sf::Sprite& getSprite() const;  // Added function to access the sprite

private:
    sf::Sprite sprite;
    sf::Clock activationTimer;  // Timer to track the activation duration
    sf::Time activationDuration;
    bool active; // Flag indicating whether the laser is currently active
    sf::Vector2f initialPosition;
};
