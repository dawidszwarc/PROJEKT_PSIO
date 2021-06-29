#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>
#include "klasy.h"
#include <string>

int main() {
    sf::RenderWindow window_menu(sf::VideoMode(800, 600), "Menu");

    Menu menu(window_menu);
    while (window_menu.isOpen()) {
        sf::Event event;
        while (window_menu.pollEvent(event)) {
            if(event.type==sf::Event::Closed)
            {
                window_menu.close();
            }
            if(event.type==sf::Event::KeyReleased){
                if(event.key.code==sf::Keyboard::Up)
                {
                    menu.MoveUp();
                }
                if(event.key.code==sf::Keyboard::Down)
                {
                    menu.MoveDown();
                }
                if(event.key.code==sf::Keyboard::Enter&& menu.GetPressedId()==2)
                {
                    window_menu.close();
                }
                if(event.key.code==sf::Keyboard::Enter&& menu.GetPressedId()==1)
                {
                    sf::RenderWindow jak_grac(sf::VideoMode(800, 600), "Zasady");
                    sf::Text text;
                    sf::Font font;
                    font.loadFromFile("Comic Sans MS 400.ttf");
                    text.setFont(font);
                    text.setColor(sf::Color::White);
                    text.setString("GRAJ");
                    text.setCharacterSize(15);
                    text.setString("Twoim zadaniem jest strzelanie do spadajacych kuczakow. Za trafienie do celu otrzymasz 10 punktow, jesli \n kurczak spadnie na ziemie, stracisz wtedy jedno z twoich trzech zyc. Do poruszania sie uzywaj strzalek \n lewo prawo, aby oddac strzal uzyj spacji.");
                    sf::Text text2;

                    text2.setFont(font);
                    text2.setColor(sf::Color::Magenta);
                    text2.setString("\n \n \n \n Wybierz tlo poprzez klikniecie odpowiedniej litery na klawiaturze: \n T -trawa \n N-niebo \n L-las");
                    text2.setCharacterSize(15);
                    sf::Text text3;
                    text3.setFont(font);
                    text3.setCharacterSize(15);
                    text3.setColor(sf::Color::Yellow);
                    text3.setString("\n \n \n \n \n \n \n \n \n Wybierz postac poprzez klikniecie odpowiedniej litery na klawiaturze: \n P-pikachu \n C-cyan z gry among us \n M-mario");

                    sf::Text text4;
                    text4.setFont(font);
                    text4.setCharacterSize(25);
                    text4.setColor(sf::Color::Red);
                    text4.setString("\n \n \n \n \n \n \n \n \n \n \n \n \n \n  Aby zamknac to okno nacisnij enter");

                    while (jak_grac.isOpen()) {
                        sf::Event event;
                        while (jak_grac.pollEvent(event)) {

                            if (event.type == sf::Event::Closed){
                                jak_grac.close();
                            }
                            if (event.type == sf::Event::KeyReleased){
                                if(event.key.code==sf::Keyboard::T)
                                {
                                    menu.set_background("grass.png");
                                }
                                if(event.key.code==sf::Keyboard::N)
                                {
                                    menu.set_background("niebo.png");
                                }
                                if(event.key.code==sf::Keyboard::L)
                                {
                                    menu.set_background("las.png");
                                }
                                if(event.key.code==sf::Keyboard::C)
                                {
                                    menu.set_hero_name("cyan.png");
                                }
                                if(event.key.code==sf::Keyboard::M)
                                {
                                    menu.set_hero_name("mario.png");
                                }
                                if(event.key.code==sf::Keyboard::P)
                                {
                                    menu.set_hero_name("pikachu.png");
                                }
                                if(event.key.code==sf::Keyboard::Enter)
                                {
                                    jak_grac.close();
                                }
                            }
                        }
                        jak_grac.clear(sf::Color::Black);
                        jak_grac.draw(text);
                        jak_grac.draw(text2);
                        jak_grac.draw(text3);
                        jak_grac.draw(text4);
                        jak_grac.display();
                    }
                }
                if(event.key.code==sf::Keyboard::Enter&& menu.GetPressedId()==0)
                {
                    Game game("easy");
                    window_menu.close();
                    sf::RenderWindow window(sf::VideoMode(800, 600), "Falling chickens");
                    window.setFramerateLimit(30);
                    Background background(menu.get_background(), window.getSize().x, window.getSize().y);
                    Hero hero1(window, menu.get_hero_name());
                    Heart heart;
                    float seconds=0;
                    float black_seconds=0;
                    //float chicken_frequency=1.5;
                    float chicken_seconds=0;
                    char string[20];
                    int strzaly=0;
                    float seconds_freeze=0;

                    std::vector<std::unique_ptr<Chicken>> shapes;
                    std::vector<std::unique_ptr<Strzal>> pociski;
                    std::vector<std::unique_ptr<Bonus>> bonusy;

                    for(int i=0; i<100;i++){
                        auto new_chicken=std::make_unique<Chicken>();
                        if(i==0){
                            new_chicken->setPosition(rand()%700, 0 );
                            new_chicken->speed(game);
                        }
                        if(i>1){
                            new_chicken->setPosition(rand()%700, shapes[i-1]->getPosition().y-60);
                            new_chicken->speed(game);
                        }
                        shapes.emplace_back(std::move(new_chicken));
                    }
                    sf::Text points;
                    sf::Font font;
                    font.loadFromFile("Comic Sans MS 400.ttf");
                    points.setPosition(0,50);
                    points.setFont(font);
                    points.setCharacterSize(30);
                    points.setColor(sf::Color::Red);

                    sf::Clock clock;
                    sf::Clock timer;
                    while (window.isOpen()) {
                        sf::Event event;
                        while (window.pollEvent(event)) {

                            if (event.type == sf::Event::Closed){
                                window.close();
                            }
                            if (event.type == sf::Event::KeyReleased){
                                if(event.key.code==sf::Keyboard::Space)
                                {
                                    auto pocisk=std::make_unique<Strzal>();
                                    pocisk->setPosition(hero1.getPosition().x, hero1.getPosition().y);
                                    pociski.emplace_back(std::move(pocisk));
                                    if(game.is_freeze()==true){
                                        strzaly--;
                                        std::cout<<strzaly<<std::endl;
                                    }
                                    if(strzaly==0)
                                    {
                                        game.set_freeze_false();
                                        for( auto &s : shapes) {
                                            s->speed(game);
                                        }
                                    }
                                }
                            }
                        }
                        window.clear(sf::Color::Black);
                        sf::Time elapsed=clock.restart();
                        sf::Time time=timer.restart();
                        seconds+=time.asSeconds();
                        black_seconds+=time.asSeconds();
                        seconds_freeze+=time.asSeconds();
                        chicken_seconds+=time.asSeconds();
                        itoa(hero1.get_points(), string, 10 );
                        points.setString(string);

                        if(seconds>20){
                            auto zycie=std::make_unique<Heart>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            bonusy.emplace_back(std::move(zycie));
                            seconds=0;
                        }

                        if(black_seconds>15){
                            auto zycie=std::make_unique<Black_heart>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            zycie->setBounds(0, window.getSize().x, 0, window.getSize().y);
                            bonusy.emplace_back(std::move(zycie));
                            black_seconds=0;
                        }

                        if(seconds_freeze>17){
                            auto zycie=std::make_unique<Freeze>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            bonusy.emplace_back(std::move(zycie));
                            seconds_freeze=0;
                        }

                        window.draw(background);
                        hero1.Animacja(elapsed);

                        for(auto it=shapes.begin(); it!=shapes.end();++it){
                            for(auto it_p=pociski.begin(); it_p!=pociski.end();++it_p){
                                if(it_p->get()->getGlobalBounds().intersects((it->get()->getGlobalBounds())))
                                {
                                    hero1.add_points();
                                    shapes.erase(it);
                                    pociski.erase(it_p--);
                                }
                            }
                        }
                        for(auto it=bonusy.begin(); it!=bonusy.end();++it){
                            if(it->get()->getGlobalBounds().intersects(hero1.getGlobalBounds())){
                                if(it->get()->is_black()==true && it->get()->is_freeze()==false)
                                {
                                    std::cout<<"BLACK HEART"<<std::endl;
                                    bonusy.erase(it--);
                                    hero1.usun_zycie();
                                    break;
                                }
                                else if(it->get()->is_black()==false && it->get()->is_freeze()==false){
                                    std::cout<<"HEART"<<std::endl;
                                    bonusy.erase(it--);
                                    hero1.dodaj_zycie();
                                    break;
                                }
                                else if(it->get()->is_freeze()==true && it->get()->is_black()== false)
                                {
                                    bonusy.erase(it--);
                                    std::cout<<"Zamrozono"<<std::endl;
                                    strzaly=10;
                                    for( auto &s : shapes) {
                                        s->freeze();
                                        game.set_freeze();
                                    }
                                    break;
                                }
                            }
                        }
                        hero1.draw_hero(window);
                        for(const auto &s : shapes) {
                            window.draw(*s);
                        }
                        for( auto &s : pociski) {
                            window.draw(*s);
                        }
                        for( auto &s : pociski) {
                            s->Animacja(elapsed);
                        }
                        for( auto &s : shapes) {
                            s->animation_chicken(elapsed);
                        }
                        for( auto &s : bonusy) {
                            s->move(elapsed);
                        }
                        for( const auto &s : bonusy) {
                            window.draw(*s);
                        }
                        window.draw(points);
                        for(auto it=pociski.begin(); it!=pociski.end();++it){
                            if( it->get()->getGlobalBounds().top<0)
                            {
                                pociski.erase(it);
                                break;
                            }
                        }
                        for(auto it=shapes.begin(); it!=shapes.end();++it){
                            if(it->get()->getGlobalBounds().top+it->get()->getGlobalBounds().height>=window.getSize().y){
                                hero1.usun_zycie();
                                shapes.erase(it);
                                if(hero1.get_hearts()==0){
                                    sf::RenderWindow komunikat(sf::VideoMode(800, 600),"PRZEGRALES");
                                    sf::Text message;
                                    sf::Font font;
                                    font.loadFromFile("Comic Sans MS 400.ttf");
                                    message.setFont(font);
                                    message.setString("PRZEGRALES");
                                    message.setCharacterSize(30);
                                    message.setColor(sf::Color::Red);
                                    while (komunikat.isOpen()) {
                                        sf::Event event;
                                        while (komunikat.pollEvent(event)) {
                                            if(event.type==sf::Event::Closed)
                                            {
                                                komunikat.close();
                                                window.close();
                                            }
                                        }
                                        komunikat.clear(sf::Color::Black);
                                        komunikat.draw(message);
                                        komunikat.display();
                                    }
                                }
                                break;
                            }
                        }
                        window.display();
                    }
                }
            }
        }
        window_menu.clear(sf::Color::Black);
        menu.draw(window_menu);
        window_menu.display();
    }
    return 0;
}
