/*------------------------------------------------------------------------------*/
/* @file      polygon.h                                                         */
/* @details   Assign structure for scalar values                                */
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

#ifndef BRAINHARMONICS_POLYGON_H
#define BRAINHARMONICS_POLYGON_H

#include <iostream>
#include <vector>
#include "polyhedron.h"

class Polygon : public Polyhedron
{
public:
    Polygon() : Polygon(0) {}
    
    Polygon(unsigned int object_type) : Polygon(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Polygon(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Polyhedron() {}
    
    Polygon(unsigned int object_type, std::chrono::time_point<Clock> event_time, Polyhedron& polyhedron_connector) : Polyhedron(polyhedron_connector)
    {
        // Each polygon type will have its own parameter ranges. The default is 0
    polygon_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Polygon", polygon_type);
    object_disabled = true;
    }
    virtual ~Polygon() {}
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    
    unsigned int SetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return polygonCounter; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { polygonCounter = val; }

    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
private:
    unsigned int polygonCounter; //!< Member variable "polygonCounter"
    int polygon_type;
    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::time_point<Clock> time_object_created;
    bool object_disabled = true;
    bool object_initialised = false;
    int duration_since_last_event;
    
};

#endif // BRAINHARMONICS_POLYGON_H
