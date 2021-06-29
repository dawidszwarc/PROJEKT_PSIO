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
class Bonus:public AnimatedSprite{
public:
    Bonus(std::string file);
    virtual void move(const sf::Time &elapsed)=0;
      virtual bool is_freeze()=0;
    virtual bool is_black()=0;



};

class Heart:public Bonus{
public:
    Heart();
    void move(const sf::Time &elapsed);
    bool is_freeze(){return false;}
    bool is_black(){return false;};

private:
    float speed_y_=40;


};
class Black_heart:public Bonus{
public:
   Black_heart();
    void move(const sf::Time &elapsed);
    void setBounds(float left, float right, float top, float bottom);
    void bounce();

    bool is_freeze(){return false;}
    bool is_black(){return true;};

private:
    int velocity_y_=60;
    int velocity_x_;
    float left_border_, right_border_, top_border_, bottom_border_;


};
class Freeze:public Bonus{
public:
    Freeze();
    void move(const sf::Time &elapsed);
    bool is_black(){return false;}
    bool is_freeze(){return true;};
private:
    float speed_y_=100;
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
    float speed_x=130;
    float left_border_, right_border_, top_border_, bottom_border_;
    sf::Texture texture_;
    int hearts_=3;
    int points=0;
     std::vector<std::unique_ptr<Heart>> zycie;
};


class Game{
public:
    std::string get_poziom_trudnosci();
    std::string get_character_name();
      std::string get_background_name();
    void set_freeze(){is_freeze_=true;};
    void set_freeze_false(){is_freeze_=false;}
    bool is_freeze(){return  is_freeze_;};
    void set_poziom_trudnoci(std::string arg);
    void set_background_name(std::string arg);
    void set_character_name(std::string arg);
    float get_ice_frequency();
    float get_chicken_frequency();
    float get_heart_frequency();
    float get_black_heart_frequency();
private:
    std::string poziom_trudnosci="easy", character_name_="pikachu.png", background_name_="niebo.png";
    bool is_freeze_=false;
};

class Chicken:public AnimatedSprite{
public:
    ~Chicken(){}
    Chicken();
    void speed(Game &game);
    void animation_chicken(const sf::Time elapsed);
    void set_speed(int arg);
    void freeze();

private:
    sf::Texture texture_;
    float speed_y_;
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
    sf::Text text[4];
};
class Settings{
public:
    Settings(sf::RenderWindow &window);
    ~Settings(){};
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedId();
private:
    int selecteditemid;
    sf::Font font;
    sf::Text text[3];

};

class Movable{
public:
    Movable(std::string a, std::string b, std:: string c, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);
    void MoveRight();
    void MoveLeft();
    int GetPressedId();
protected:
    int selecteditemid;
    sf::Font font;
    sf::Text text[3];
};

#endif // KLASY_H
