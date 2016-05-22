//
//  localtime.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 22/05/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef localtime_hpp
#define localtime_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>

class LocalTime
{
public:
    LocalTime()
    {
    timeSpacer = 1.0;
    };
    
    virtual ~LocalTime() {};
    
    time_t theTimeNow()
    {
    now = time(0);
    now *= timeSpacer;
    return now;
    }
    
    double getTimeSpacer() {return timeSpacer;};
    
    void setTimeSpacer(double val) {timeSpacer = val;};
    
protected:
        // Only the member functions of the class and its descendent classes can access protected members. The class instances are denied access to protected members.
    
    double timeSpacer;       //!< Member variable "timeSpacer"
    time_t now;
    time_t convertedTime;

private:
};
#endif /* localtime_hpp */
