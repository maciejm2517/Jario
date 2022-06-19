#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "animation.h"
#include "collider.h"
#include "math.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight_);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);
    void OnCollision(sf::Vector2f direction);
    void Resize(sf::Vector2f size);
    void NewGame();
    void NewLevel();
    void ChangeTexture(sf::Texture* texture);

    sf::Vector2f GetPosition() {return body.getPosition();}
    Collider GetCollider(){return Collider(body);}
private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool resize;

    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
    float jumpHeight_;
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

