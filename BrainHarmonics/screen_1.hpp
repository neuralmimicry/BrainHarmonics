    //
    //  screen_1.hpp
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 16/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef screen_1_hpp
#define screen_1_hpp

#include <iostream>
#include "multiscreen.h"
    //#include "SFML/Graphics.hpp"
#include "ResourcePath.hpp"

class Screen_1 : public MultiScreen
{
public:
    /** Default constructor */
    Screen_1();
    /** Default destructor */
    virtual ~Screen_1() {};
    void creation();
    virtual int runScreen(sf::RenderWindow &app);
    
protected:
private:
    bool m_onScreen; //!< Member variable "m_onScreen"
};

Screen_1::Screen_1()
{
    m_onScreen = false;
}
void Screen_1::creation() {std::cout << "Screen 0 created." << std::endl; }

int Screen_1::runScreen(sf::RenderWindow &app)
{
    sf::Event Event;
    bool Running = true;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    sf::Text Menu4;
    int menu = 0;
    
    if (!Font.loadFromFile(resourcePath() + "DroidSans.ttf"))
        {
        std::cerr << "Error loading font." << std::endl;
        return (-1);
        }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Add item");
    Menu1.setPosition({ 280.f, 160.f });
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Remove item");
    Menu2.setPosition({ 280.f, 220.f });
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Up level");
    Menu3.setPosition({ 280.f, 280.f });
    
    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Down level");
    Menu4.setPosition({ 280.f, 320.f });
    
    while (Running)
        {
        while(app.pollEvent(Event))
            {
                // Window closed
            if (Event.type == sf::Event::Closed)
                {
                return (-1);
                }
            }
        if (menu == 0)
            {
            Menu1.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu1.setFillColor(sf::Color(255, 0, 0, 255));
            Menu2.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu2.setFillColor(sf::Color(255, 255, 255, 255));
            Menu3.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu3.setFillColor(sf::Color(255, 0, 0, 255));
            Menu4.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu4.setFillColor(sf::Color(255, 0, 0, 255));
            }
        else
            {
            Menu1.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu1.setFillColor(sf::Color(255, 255, 255, 255));
            Menu2.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu2.setFillColor(sf::Color(255, 0, 0, 255));
            Menu3.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu3.setFillColor(sf::Color(255, 255, 255, 255));
            Menu4.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu4.setFillColor(sf::Color(255, 255, 255, 255));
            }
        
        app.clear();
        app.display();
        }
    return (-1);
}
#endif /* screen_1_hpp */
