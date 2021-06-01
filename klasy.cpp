#include "klasy.h"

Background::Background(std::string background, float x, float y){
    texture_.loadFromFile(background);
    texture_.setRepeated(true);
    this->setTexture(texture_);
    this->setTextureRect(sf::IntRect(0,0,x,y));
}

Strzal::Strzal(){
    texture_.loadFromFile("fireshot.png");
    this->setTexture(texture_);
    this->setScale(0.03,0.05);
}

void Strzal::Animacja(const sf::Time elapsed){
    float time=elapsed.asSeconds();
    float distance_y=speed_y_*time;
    this->move(0,-distance_y);
}

Hero::Hero(sf::RenderWindow &window, std::string file)
{
    texture_.loadFromFile(file);
    this->setTexture(texture_);
    this->setScale(0.1, 0.1);
    this->setBounds(0, window.getSize().x, 0, window.getSize().y);
    this->setPosition((window.getSize().x/2.0)-((this->getGlobalBounds().width)/2.0),(window.getSize().y-this->getGlobalBounds().height));
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
    text[0].setPosition((width/1.9), (height/4*1));

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString("ZASADY GRY + USTAWIENIA");
    text[1].setPosition(width/3, (height/4)*2);

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("WYJSCIE");
    text[2].setPosition(width/2, (height/4)*3);
    selecteditemid=0;

}

void Menu::draw(sf::RenderWindow &window){
    for(int i=0; i<3; i++)
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
    if(selecteditemid+1<3)
    {
        text[selecteditemid].setColor(sf::Color::White);
        selecteditemid++;
        text[selecteditemid].setColor(sf::Color::Cyan);
    }
}

int Menu::GetPressedId(){
    return selecteditemid;
}

void Menu::set_background(std::string background){
    chosen_background_name_=background;

}

std::string Menu::get_background(){
    return chosen_background_name_;
}

void Menu::set_hero_name(std::string background){
    chosen_hero_name_=background;

}

std::string Menu::get_hero_name(){
    return chosen_hero_name_;
}

Chicken::Chicken(){
    this->setScale(0.1,0.1);
    texture_.loadFromFile("chicken.png");
    this->setTexture(texture_);
}

void Chicken::animation_chicken(const sf::Time elapsed){
    float time=elapsed.asSeconds();
    float distance_y=time*speed_y_;
    this->move(0,distance_y);
}
