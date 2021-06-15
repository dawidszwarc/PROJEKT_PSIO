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
class AnimatedSprite:public sf::Sprite{
    public:
       AnimatedSprite(std::string texture_file_name){
            texture_.loadFromFile(texture_file_name);
            this->setTexture(texture_);
        }
            private:
                sf::Texture texture_;
};

class Heart:public AnimatedSprite{
public:
    Heart();
    void move_heart(const sf::Time &elapsed);
private:
    float speed_y_=40;
};

class Strzal:public AnimatedSprite{
public:
    ~Strzal(){};
    Strzal();
    void Animacja(const sf::Time elapsed);
private:
    float speed_y_=250;
    sf::Texture texture_;
};

class Hero:public AnimatedSprite{
public:
    Hero(sf::RenderWindow &window, std::string file);
    void Animacja(const sf::Time elapsed);
    void setBounds(float left, float right, float top, float bottom);
    int get_hearts();
    int get_points();
    void add_points();
    void set_hearts(int hearts);
    void draw_hero(sf::RenderWindow &window);
    void usun_zycie();
    void dodaj_zycie();
    void jump();
private:
    float speed_x=100;
    float left_border_, right_border_, top_border_, bottom_border_;
    sf::Texture texture_;
    int hearts_=3;
    int points=0;
     std::vector<std::unique_ptr<Heart>> zycie;
};

class Chicken:public AnimatedSprite{
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
