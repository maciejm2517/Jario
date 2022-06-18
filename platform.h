#pragma once
#include <SFML/Graphics.hpp>
#include "collider.h"

class Platform
{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color color, std::string type);
    ~Platform();

    void Draw(sf::RenderWindow& window);
    void ChangeColor(sf::Color color);
    void SetSize(sf::Vector2f size);
    Collider GetCollider(){return Collider(body);}
    std::string GetType(){return type;}
    sf::Vector2f GetPosition(){return body.getPosition();}

private:
    sf::RectangleShape body;
    std::string type;
};
