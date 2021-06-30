#include "klasy.h"
#include <random>
#include <iostream>
Background::Background(std::string background, float x, float y){
    texture_.loadFromFile(background);
    texture_.setRepeated(true);
    this->setTexture(texture_);
    this->setTextureRect(sf::IntRect(0,0,x,y));
}


Strzal::Strzal():AnimatedSprite("fireshot.png"){
    this->setScale(0.03,0.05);
}

void Strzal::Animacja(const sf::Time elapsed){
    float time=elapsed.asSeconds();
    float distance_y=speed_y_*time;
    this->move(0,-distance_y);
}

Hero::Hero(sf::RenderWindow &window, std::string file):AnimatedSprite(file)
{
    if(file=="cyan.png"){
        this->setScale(0.04, 0.04);
    }
    else if(file=="pikachu.png"){
        setScale(0.05, 0.05);
    }
    else{
        this->setScale(0.1, 0.1);
    }
    this->setBounds(0, window.getSize().x, 0, window.getSize().y);
    this->setPosition((window.getSize().x/2.0)-((this->getGlobalBounds().width)/2.0),(window.getSize().y-this->getGlobalBounds().height));
    for(int i=0; i<3; i++){
        auto heart=std::make_unique<Heart>();
        zycie.emplace_back(std::move(heart));
        if(i==0){
            zycie[i]->setPosition(0,0);
        }
        if(i>0){
            zycie[i]->setPosition(zycie[i-1]->getPosition().x+zycie[i]->getGlobalBounds().width,0);
        }
    }
}
void Hero::usun_zycie(){
    zycie.erase(zycie.end());
    hearts_-=1;

}

void Hero::dodaj_zycie()
{
    auto heart=std::make_unique<Heart>();
    heart->setPosition(zycie[zycie.size()-1]->getPosition().x+heart->getGlobalBounds().width,0);
    zycie.emplace_back(std::move(heart));
    hearts_++;

}

void Hero::jump()
{
    move(0,10);
    move(0,-10);
}
void Hero::draw_hero(sf::RenderWindow &window){
    window.draw(*this);
    for(const auto &s : zycie) {
        window.draw(*s);
    }

}

void Hero::Animacja(const sf::Time elapsed){
    float time=elapsed.asSeconds();
    float distance_x=speed_x*time;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& this->getGlobalBounds().left+ this->getGlobalBounds().width <=right_border_)
    {
        this->move(distance_x,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& this->getGlobalBounds().left>left_border_)
    {
        this->move(-distance_x, 0);
    }
}

void Hero::setBounds(float left, float right, float top, float bottom)
{
    left_border_=left;
    right_border_=right;
    top_border_=top;
    bottom_border_=bottom;
}

int Hero::get_hearts(){return hearts_;}

int Hero::get_points(){return points;}

void Hero::add_points(){points+=10;}

void Hero::set_hearts(int hearts){
    hearts_=hearts;
}

Menu::Menu(sf::RenderWindow &window){
    float width=window.getSize().x;
    float height=window.getSize().y;
    font.loadFromFile("Comic Sans MS 400.ttf");
    text[0].setFont(font);
    text[0].setColor(sf::Color::Cyan);
    text[0].setString("GRAJ");
    text[0].setPosition((width/2), (height/5)*1);

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString("USTAWIENIA");
    text[1].setPosition(width/2, (height/5)*2);

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("WYJSCIE");
    text[2].setPosition(width/2, (height/5)*3);

    text[3].setFont(font);
    text[3].setColor(sf::Color::White);
    text[3].setString("JAK GRAC");
    text[3].setPosition(width/2, (height/5)*4);
    selecteditemid=0;
}

void Menu::draw(sf::RenderWindow &window){
    for(int i=0; i<4; i++)
    {
        window.draw(text[i]);
    }
}

