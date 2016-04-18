/*------------------------------------------------------------------------------*/
/* @file      multiscreen.h                                                     */
/* @details   Each screen as an instance                                        */
/* @author    Paul Isaac's                                                      */
/* @date      16.02.2016                                                        */
/* @Copyright © 2016 Paul Isaac's. All rights reserved.                         */
/*------------------------------------------------------------------------------*/

/* Code snippets used:                                                          */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com          */
/* The class defines a data point and the operations that can be carried out on */
/* it.                                                                          */
/* Using the hierarchical linking the aim is to develop the application to      */
/* relate to real-world physics. This will then ease mapping between simulation,*/
/* emulation and real-world universes.                                          */

#ifndef MULTISCREEN_H
#define MULTISCREEN_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourcePath.hpp"

class MultiScreen
{
    
public:
    /** Default constructor */
    MultiScreen() {};
    /** Default destructor */
    virtual ~MultiScreen() {};
    
    virtual int runScreen(sf::RenderWindow &app) = 0;
    
    void creation() {std::cout << "Screen added." << std::endl; }
    
protected:
private:

};


#endif // MULTISCREEN_H
