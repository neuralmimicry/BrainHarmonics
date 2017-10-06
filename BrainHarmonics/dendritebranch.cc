/*------------------------------------------------------------------------------*/
/* @file      dendritebranch.cc                                                 */
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

#include "dendritebranch.h"
#include "dendritecleft.h"

bool DendriteBranch::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(dendritebranch_type < 1)
        {
        dendritebranch_type = 1;
        }

    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    object_energy_threshold = 200;
    switch(m_DendriteBranchType)
    {
        case 0:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        m_Length = 100;
        break;
        }
        case 1:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        m_Length = 100;
        break;
        }
        case 2:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        m_Length = 100;
        break;
        }
    }
    return true;
}

DendriteBranch*  DendriteBranch::CreateDendriteCleft(std::chrono::time_point<Clock> event_time)
{
    if(dendritecleft_list.size() < dendritecleft_pool)
        {
        DendriteCleft* new_object = new DendriteCleft();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<DendriteBranch*> DendriteBranch::CreateDendriteClefts(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(dendritecleft_pool - int(dendritecleft_list.size()), quantity);
    std::vector<DendriteBranch*> new_dendritecleft_list;
    new_dendritecleft_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            DendriteBranch* new_object = CreateDendriteCleft(event_time);
            if(new_object != nullptr)
                {
                dendritecleft_list.push_back(new_object);
                new_dendritecleft_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_dendritecleft_list;
}


std::vector<DendriteBranch*> DendriteBranch::CloneDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> cloning_list, double perfection_membership)
{
        // Function TBD
}

DendriteBranch*  DendriteBranch::CloneDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<DendriteBranch*> DendriteBranch::DestroyDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> destruction_list)
{
        // Function TBD
}

DendriteBranch*  DendriteBranch::DestroyDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* destroy_object)
{
        // Function TBD
}

DendriteBranch*  DendriteBranch::AddDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* add_object)
{
    if(add_object != nullptr)
        {
        dendritecleft_list.push_back(add_object);
        return dendritecleft_list.back();
        }
    else
        return nullptr;
}

std::vector<DendriteBranch*> DendriteBranch::AddDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(dendritecleft_pool - int(dendritecleft_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                DendriteBranch* result = AddDendriteCleft(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return dendritecleft_list;
}


DendriteBranch*  DendriteBranch::RemoveDendriteCleft(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<DendriteBranch*> DendriteBranch::RemoveDendriteClefts(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

DendriteBranch*  DendriteBranch::GetDendriteCleft(std::chrono::time_point<Clock> event_time, int selector)
{
    return dendritecleft_list[selector];
}

std::vector<DendriteBranch*> DendriteBranch::GetDendriteClefts(std::chrono::time_point<Clock> event_time)
{
    return dendritecleft_list;
}

int DendriteBranch::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);
        DendriteBranch* dendritecleft_pointer = CreateDendriteCleft(event_time);
        dendritecleft_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1);
        dendritecleft_list.push_back(dendritecleft_pointer);
        }
    if (object_energy < (object_energy_threshold * .1))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, -1, 10000, 0);
        }
    if (object_size < 1)
        {
        object_size = 1;
        }
    if (object_size > 50)
        {
        object_size = 50;
        }
    return 0;
}

int DendriteBranch::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
 
        auto visualisation_pointer = dynamic_cast<Solid*>(dynamic_cast<Neuron*>(visualisation_list[0]))->CreatePolyhedron(event_time);
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_GEN1);
        visualisation_list.push_back(visualisation_pointer);
        }
    
    if(event_time != previous_event_time)
        {
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
#pragma omp parallel
    {
#pragma omp single nowait
        {
        for(std::vector<DendriteBranch*>::iterator it = dendritecleft_list.begin(); it != dendritecleft_list.end(); ++it)
            {
#pragma omp task
            (*it)->Update(event_time);
            }
        }
    }
    
    if (object_energy < object_energy_threshold)
        {
        for(std::vector<DendriteBranch*>::iterator it = dendritecleft_list.begin(); it != dendritecleft_list.end(); ++it)
            {
            (*it)->AddTemporalAdjustment(event_time, &object_energy, 0, 100, 1);   // absorb energy
            }
        }
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

