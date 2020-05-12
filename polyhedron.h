/*------------------------------------------------------------------------------*/
/* @file      polyhedron.h                                                      */
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

#ifndef BRAINHARMONICS_POLYHEDRON_H
#define BRAINHARMONICS_POLYHEDRON_H

#include <iostream>
#include "solid.h"
#include "point.h"

class Polyhedron : public Solid
{
    friend class Soma;
    friend class Membrane;
public:
    Polyhedron() : Polyhedron(0) {}
    
    Polyhedron(unsigned int object_type) : Polyhedron(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Polyhedron(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Solid() {}
    
    Polyhedron(unsigned int object_type, std::chrono::time_point<Clock> event_time, Solid& solid_connector) : Solid(solid_connector)
    {
        // Each polyhedron type will have its own parameter ranges. The default is 0
    polyhedron_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Polyhedron", polyhedron_type);
    object_disabled = true;
    }
    virtual ~Polyhedron() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return polyhedronCounter; }

    void setCounter(unsigned int val) { polyhedronCounter = val; }

    void SetObjectType(std::chrono::time_point<Clock> event_time, unsigned int val);

    Polyhedron*  CreatePolygon(std::chrono::time_point<Clock> event_time);
    
    std::vector<Polyhedron*> CreatePolygons(std::chrono::time_point<Clock> event_time, int quantity);
    
    Polyhedron*  ClonePolygon(std::chrono::time_point<Clock> event_time, Polyhedron* clone_object, double perfection_membership);
    
    std::vector<Polyhedron*> ClonePolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> cloning_list, double perfection_membership);
    
    Polyhedron*  DestroyPolygon(std::chrono::time_point<Clock> event_time, Polyhedron* destroy_object);
    
    std::vector<Polyhedron*> DestroyPolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> destruction_list);
    
    Polyhedron*  AddPolygon(std::chrono::time_point<Clock> event_time, Polyhedron* add_object);
    
    std::vector<Polyhedron*> AddPolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> add_objects);
    
    Polyhedron*  RemovePolygon(std::chrono::time_point<Clock> event_time);
    
    std::vector<Polyhedron*> RemovePolygons(std::chrono::time_point<Clock> event_time, int quantity);
    
    Polyhedron*  GetPolygon(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Polyhedron*> GetPolygons(std::chrono::time_point<Clock> event_time);

    Point*  GetPoint(std::chrono::time_point<Clock> event_time, int selector);

    std::vector<Point*> GetPoints(std::chrono::time_point<Clock> event_time);
    
    int GenerateSpherePoints(std::chrono::time_point<Clock> event_time);

    int GenerateCylinderPoints(std::chrono::time_point<Clock> event_time);

    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Point*> set_of_update_pointers, unsigned int pointer_type);
    
    int Update(std::chrono::time_point<Clock> event_time);

protected:
    std::vector<Polyhedron*> polygon_list;
    std::vector<Point*> point_list;
    
private:
    unsigned int polyhedronCounter; //!< Member variable "polyhedronCounter"
    unsigned int polyhedron_type = 0;
    bool object_disabled = true;
    bool object_initialised = false;
    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::time_point<Clock> time_object_created;
    int duration_since_last_event;
    
    int polygon_pool;
    int point_pool;
};

#endif // BRAINHARMONICS_POLYHEDRON_H
