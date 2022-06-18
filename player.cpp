#include "player.h"

Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
    : animation(texture, imageCount, switchTime)
{
    this ->speed = speed;
    this->jumpHeight=jumpHeight;
    this->jumpHeight_=jumpHeight;
    row = 0;
    faceRight = true;
    resize=true;

    body.setSize(sf::Vector2f(100.0f,150.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(306.0f,756.0f);
    body.setTexture(texture);
    if(!buffer.loadFromFile("mario_jump.wav")) std::cout<<"err";
    sound.setBuffer(buffer);

}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    velocity.x*=0.0f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        velocity.x-=speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        velocity.x+=speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump){
        canJump=false;
        velocity.y=-std::sqrt(2.0f*981.0f*jumpHeight);
        sound.play();
    }



    if(velocity.x==0.0f){
        row=0;
    }
    else{
        if(velocity.y!=0.0f){
            row=2;
        }
        else{
            row = 1;
        }
        if(velocity.x>0.0f){
            faceRight=true;
        }
        else{
            faceRight=false;
        }
    }
    velocity.y+=981.0f*deltaTime;
    animation.Update(row,deltaTime,faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity*deltaTime);
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
    if(direction.x<0.0f){
        //collision on the left
        velocity.x=0.0f;
    }
    else if(direction.x>0.0f){
        //collision on the right
        velocity.x=0.0f;
    }
    if(direction.y<0.0f){
        //collision on the bottom
        velocity.y=0.0f;
        canJump=true;
    }
    else if(direction.y>0.0f){
        //collision on the top
        velocity.y=0.0f;
    }
}

void Player::Resize(sf::Vector2f size)
{

        body.setSize(size);
        body.setOrigin(body.getSize()/2.0f);
        if(resize){
            this->jumpHeight=jumpHeight+100.0f;
            resize=false;
        }

}

void Player::NewGame()
{
    this->jumpHeight=jumpHeight_;
    this->resize=true;
    this->velocity.y=0.0f;
    body.setSize(sf::Vector2f(100.0f,150.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(306.0f,756.0f);
}

void Player::NewLevel()
{
    this->jumpHeight=jumpHeight_;
    this->resize=true;
    this->velocity.y=0.0f;
    body.setSize(sf::Vector2f(100.0f,150.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(306.0f,200.0f);
}

void Player::ChangeTexture(sf::Texture *texture)
{
    this->body.setTexture(texture);
}

