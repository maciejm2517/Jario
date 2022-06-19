#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "animation.h"
#include "player.h"
#include "platform.h"
#include "collider.h"
#include "obstacle.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <fstream>

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){
    float aspectRatio=float(window.getSize().x)/float(window.getSize().y);
    view.setSize(VIEW_HEIGHT*aspectRatio, VIEW_HEIGHT);
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(512, 512), "Platform game");
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));
    sf::Texture playerTexture, mysteryTexture, platformTexture, platformTexture1, objectiveTexture, obstacleTexture, playerTexture1, playerTexture2, playerTexture3, textureBackground, textureBackground1;
    playerTexture.loadFromFile("kisi_from_konsolscript.png");
    playerTexture1.loadFromFile("droid_from_android.png");
    playerTexture2.loadFromFile("gnu_from_gnu.png");
    playerTexture3.loadFromFile("wilber_from_gimp.png");
    mysteryTexture.loadFromFile("images.png");
    platformTexture.loadFromFile("bluebrick.png");
    platformTexture1.loadFromFile("brick.png");
    objectiveTexture.loadFromFile("star.png");
    obstacleTexture.loadFromFile("spikes.png");
    textureBackground.loadFromFile("background.jpg");
    textureBackground1.loadFromFile("background1.jpg");
    Player player(&playerTexture, sf::Vector2u(3,9), 0.3f,200.0f,200.0f);
    sf::Sprite spriteBackground, spriteBackground1;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    spriteBackground1.setTexture(textureBackground1);
    spriteBackground1.setPosition(0,0);

    sf::Music music;
    if(!music.openFromFile("Back_Ground_Music.wav")) std::cout<<"err";
    music.play();
    music.setLoop(true);

    std::vector <Platform> platforms, platforms1;

    sf::RectangleShape wejscie1(sf::Vector2f(100.0, 60.0));
    wejscie1.setPosition(100.0, 300.0);
    wejscie1.setFillColor(sf::Color::White);

    sf::RectangleShape wejscie2(sf::Vector2f(100.0, 60.0));
    wejscie2.setPosition(350.0, 300.0);
    wejscie2.setFillColor(sf::Color::White);

    sf::RectangleShape wyjscie(sf::Vector2f(100.0, 60.0));
    wyjscie.setPosition(100.0, 300.0);
    wyjscie.setFillColor(sf::Color::White);

    sf::RectangleShape menu(sf::Vector2f(100.0, 60.0));
    menu.setPosition(350.0, 300.0);
    menu.setFillColor(sf::Color::White);

    sf::RectangleShape instrukcja(sf::Vector2f(100.0, 60.0));
    instrukcja.setPosition(350.0, 400.0);
    instrukcja.setFillColor(sf::Color::White);

    sf::RectangleShape wyjscie1(sf::Vector2f(100.0, 60.0));
    wyjscie1.setPosition(100.0, 400.0);
    wyjscie1.setFillColor(sf::Color::White);


    std::fstream in;
    std::string line;
    float column=0,row=0;
    in.open("mapa.txt",std::ios::in);

    while(std::getline(in,line)){
        column=50;
        for(auto it = line.begin(); it != line.end(); it++){
            if(*it=='x'){
                platforms.push_back(Platform(&platformTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "platform"));
            }
            if(*it=='p'){
                platforms.push_back(Platform(&mysteryTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "power_up1"));
            }
            if(*it=='2'){
                platforms.push_back(Platform(&mysteryTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "power_up2"));
            }
            if(*it=='o'){
                platforms.push_back(Platform(&objectiveTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "objective"));
            }
            if(*it=='s'){
                platforms.push_back(Platform(&obstacleTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "obstacle"));
            }
            column+=50;
        }
        row+=50;
    }

    in.close();

    in.open("mapa1.txt",std::ios::in);
    row=0;
    while(std::getline(in,line)){
        column=50;
        for(auto it = line.begin(); it != line.end(); it++){
            if(*it=='x'){
                platforms1.push_back(Platform(&platformTexture1,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "platform"));
            }
            if(*it=='p'){
                platforms1.push_back(Platform(&mysteryTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "power_up1"));
            }
            if(*it=='2'){
                platforms1.push_back(Platform(&mysteryTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "power_up2"));
            }
            if(*it=='o'){
                platforms1.push_back(Platform(&objectiveTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "objective"));
            }
            if(*it=='s'){
                platforms1.push_back(Platform(&obstacleTexture,sf::Vector2f(50.0f,50.0f), sf::Vector2f(column,row), sf::Color::White, "obstacle"));
            }
            column+=50;
        }
        row+=50;
    }

    in.close();

    float deltaTime = 0.0f;
    sf::Clock clock;
    bool win=false, problem=false, start=true, instrukcja_ = false, game1=false, game2=false;

    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");
    sf::Text text, text1, text2, text3, text4, text5;
    text.setFont(font);
    text.setCharacterSize(36);
    text.setPosition(sf::Vector2f{100,100});
    text1.setFont(font);
    text1.setCharacterSize(20);
    text2.setFont(font);
    text2.setCharacterSize(20);
    text3.setFont(font);
    text4.setFont(font);
    text5.setFont(font);
    text3.setCharacterSize(20);
    text4.setCharacterSize(20);
    text5.setCharacterSize(20);
    text1.setFillColor(sf::Color::Black);
    text2.setFillColor(sf::Color::Black);
    text3.setFillColor(sf::Color::Black);
    text4.setFillColor(sf::Color::Black);
    text5.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized){
                ResizeView(window,view);
            }
            if (start and event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    if(wejscie1.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        game1=true;
                        start=false;
                    }
                    if(wejscie2.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        game2=true;
                        start=false;
                        player.NewLevel();
                        player.ChangeTexture(&playerTexture2);
                    }
                    if(instrukcja.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        instrukcja_ = true;
                        start=false;
                    }
                    if(wyjscie1.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        window.close();
                    }
                }
            }
            if (((game1 and (win or problem)) or (game2 and (win or problem))) and event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    if(wyjscie.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        window.close();
                    }
                    if(menu.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        start=true;
                        game1=false;
                        game2=false;
                    }
                }
            }
            if (instrukcja_ and event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    if(wyjscie1.getGlobalBounds().contains(mouse_pos.x,mouse_pos.y)){
                        start=true;
                        instrukcja_=false;
                    }
                }
            }

        }
        if(start){
            win=false;
            problem=false;
            window.clear(sf::Color(100,100,100));
            text.setString("Menu");
            text1.setString("Poziom 1");
            text2.setString("Poziom 2");
            text3.setString("Wyjscie");
            text4.setString("Instrukcja");
            text1.setPosition(wejscie1.getPosition());
            text2.setPosition(wejscie2.getPosition());
            text3.setPosition(wyjscie1.getPosition());
            text4.setPosition(instrukcja.getPosition());
            view.reset(sf::FloatRect(0,0,512,512));
            window.setView(view);
            window.draw(text);
            window.draw(wejscie1);
            window.draw(wejscie2);
            window.draw(wyjscie1);
            window.draw(instrukcja);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.display();

        }
        else if(game1){

            player.Update(deltaTime);

            sf::Vector2f direction;

            for(auto& platform : platforms){
                if(platform.GetType()=="platform"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        std::cout<<"platforma"<<std::endl;
                    }
                }
                else if(platform.GetType()=="obstacle"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        std::cout<<"kolizja"<<std::endl;
                        problem=true;
                        game2=false;
                        player.ChangeTexture(&playerTexture);
                        player.NewGame();
                    }
                }
                else if(platform.GetType()=="power_up1"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        platform.SetSize(sf::Vector2f{0,0});
                        player.Resize(sf::Vector2f{100.0f,150.0f});
                        platform.ChangeColor(sf::Color::White);
                        std::cout<<"power up"<<std::endl;
                    }
                }
                else if(platform.GetType()=="power_up2"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        platform.SetSize(sf::Vector2f{0,0});
                        player.Resize(sf::Vector2f{100.0f,150.0f});
                        player.ChangeTexture(&playerTexture1);
                        platform.ChangeColor(sf::Color::White);
                        std::cout<<"power up"<<std::endl;
                    }
                }
                else if(platform.GetType()=="objective"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        game1=false;
                        game2=true;
                        player.NewLevel();
                        player.ChangeTexture(&playerTexture2);
                    }

                }

            }
            if(!win and !problem){
                view.setCenter(player.GetPosition());

                window.clear();
                window.draw(spriteBackground);
                window.setView(view);
                player.Draw(window);
                for(auto& platform :platforms){
                    platform.Draw(window);
                }
                window.display();
            }
            else{
                if(problem){
                    text.setFillColor(sf::Color::Red);
                    text.setString("Przegrales");
                    text1.setString("Menu");
                    text2.setString("Wyjscie");
                    text1.setPosition(menu.getPosition());
                    text2.setPosition(wyjscie.getPosition());
                    window.clear(sf::Color(0,0,0));
                    view.reset(sf::FloatRect(0,0,512,512));
                    window.setView(view);
                    window.draw(wyjscie);
                    window.draw(menu);
                    window.draw(text);
                    window.draw(text1);
                    window.draw(text2);
                    window.display();
                    for(auto& platform : platforms){
                                if(platform.GetType()=="power_up1" or platform.GetType()=="power_up2" or platform.GetType()=="objective"){
                                    platform.SetSize(sf::Vector2f{50,50});
                                }
                    }
                }
                if(win){
                    text.setFillColor(sf::Color::White);
                    text.setString("Wygrales");
                    text1.setString("Menu");
                    text2.setString("Wyjscie");
                    text1.setPosition(menu.getPosition());
                    text2.setPosition(wyjscie.getPosition());
                    window.clear(sf::Color(0,0,0));
                    view.reset(sf::FloatRect(0,0,512,512));
                    window.setView(view);
                    window.draw(wyjscie);
                    window.draw(menu);
                    window.draw(text);
                    window.draw(text1);
                    window.draw(text2);
                    window.display();
                    for(auto& platform : platforms){
                                if(platform.GetType()=="power_up1" or platform.GetType()=="power_up2" or platform.GetType()=="objective"){
                                    platform.SetSize(sf::Vector2f{50,50});
                                }
                    }
                }
            }


        }
        else if(game2){
            player.Update(deltaTime);

            sf::Vector2f direction;

            for(auto& platform : platforms1){
                if(platform.GetType()=="platform"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        std::cout<<"platforma"<<std::endl;
                    }
                }
                else if(platform.GetType()=="obstacle"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        std::cout<<"kolizja"<<std::endl;
                        problem=true;
                        player.ChangeTexture(&playerTexture);
                        player.NewGame();
                    }
                }
                else if(platform.GetType()=="power_up1"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        platform.SetSize(sf::Vector2f{0,0});
                        player.Resize(sf::Vector2f{60.0f,90.0f});
                        platform.ChangeColor(sf::Color::White);
                        std::cout<<"power up"<<std::endl;
                        player.ChangeTexture(&playerTexture3);
                    }
                }
                else if(platform.GetType()=="power_up2"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        player.OnCollision(direction);
                        platform.SetSize(sf::Vector2f{0,0});
                        player.Resize(sf::Vector2f{100.0f,150.0f});
                        player.ChangeTexture(&playerTexture1);
                        platform.ChangeColor(sf::Color::White);
                        std::cout<<"power up"<<std::endl;
                    }
                }
                else if(platform.GetType()=="objective"){
                    if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                        win=true;
                        player.NewGame();
                        player.ChangeTexture(&platformTexture);
                    }

                }

            }
            if(!win and !problem){
                view.setCenter(player.GetPosition());

                window.clear();
                window.draw(spriteBackground1);
                window.setView(view);
                player.Draw(window);
                for(auto& platform :platforms1){
                    platform.Draw(window);
                }
                window.display();
            }
            else{
                if(problem){
                    text.setFillColor(sf::Color::Red);
                    text.setString("Przegrales");
                    text1.setString("Menu");
                    text2.setString("Wyjscie");
                    text1.setPosition(menu.getPosition());
                    text2.setPosition(wyjscie.getPosition());
                    window.clear(sf::Color(0,0,0));
                    view.reset(sf::FloatRect(0,0,512,512));
                    window.setView(view);
                    window.draw(wyjscie);
                    window.draw(menu);
                    window.draw(text);
                    window.draw(text1);
                    window.draw(text2);
                    window.display();
                    for(auto& platform : platforms1){
                                if(platform.GetType()=="power_up1" or platform.GetType()=="power_up2" or platform.GetType()=="objective"){
                                    platform.SetSize(sf::Vector2f{50,50});
                                }
                    }
                }
                if(win){
                    text.setFillColor(sf::Color::White);
                    text.setString("Wygrales");
                    text1.setString("Menu");
                    text2.setString("Wyjscie");
                    text1.setPosition(menu.getPosition());
                    text2.setPosition(wyjscie.getPosition());
                    window.clear(sf::Color(0,0,0));
                    view.reset(sf::FloatRect(0,0,512,512));
                    window.setView(view);
                    window.draw(wyjscie);
                    window.draw(menu);
                    window.draw(text);
                    window.draw(text1);
                    window.draw(text2);
                    window.display();
                    for(auto& platform : platforms1){
                                if(platform.GetType()=="power_up1" or platform.GetType()=="power_up2" or platform.GetType()=="objective"){
                                    platform.SetSize(sf::Vector2f{50,50});
                                }
                    }
                    for(auto& platform : platforms){
                                if(platform.GetType()=="power_up1" or platform.GetType()=="power_up2" or platform.GetType()=="objective"){
                                    platform.SetSize(sf::Vector2f{50,50});
                                }
                    }
                }
            }

        }
        else if(instrukcja_){
            window.clear(sf::Color(150,150,150));
            view.reset(sf::FloatRect(0,0,512,512));
            text.setString("Instrukcja");
            text5.setPosition(sf::Vector2f{100,200});
            text1.setString("Powrot");
            text1.setFillColor(sf::Color::Black);
            text1.setPosition(wyjscie1.getPosition());
            text5.setString("Gra zawiera 2 poziomy, sterowanie \nodbywa sie za pomoca \nspacji i klawiszy A i D\nGra zawiera przeszkody w postaci\nkolcow i power upy w postaci\nzoltych blokow ze znakiem zapytania\nprzejscie do nastepnego poziomu\nmozliwe przez dotarcie do gwiazdki");
            window.setView(view);
            window.draw(text5);
            window.draw(wyjscie1);
            window.draw(text);
            window.draw(text1);
            window.display();
        }
    }

    return 0;
}
