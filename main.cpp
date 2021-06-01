#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>
#include "klasy.h"

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
                    window_menu.close();
                    sf::RenderWindow window(sf::VideoMode(800, 600), "Falling chickens");
                    window.setFramerateLimit(30);
                    Background background(menu.get_background(), window.getSize().x, window.getSize().y);
                    Hero hero1(window, menu.get_hero_name());
                    std::vector<std::unique_ptr<Chicken>> shapes;
                    std::vector<std::unique_ptr<Strzal>> pociski;
                    for(int i=0; i<100; i++){
                        auto chicken=std::make_unique<Chicken>();
                        shapes.emplace_back(std::move(chicken));
                        if(i==0){
                            shapes[i]->setPosition(rand()%window.getSize().x, 15);
                        }
                        else if(i>0){
                            shapes[i]->setPosition(rand()%window.getSize().x,shapes[i-1]->getPosition().y-60);
                        }
                    }
                    sf::Clock clock;
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
                                }

                            }
                        }
                        window.clear(sf::Color::Black);
                        sf::Time elapsed=clock.restart();
                        window.draw(background);
                        hero1.Animacja(elapsed);

                        for(auto it=shapes.begin(); it!=shapes.end();++it){
                            for(auto it_p=pociski.begin(); it_p!=pociski.end();++it_p){
                                if(it_p->get()->getGlobalBounds().intersects((it->get()->getGlobalBounds())))
                                {
                                    shapes.erase(it);
                                    pociski.erase(it_p--);
                                }
                            }
                        }
                        window.draw(hero1);
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

                        for( auto &s : shapes) {
                            if(s->getGlobalBounds().top+s->getGlobalBounds().height>=window.getSize().y){
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
                                        if(event.type==sf::Event::KeyPressed)
                                        {
                                            komunikat.close();
                                        }


                                    }
                                    komunikat.clear(sf::Color::Black);
                                    komunikat.draw(message);
                                    komunikat.display();
                                }
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
