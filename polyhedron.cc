/*------------------------------------------------------------------------------*/
/* @file      polyhedron.cc                                                     */
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

#include "polyhedron.h"
#include "polygon.h"
    //#include "point.h"
#include <cmath>

bool Polyhedron::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(polyhedron_type < 1)
        {
        polyhedron_type = TYPE_SOLID_POLYHEDRON_SOMA_GEN1;
        }
    polygon_list.clear();
    point_list.clear();
    point_pool = 1000;
    polygon_pool = 100;
    object_energy = 5.0;

    switch(polyhedron_type)
    {
        case 0:
        {
            //        m_Tau = int(rand() % 50000000000000);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_MEMBRANE_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_GEN1:
        {
        polygon_pool = 100;
        GenerateCylinderPoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_GEN1:
        {
        polygon_pool = 100;
        GenerateCylinderPoints(event_time);
        break;
        }
        case TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1:
        {
        polygon_pool = 100;
        GenerateSpherePoints(event_time);
        break;
        }
        case 2:
        {
            //m_Tau = int(50000000000000);
        break;
        }
    }
    
        //    std::cout << "Points Created: " << point_list.size() << std::endl;
        //   std::cout << "Polygons Created: " << polygon_list.size() << std::endl;
    
    previous_event_time = event_time;
    return true;
}

void Polyhedron::SetObjectType(std::chrono::time_point<Clock> event_time, unsigned int val)
{
    if(polyhedron_type != val)
        {
        polyhedron_type = val;
        ResetParameters(event_time);
        }
}

Polyhedron*  Polyhedron::CreatePolygon(std::chrono::time_point<Clock> event_time)
{
    if(polygon_list.size() < polygon_pool)
        {
        Polygon* new_object = new Polygon();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Polyhedron*> Polyhedron::CreatePolygons(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(polygon_pool - int(polygon_list.size()), quantity);
    std::vector<Polyhedron*> new_polygon_list;
    new_polygon_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Polyhedron* new_object = CreatePolygon(event_time);
            if(new_object != nullptr)
                {
                polygon_list.push_back(new_object);
                new_polygon_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_polygon_list;
}

std::vector<Polyhedron*> Polyhedron::ClonePolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Polyhedron*  Polyhedron::ClonePolygon(std::chrono::time_point<Clock> event_time, Polyhedron* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Polyhedron*> Polyhedron::DestroyPolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> destruction_list)
{
        // Function TBD
}

Polyhedron*  Polyhedron::DestroyPolygon(std::chrono::time_point<Clock> event_time, Polyhedron* destroy_object)
{
        // Function TBD
}

Polyhedron*  Polyhedron::AddPolygon(std::chrono::time_point<Clock> event_time, Polyhedron* add_object)
{
    if(add_object != nullptr)
        {
        polygon_list.push_back(add_object);
        return polygon_list.back();
        }
    else
        return nullptr;
}

std::vector<Polyhedron*> Polyhedron::AddPolygons(std::chrono::time_point<Clock> event_time, std::vector<Polyhedron*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(polygon_pool - int(polygon_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Polyhedron* result = AddPolygon(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return polygon_list;
}


Polyhedron*  Polyhedron::RemovePolygon(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Polyhedron*> Polyhedron::RemovePolygons(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Polyhedron*  Polyhedron::GetPolygon(std::chrono::time_point<Clock> event_time, int selector)
{
    return polygon_list[selector];
}

std::vector<Polyhedron*> Polyhedron::GetPolygons(std::chrono::time_point<Clock> event_time)
{
    return polygon_list;
}

Point*  Polyhedron::GetPoint(std::chrono::time_point<Clock> event_time, int selector)
{
    return point_list[selector];
}

std::vector<Point*> Polyhedron::GetPoints(std::chrono::time_point<Clock> event_time)
{
    return point_list;
}

void Polyhedron::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Point*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<Point*>::iterator update_iter;
    Point* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<Point*>(*update_iter);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<Point*>(*update_iter);
                break;
                }
            }
        update_pointer->Update(event_time);
        }
}

int Polyhedron::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    if(event_time != previous_event_time)
        {

    std::cout << "P";
    UpdateCycle(event_time, point_list, 1);
    
    // time_dimension_pointer->AdjustCounters(event_time);
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    
    if (object_energy < 0)
        {
        object_energy = 0;
        }
    
    if (duration_since_last_event > 0 && object_energy > 0)
        {
        }
        previous_event_time = event_time;
        }
    return 0;
}

int Polyhedron::GenerateSpherePoints(std::chrono::time_point<Clock> event_time)
{
    
    double x, y, z;
        // generate random points on unit sphere
    for(int i=0; i<50; i++)
        {
        double u = rand();
        double v = rand();
        double phi = 2.0*3.14159265*u;
        double theta = acos(2.0*v-1.0);
        
        x = std::cos(phi)*std::sin(theta);
        y = std::sin(phi)*std::sin(theta);
        z = std::cos(theta);
        
        auto new_point = AddPoint(event_time);
        Point* point_pointer = dynamic_cast<Point*>(new_point);
        point_pointer->SetPointPosition(event_time, {x, y, z});
        point_list.push_back(point_pointer);
        }
    
    return 0;
}

int Polyhedron::GenerateCylinderPoints(std::chrono::time_point<Clock> event_time)
{
        //    std::cout << "Generating cylinder..." << std::endl;
    double x, y, z;
    double l = 50;
    int num_points = 100;
        // generate random points on unit sphere
    for(int i=0; i<num_points; i++)
        {
        double u = rand();
        double v = rand();
        double phi = 2.0*3.14159265*u;
        double theta = acos(2.0*v-1.0);
        
        x = std::cos(phi)*std::sin(theta);
        y = std::sin(phi)*std::sin(theta);
        z = (l / num_points) * i;
        
        auto new_point = AddPoint(event_time);
        Point* point_pointer = dynamic_cast<Point*>(new_point);
        point_pointer->SetPointPosition(event_time, {x, y, z});
        point_list.push_back(point_pointer);
        }
    
    return 0;
}