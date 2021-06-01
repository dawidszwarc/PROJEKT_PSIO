#ifndef KLASY_H
#define KLASY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Background: public sf::Sprite{
public:
    Background(std::string background, float x, float y);
private:
    sf::Texture texture_;
};

class Strzal:public sf::Sprite{
public:
    ~Strzal(){};
    Strzal();
    void Animacja(const sf::Time elapsed);
private:
    float speed_y_=250;
    sf::Texture texture_;
};

class Hero:public sf::Sprite{
public:
    Hero(sf::RenderWindow &window, std::string file);
    void Animacja(const sf::Time elapsed);
    void setBounds(float left, float right, float top, float bottom);
    int get_hearts();
    void set_hearts(int hearts);
private:
    float speed_x=100;
    float left_border_, right_border_, top_border_, bottom_border_;
    sf::Texture texture_;
    int hearts_=3;
    int points=0;
};

class Chicken:public sf::Sprite{
public:
    ~Chicken(){}
    Chicken();
    void animation_chicken(const sf::Time elapsed);
private:
    sf::Texture texture_;
    float speed_y_=30;
};

class Menu{
public:
    Menu(sf::RenderWindow &window);
    ~Menu(){};
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedId();
    void set_background(std::string background);
    std::string get_background();
    void set_hero_name(std::string background);
    std::string get_hero_name();
private:
    int selecteditemid;
    sf::Font font;
    sf::Text text[3];
    std::string chosen_background_name_;
    std::string chosen_hero_name_;
};
#endif // KLASY_H
