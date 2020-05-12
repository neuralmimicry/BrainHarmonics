//
//  node.h
//  RobotEngineering
//
//  Created by Paul Isaac's on 05/05/15.
//  Copyright (c) 2015 Paul Isaac's. All rights reserved.
//
//#include <algorithm>            /**< For max, min, sort function                   */
#include <math.h>               /**< For Sine, Cosine, Power, Fabs & Sqrt functions*/

#ifndef ROBOTENGINEERING_NODE_H
#define ROBOTENGINEERING_NODE_H

class node
{
        // current position
    int xPos;
    int yPos;
        // total distance already travelled to reach the node
    int level;
        // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority
    
    int dir; // Number of directions to move
    
public:
    node(int xp, int yp, int d, int p) { xPos = xp; yPos = yp; level = d; priority = p;}
    ~node() {}
    int GetxPos() const {return xPos;}
    int GetyPos() const {return yPos;}
    int GetLevel() const {return level;}
    int GetPriority() const {return priority;}
    
    void updatePriority(const int & xDest, const int & yDest)
    {
    priority = level + estimate(xDest, yDest)*10; //A*
    }
    
        // give better priority to going straight instead of diagonally
    void nextLevel(const int & i) // i: direction
    {
    level += ( dir == 8?(i%2==0?10:14):10 );
    }
    
        // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const
    {
    static int xd, yd, d;
    xd = xDest - xPos;
    yd = yDest - yPos;
    
        // Euclidian Distance
    d = static_cast<int>(sqrt(xd*xd+yd*yd));
    
        // Manhattan distance
        // d = std::abs(xd) + std::abs(yd);
    
        // Chebyshev distance
        // d = std::max(std::abs(xd), std::abs(yd));
    
    return(d);
    }
};

#endif // ROBOTENGINEERING_NODE_H
