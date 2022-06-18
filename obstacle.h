#pragma once
#include <SFML/Graphics.hpp>
#include "collider.h"
class obstacle
{
public:
    obstacle(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~obstacle();
    void Draw(sf::RenderWindow& window);
    Collider GetCollider(){return Collider(body);}
private:
    sf::RectangleShape body;
};
