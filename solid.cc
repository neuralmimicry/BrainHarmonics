/*------------------------------------------------------------------------------*/
/* @file      solid.cc                                                          */
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

#include "solid.h"
#include "polyhedron.h"

bool Solid::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // Attach object to new dimension for time based calculations
    if(!time_dimension_pointer)
        {
        time_dimension_pointer = AddDimension(event_time);
        time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
        }

        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
    poly_type_list.clear();
    polyhedron_list.clear();
    
        // If object instantiated without a type specified the set one.
    if(solid_type < 1)
        {
        solid_type = TYPE_SOLID_NEURON_GEN1;
        }
    polyhedron_pool = 10;
    object_energy = 5.0;
    
    switch(solid_type)
    {
        case 0:
        {
        polyhedron_pool = 10;
        object_energy = 5.0;
            //        m_Tau = int(rand() % 50000000000000);
        break;
        }
        case TYPE_SOLID_NEURON_GEN1:
        {
            //        std::cout << "Solid selected..." << std::endl;
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_MEMBRANE_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_GEN1);
        poly_type_list.push_back(TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1);

        polyhedron_pool = 20;
        object_energy = 5.0;
            //m_Tau = int(70000000000000);
        break;
        }
        case 2:
        {
        polyhedron_pool = 10;
        object_energy = 5.0;
            //m_Tau = int(50000000000000);
        break;
        }
    }

    for(int poly_loop = 0; poly_loop < poly_type_list.size(); poly_loop++)
        {
        auto polyhedron_pointer = dynamic_cast<Polyhedron*>(CreatePolyhedron(event_time));
        polyhedron_pointer->SetObjectType(event_time, poly_type_list[poly_loop]);
        polyhedron_list.push_back(polyhedron_pointer);
        }

        //std::cout << "Polyhedrons Created: " << polyhedron_list.size() << std::endl;
    
    previous_event_time = event_time;
    return true;
}

unsigned int Solid::GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }

void Solid::SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }

void Solid::SetObjectType(std::chrono::time_point<Clock> event_time, unsigned int val)
    {
    if(solid_type != val)
        {
        solid_type = val;
        ResetParameters(event_time);
        }
    }

Solid*  Solid::CreatePolyhedron(std::chrono::time_point<Clock> event_time)
{
    if(polyhedron_list.size() < polyhedron_pool)
        {
        Polyhedron* new_object = new Polyhedron();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Solid*> Solid::CreatePolyhedrons(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(polyhedron_pool - int(polyhedron_list.size()), quantity);
    std::vector<Solid*> new_polyhedron_list;
    new_polyhedron_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Solid* new_object = CreatePolyhedron(event_time);
            if(new_object != nullptr)
                {
                polyhedron_list.push_back(new_object);
                new_polyhedron_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_polyhedron_list;
}


std::vector<Solid*> Solid::ClonePolyhedrons(std::chrono::time_point<Clock> event_time, std::vector<Solid*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Solid*  Solid::ClonePolyhedron(std::chrono::time_point<Clock> event_time, Solid* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Solid*> Solid::DestroyPolyhedrons(std::chrono::time_point<Clock> event_time, std::vector<Solid*> destruction_list)
{
        // Function TBD
}

Solid*  Solid::DestroyPolyhedron(std::chrono::time_point<Clock> event_time, Solid* destroy_object)
{
        // Function TBD
}

Solid*  Solid::AddPolyhedron(std::chrono::time_point<Clock> event_time, Solid* add_object)
{
    if(add_object != nullptr)
        {
        polyhedron_list.push_back(add_object);
        return polyhedron_list.back();
        }
    else
        return nullptr;
}

std::vector<Solid*> Solid::AddPolyhedrons(std::chrono::time_point<Clock> event_time, std::vector<Solid*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(polyhedron_pool - int(polyhedron_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Solid* result = AddPolyhedron(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return polyhedron_list;
}


Solid*  Solid::RemovePolyhedron(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Solid*> Solid::RemovePolyhedrons(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Solid*  Solid::GetPolyhedron(std::chrono::time_point<Clock> event_time, int selector)
{
    return polyhedron_list[selector];
}

std::vector<Solid*> Solid::GetPolyhedrons(std::chrono::time_point<Clock> event_time)
{
    return polyhedron_list;
}

void Solid::GluePolyhedrons(std::chrono::time_point<Clock> event_time)
{
    
}

void Solid::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Solid*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<Solid*>::iterator update_iter;
    Solid* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<Polyhedron*>(*update_iter);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<Polyhedron*>(*update_iter);
                break;
                }
            }
        update_pointer->Update(event_time);
        }
}

int Solid::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    if(event_time != previous_event_time)
        {
    std::cout << "S";

    UpdateCycle(event_time, polyhedron_list, 1);
    
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