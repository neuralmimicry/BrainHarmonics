/*------------------------------------------------------------------------------*/
/* @file      quad.h                                                            */
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
/* emulation and real-world polygons.                                          */

#ifndef BRAINHARMONICS_QUAD_H
#define BRAINHARMONICS_QUAD_H

#include <iostream>
#include "polygon.h"

class Quad : public Polygon
{
public:
    Quad() : Quad(0) {}
    
    Quad(unsigned int object_type) : Quad(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Quad(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Polygon() {}
    
    Quad(unsigned int object_type, std::chrono::time_point<Clock> event_time, Polygon& polygon_connector) : Polygon(polygon_connector)
    {
        // Each quad type will have its own parameter ranges. The default is 0
    quad_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Quad", quad_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Quad() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    int GetQuadID(std::chrono::time_point<Clock> event_time) const { return quadQuadID; }
    double GetQuadX1(std::chrono::time_point<Clock> event_time) const { return quadQuadX1; }
    double GetQuadY1(std::chrono::time_point<Clock> event_time) const { return quadQuadY1; }
    double GetQuadX2(std::chrono::time_point<Clock> event_time) const { return quadQuadX2; }
    double GetQuadY2(std::chrono::time_point<Clock> event_time) const { return quadQuadY2; }
    double GetQuadX3(std::chrono::time_point<Clock> event_time) const { return quadQuadX3; }
    double GetQuadY3(std::chrono::time_point<Clock> event_time) const { return quadQuadY3; }
    double GetQuadX4(std::chrono::time_point<Clock> event_time) const { return quadQuadX4; }
    double GetQuadY4(std::chrono::time_point<Clock> event_time) const { return quadQuadY4; }
    double GetQuadTTL(std::chrono::time_point<Clock> event_time) const { return quadQuadTTL; }
    int GetQuadCounter(std::chrono::time_point<Clock> event_time) const { return quadQuadCounter; }
    bool GetInQuad(std::chrono::time_point<Clock> event_time, double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4, double Threshold)
    {
    return true;
    }

    void SetQuadID(std::chrono::time_point<Clock> event_time, int val) { quadQuadID = val; }
    void SetQuadX1(std::chrono::time_point<Clock> event_time, double val) { quadQuadX1 = val; quadQuadX2 = val; }
    void SetQuadY1(std::chrono::time_point<Clock> event_time, double val) { quadQuadY1 = val; quadQuadY4 = val; }
    void SetQuadX2(std::chrono::time_point<Clock> event_time, double val) { quadQuadX1 = val; quadQuadX2 = val; }
    void SetQuadY2(std::chrono::time_point<Clock> event_time, double val) { quadQuadY2 = val; quadQuadY3 = val; }
    void SetQuadX3(std::chrono::time_point<Clock> event_time, double val) { quadQuadX3 = val; quadQuadX4 = val; }
    void SetQuadY3(std::chrono::time_point<Clock> event_time, double val) { quadQuadY2 = val; quadQuadY3 = val; }
    void SetQuadX4(std::chrono::time_point<Clock> event_time, double val) { quadQuadX3 = val; quadQuadX4 = val; }
    void SetQuadY4(std::chrono::time_point<Clock> event_time, double val) { quadQuadY1 = val; quadQuadY4 = val; }
    void SetQuadTTL(std::chrono::time_point<Clock> event_time, double val) { quadQuadTTL = val; }
    void SetQuadCounter(std::chrono::time_point<Clock> event_time, int val) { quadQuadCounter = val; }

    int Update(std::chrono::time_point<Clock> event_time);
  
protected:
private:
    int quadQuadID;
    double quadQuadX1; //!< Member variable "quadQuadX1"
    double quadQuadY1; //!< Member variable "quadQuadY1"
    double quadQuadX2; //!< Member variable "quadQuadX2"
    double quadQuadY2; //!< Member variable "quadQuadY2"
    double quadQuadX3; //!< Member variable "quadQuadX3"
    double quadQuadY3; //!< Member variable "quadQuadY3"
    double quadQuadX4; //!< Member variable "quadQuadX4"
    double quadQuadY4; //!< Member variable "quadQuadY4"
    double quadQuadTTL;
    int quadQuadCounter;
    int quad_type;
    bool object_disabled = true;
    bool object_initialised = false;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
};

#endif // BRAINHARMONICS_QUAD_H
