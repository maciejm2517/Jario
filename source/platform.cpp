#include "platform.h"
#include "collider.h"

Platform::Platform(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Color color, std::string type)
{
    body.setSize(size);
    body.setOrigin(size/2.0f);
    body.setTexture(texture);
    body.setPosition(position);
    this->type=type;
}

Platform::~Platform()
{

}

void Platform::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}

void Platform::ChangeColor(sf::Color color)
{
    body.setFillColor(color);
}

void Platform::SetSize(sf::Vector2f size)
{
    body.setSize(size);
}
