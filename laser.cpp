// SpecialLaser.cpp
#include "laser.h"

// Constructor for SpecialLaser class
SpecialLaser::SpecialLaser(const sf::Texture& texture) : activationDuration(sf::seconds(5.0f)), active(false) 
{
    // Set the texture for the sprite
    sprite.setTexture(texture);
}

// Activate the special laser at the specified position
void SpecialLaser::activate(const sf::Vector2f& position) 
{
    // Set initial position, activate the laser, and start the activation timer
    initialPosition = position;
    sprite.setPosition(initialPosition);
    active = true;
    activationTimer.restart();
}

// Update the special laser's position and check for deactivation
void SpecialLaser::update(float deltaTime, const sf::Vector2f& characterPosition) {
    if (active) {
        // Move the laser along with the character (adjust the offset as needed)
        sprite.setPosition(characterPosition.x + 30, initialPosition.y - 700);//450 
    }
    // Deactivate the laser if the activation duration has elapsed
    if (active && activationTimer.getElapsedTime() > activationDuration) {
        active = false;
    }
}

// Draw the special laser on the window if it's active
void SpecialLaser::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

// Check if the special laser is currently active
bool SpecialLaser::isActive() const {
    return active;
}

// Get the sprite associated with the special laser
const sf::Sprite& SpecialLaser::getSprite() const
{
    // Return the sprite associated with the special laser
    return sprite;
}
