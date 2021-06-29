
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
    Game game;

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
                if(event.key.code==sf::Keyboard::Enter && menu.GetPressedId()==2)
                {
                    window_menu.close();
                }
                if(event.key.code==sf::Keyboard::Enter && menu.GetPressedId()==3)
                {
                    sf::RenderWindow zasady(sf::VideoMode(800, 600), "Zasady");
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
                    text2.setString("\n \n \n \n Podczas gry co jakis czas beda spadaly bonusy, ktore ulatwia lub utrudnia twoja rozgrywke \n CZARNE SERCE- odbiera ci jedno zycie \n CZERWONE SERCE- dodaje ci jedno zycie \n LOD-zamraza kurczaki, po oddaniu 10 strzalow zaczynaja spada znowu");
                    text2.setCharacterSize(15);

                    sf::Text text3;
                    text3.setFont(font);
                    text3.setCharacterSize(25);
                    text3.setColor(sf::Color::Red);
                    text3.setString("\n \n \n \n \n Pamietaj, aby przed rozpoczeciem gry wejsc w ustaweienia gry, \n mozesz tam wybrac poziom trudnosci, postac lub tlo");


                    while (zasady.isOpen()) {
                        sf::Event event;
                        while (zasady.pollEvent(event)) {

                            if (event.type == sf::Event::Closed){
                                zasady.close();
                            }
                            if(event.type==sf::Event::KeyReleased)
                            {
                               if(event.key.code==sf::Keyboard::Enter)
                                {
                                    zasady.close();
                                }
                            }
                            zasady.clear(sf::Color::Black);
                       zasady.draw(text);
                       zasady.draw(text2);
                       zasady.draw(text3);

                            zasady.display();



                }
                    }
                }
                if(event.key.code==sf::Keyboard::Enter&& menu.GetPressedId()==1)
                {
                    sf::RenderWindow ustawienia(sf::VideoMode(800, 600), "Ustawienia");
                    Settings settings(ustawienia);


                    while (ustawienia.isOpen()) {
                        sf::Event event;
                        while (ustawienia.pollEvent(event)) {

                            if (event.type == sf::Event::Closed){
                                ustawienia.close();
                            }
                            if (event.type == sf::Event::KeyReleased){
                                if(event.key.code==sf::Keyboard::Up)
                                {
                                    settings.MoveUp();
                                }
                                if(event.key.code==sf::Keyboard::Down)
                                {
                                    settings.MoveDown();
                                }

                                if(event.key.code==sf::Keyboard::Escape)
                                {
                                    ustawienia.close();
                                }
                                if(event.key.code==sf::Keyboard::Enter&& settings.GetPressedId()==0)
                                {
                                    sf::RenderWindow postac(sf::VideoMode(800, 600), "WYBOR POSTACI");
                                    Movable wyborpostaci("Pikachu", "Cyan", "Mario", postac);

                                    while (postac.isOpen()) {
                                        sf::Event event;
                                        while (postac.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed){
                                                postac.close();
                                            }
                                            if (event.type == sf::Event::KeyReleased){
                                                if(event.key.code==sf::Keyboard::Enter&& wyborpostaci.GetPressedId()==0)
                                                {
                                                    game.set_character_name("pikachu.png");
                                                    postac.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter&& wyborpostaci.GetPressedId()==1)
                                                {
                                                    game.set_character_name("cyan.png");
                                                    postac.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter&& wyborpostaci.GetPressedId()==2)
                                                {
                                                    game.set_character_name("mario.png");
                                                    postac.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Right)
                                                {
                                                    wyborpostaci.MoveRight();
                                                }
                                                if(event.key.code==sf::Keyboard::Left)
                                                {
                                                    wyborpostaci.MoveLeft();
                                                }
                                            }
                                        }
                                        postac.clear(sf::Color::Black);
                                        wyborpostaci.draw(postac);
                                        postac.display();
                                    }
                                }
                                if(event.key.code==sf::Keyboard::Enter&& settings.GetPressedId()==1)
                                {
                                    sf::RenderWindow tlo(sf::VideoMode(800, 600), "WYBOR TLA");
                                    Movable wybortla("niebo", "trawa", "las", tlo);
                                    while (tlo.isOpen()) {
                                        sf::Event event;
                                        while (tlo.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed){
                                                tlo.close();
                                            }
                                            if (event.type == sf::Event::KeyReleased){
                                                if(event.key.code==sf::Keyboard::Enter && wybortla.GetPressedId()==0)
                                                {
                                                    game.set_background_name("niebo.png");
                                                    tlo.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter  && wybortla.GetPressedId()==1)
                                                {
                                                    game.set_background_name("grass.png");
                                                    tlo.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter  && wybortla.GetPressedId()==2)
                                                {
                                                    game.set_background_name("las.png");
                                                    tlo.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Right)
                                                {
                                                    wybortla.MoveRight();
                                                }
                                                if(event.key.code==sf::Keyboard::Left)
                                                {
                                                    wybortla.MoveLeft();
                                                }

                                            }
                                        }
                                        tlo.clear(sf::Color::Black);
                                        wybortla.draw(tlo);
                                        tlo.display();
                                    }
                                }
                                if(event.key.code==sf::Keyboard::Enter&& settings.GetPressedId()==2)
                                {
                                    sf::RenderWindow poziom(sf::VideoMode(800, 600), "POZIOM TRUDNOSCI");
                                    Movable wyborpoziomu("easy", "medium", "hard", poziom);

                                    while (poziom.isOpen()) {
                                        sf::Event event;
                                        while (poziom.pollEvent(event)) {

                                            if (event.type == sf::Event::Closed){
                                                poziom.close();
                                            }
                                            if (event.type == sf::Event::KeyReleased){
                                                if(event.key.code==sf::Keyboard::Enter && wyborpoziomu.GetPressedId()==0)
                                                {
                                                    game.set_poziom_trudnoci("easy");
                                                    poziom.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter && wyborpoziomu.GetPressedId()==1)
                                                {
                                                    game.set_poziom_trudnoci("medium");
                                                    poziom.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Enter && wyborpoziomu.GetPressedId()==2)
                                                {
                                                    game.set_poziom_trudnoci("hard");
                                                    poziom.close();
                                                }
                                                if(event.key.code==sf::Keyboard::Right)
                                                {
                                                    wyborpoziomu.MoveRight();
                                                }
                                                if(event.key.code==sf::Keyboard::Left)
                                                {
                                                    wyborpoziomu.MoveLeft();
                                                }

                                            }
                                        }
                                        poziom.clear(sf::Color::Black);
                                        wyborpoziomu.draw(poziom);
                                        poziom.display();
                                    }
                                }
                            }
                        }
                        ustawienia.clear(sf::Color::Black);
                        settings.draw(ustawienia);
                        ustawienia.display();
                    }
                }
                if(event.key.code==sf::Keyboard::Enter&& menu.GetPressedId()==0)
                {
                    std::cout<<game.get_background_name()<<std::endl;
                    std::cout<<game.get_character_name()<<std::endl;
                    std::cout<<game.get_poziom_trudnosci()<<std::endl;

                    window_menu.close();
                    sf::RenderWindow window(sf::VideoMode(800, 600), "Falling chickens");
                    window.setFramerateLimit(30);
                    Background background(game.get_background_name(), window.getSize().x, window.getSize().y);
                    Hero hero1(window, game.get_character_name());
                    Heart heart;
                    float seconds=0;
                    float black_seconds=0;
                    float chicken_frequency=game.get_chicken_frequency();
                    float heart_frequency=game.get_heart_frequency();
                    float black_heart_frequency=game.get_black_heart_frequency();
                    float ice_frequency=game.get_ice_frequency();
                    float chicken_seconds=0;
                    char string[20];
                    int strzaly=0;
                    float seconds_freeze=0;

                    std::vector<std::unique_ptr<Chicken>> shapes;
                    std::vector<std::unique_ptr<Strzal>> pociski;
                    std::vector<std::unique_ptr<Bonus>> bonusy;

//                    for(int i=0; i<100;i++){
//                        auto new_chicken=std::make_unique<Chicken>();
//                        if(i==0){
//                            new_chicken->setPosition(rand()%700, 0 );
//                            new_chicken->speed(game);
//                        }
//                        if(i>1){
//                            new_chicken->setPosition(rand()%700, shapes[i-1]->getPosition().y-60);
//                            new_chicken->speed(game);
//                        }
//                        shapes.emplace_back(std::move(new_chicken));
//                    }
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
                                    pocisk->setPosition(hero1.getPosition().x+0.5*hero1.getGlobalBounds().width, hero1.getPosition().y);
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
                        if(game.is_freeze()==false){
                        if(chicken_seconds>chicken_frequency){
                            auto zycie=std::make_unique<Chicken>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            zycie->speed(game);
                          shapes.emplace_back(std::move(zycie));
                            chicken_seconds=0;
                        }
}
                        if(seconds>heart_frequency){
                            auto zycie=std::make_unique<Heart>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            bonusy.emplace_back(std::move(zycie));
                            seconds=0;
                        }

                        if(black_seconds>black_heart_frequency){
                            auto zycie=std::make_unique<Black_heart>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            zycie->setBounds(0, window.getSize().x, 0, window.getSize().y);
                            bonusy.emplace_back(std::move(zycie));
                            black_seconds=0;
                        }

                        if(seconds_freeze>ice_frequency){
                            auto zycie=std::make_unique<Freeze>();
                            zycie->setPosition(rand()%window.getSize().x,-50);
                            bonusy.emplace_back(std::move(zycie));
                            seconds_freeze=0;
                        }

                        window.draw(background);
                        hero1.Animacja(elapsed);


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
                        for(auto it=shapes.begin(); it!=shapes.end();++it){
                            for(auto it_p=pociski.begin(); it_p!=pociski.end();++it_p){
                                if(it_p->get()->getGlobalBounds().intersects((it->get()->getGlobalBounds())))
                                {
                                    hero1.add_points();
                                    shapes.erase(it--);
                                    pociski.erase(it_p++);
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

                                break;
                            }
                        }
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