void Menu::MoveUp(){
    if(selecteditemid-1>=0)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid--;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

void Menu::MoveDown(){
    if(selecteditemid+1<4)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid++;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

int Menu::GetPressedId(){
    return selecteditemid;
}


Settings::Settings(sf::RenderWindow &window){
    float width=window.getSize().x;
    float height=window.getSize().y;
    font.loadFromFile("Comic Sans MS 400.ttf");
    text[0].setFont(font);
    text[0].setColor(sf::Color::Cyan);
    text[0].setString("POSTAC");
    text[0].setPosition((width/1.9), (height/4*1));

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString("TLO");
    text[1].setPosition(width/1.9, (height/4)*2);

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("POZIOM TRUDNOSCI");
    text[2].setPosition(width/1.9, (height/4)*3);
    selecteditemid=0;
}

void Settings::draw(sf::RenderWindow &window){
    for(int i=0; i<3; i++)
    {
        window.draw(text[i]);
    }
}

void Settings::MoveUp(){
    if(selecteditemid-1>=0)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid--;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

void Settings::MoveDown(){
    if(selecteditemid+1<3)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid++;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

int Settings::GetPressedId(){
    return selecteditemid;
}

std::string Game::get_poziom_trudnosci()
{
    return poziom_trudnosci;
}

std::string Game::get_character_name(){return character_name_;}

std::string Game::get_background_name(){return background_name_;}

void Game::set_poziom_trudnoci(std::string arg)
{
    poziom_trudnosci=arg;
}

void Game::set_background_name(std::string arg)
{
    background_name_=arg;
}

void Game::set_character_name(std::string arg)
{
    character_name_=arg;
}

float Game::get_ice_frequency()
{
    if(poziom_trudnosci=="easy"){
        return 10;
    }
    else if(poziom_trudnosci=="medium"){
        return 15;
    }
    else{
        return 20;
    }
}

float Game::get_chicken_frequency()
{
    if(poziom_trudnosci=="easy"){
        return 2.5;
    }
    else if(poziom_trudnosci=="medium"){
        return 2;
    }
    else{
        return 1.5;
    }
}

float Game::get_heart_frequency()
{
    if(poziom_trudnosci=="easy"){
        return 7;
    }
    else if(poziom_trudnosci=="medium"){
        return 10;
    }
    else{
        return 13;
    }
}

float Game::get_black_heart_frequency()
{
    if(poziom_trudnosci=="easy"){
        return 10;
    }
    else if(poziom_trudnosci=="medium"){
        return 7;
    }
    else{
        return 3;
    }
}
Chicken::Chicken():AnimatedSprite("chicken.png"){
    this->setScale(0.1,0.1);

}
void Chicken::speed(Game &game){
    if(game.get_poziom_trudnosci()=="easy"){
        this->set_speed(30);
    }
    else if(game.get_poziom_trudnosci()=="medium")
    {
        this->set_speed(60);
    }
    else if(game.get_poziom_trudnosci()=="hard")
    {
        this->set_speed(90);
    }

}
void Chicken::animation_chicken(const sf::Time elapsed){
    float time=elapsed.asSeconds();
    float distance_y=time*speed_y_;
    this->move(0,distance_y);
}

void Chicken::set_speed(int arg)
{
    speed_y_=arg;
}

void Chicken::freeze()
{
    this->speed_y_=0;
}

Bonus::Bonus(std::string file):AnimatedSprite(file){}

Heart::Heart():Bonus("heart.png"){
    this->setScale(0.05,0.05);
}

void Heart::move(const sf::Time &elapsed)
{
    float time=elapsed.asSeconds();
    float distance_y=time*speed_y_;
    this->sf::Sprite::move(0,distance_y);
}

Black_heart::Black_heart():Bonus("black_heart.png")
{
    this->setScale(0.1,0.1);
    static std::default_random_engine e{static_cast<long unsigned int>(time(0))};
    std::uniform_int_distribution<int> d{-30, 30};
    velocity_x_= d(e);
}

void Black_heart::move(const sf::Time &elapsed)
{
    bounce();
    float time=elapsed.asSeconds();
    float distance_y=time*velocity_y_;
    float distance_x=time*velocity_x_;
    this->sf::Sprite::move(distance_x,distance_y);
}

void Black_heart::setBounds(float left, float right, float top, float bottom)
{
    left_border_=left;
    right_border_=right;
    top_border_=top;
    bottom_border_=bottom;
}

void Black_heart::bounce()
{
    if(this->getGlobalBounds().left<=left_border_)
    {
        this->velocity_x_=abs(this->velocity_x_);
    }
    else if((this->getGlobalBounds().left+this->getGlobalBounds().width)>=right_border_){
        this->velocity_x_=-abs(this->velocity_x_);
    }
}


Freeze::Freeze():Bonus("ice.png")
{
    setScale(0.1, 0.1);
}
void Freeze::move(const sf::Time &elapsed)
{
    float time=elapsed.asSeconds();
    float distance_y=time*speed_y_;
    this->sf::Sprite::move(0,distance_y);
}


Movable::Movable(std::string a, std::string b, std::string c, sf::RenderWindow &window)
{
    float width=window.getSize().x;
    float height=window.getSize().y;
    font.loadFromFile("Comic Sans MS 400.ttf");
    text[0].setFont(font);
    text[0].setColor(sf::Color::Cyan);
    text[0].setString(a);
    text[0].setPosition(width/4, height/2);

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString(b);
    text[1].setPosition((width/4)*2, height/2 );

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString(c);
    text[2].setPosition( (width/4)*3,height/2);
    selecteditemid=0;
}

void Movable::draw(sf::RenderWindow &window){
    for(int i=0; i<3; i++)
    {
        window.draw(text[i]);
    }
}

void Movable::MoveRight(){
    if(selecteditemid+1<3)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid++;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}
void Movable::MoveLeft(){
    if(selecteditemid-1>=0)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid--;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

int Movable::GetPressedId(){
    return selecteditemid;
}


