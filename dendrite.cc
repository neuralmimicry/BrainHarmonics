/*------------------------------------------------------------------------------*/
/* @file      dendrite.cc                                                       */
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

#include "dendrite.h"
#include "dendritebranch.h"

bool Dendrite::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(dendrite_type < 1)
        {
        dendrite_type = 1;
        }

    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    object_energy_threshold = 500;
    switch(dendrite_type)
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

Dendrite*  Dendrite::CreateDendriteBranch(std::chrono::time_point<Clock> event_time)
{
    if(dendritebranch_list.size() < dendritebranch_pool)
        {
        DendriteBranch* new_object = new DendriteBranch();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Dendrite*> Dendrite::CreateDendriteBranches(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(dendritebranch_pool - int(dendritebranch_list.size()), quantity);
    std::vector<Dendrite*> new_dendritebranch_list;
    new_dendritebranch_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Dendrite* new_object = CreateDendriteBranch(event_time);
            if(new_object != nullptr)
                {
                dendritebranch_list.push_back(new_object);
                new_dendritebranch_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_dendritebranch_list;
}


std::vector<Dendrite*> Dendrite::CloneDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<Dendrite*>();
}

Dendrite*  Dendrite::CloneDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<Dendrite*> Dendrite::DestroyDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> destruction_list)
{
        // Function TBD
	return std::vector<Dendrite*>();
}

Dendrite*  Dendrite::DestroyDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* destroy_object)
{
        // Function TBD
	return nullptr;
}

Dendrite*  Dendrite::AddDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* add_object)
{
    if(add_object != nullptr)
        {
        dendritebranch_list.push_back(add_object);
        return dendritebranch_list.back();
        }
    else
        return nullptr;
}

std::vector<Dendrite*> Dendrite::AddDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(dendritebranch_pool - int(dendritebranch_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Dendrite* result = AddDendriteBranch(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return dendritebranch_list;
}


Dendrite*  Dendrite::RemoveDendriteBranch(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Dendrite*> Dendrite::RemoveDendriteBranches(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<Dendrite*>();
}

Dendrite*  Dendrite::GetDendriteBranch(std::chrono::time_point<Clock> event_time, int selector)
{
    return dendritebranch_list[selector];
}

std::vector<Dendrite*> Dendrite::GetDendriteBranches(std::chrono::time_point<Clock> event_time)
{
    return dendritebranch_list;
}

int Dendrite::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);
        Dendrite* dendritebranch_pointer = CreateDendriteBranch(event_time);
        dendritebranch_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_DENDRITEBRANCH_GEN1);
        dendritebranch_list.push_back(dendritebranch_pointer);
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

int Dendrite::Update(std::chrono::time_point<Clock> event_time)
{
       // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);

        auto visualisation_pointer = dynamic_cast<Solid*>(dynamic_cast<Neuron*>(visualisation_list[0]))->CreatePolyhedron(event_time);
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_GEN1);
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
            //            for(std::vector<DendriteBranch>::iterator it = dendritebranch_list.begin(); it != dendritebranch_list.end(); ++it)
            {
#pragma omp task
                //                it->Update(event_time);
            }
        }
#pragma omp single nowait
        {
        /*
        for(std::vector<Dendrite*>::iterator it = dynamic_cast<Dendrite*>(dendritebranch_list.begin()); it != dynamic_cast<Dendrite*>(dendritebranch_list.end()); ++it)
            {
#pragma omp task
            (*it)->Update(event_time);
            }
         */
        }
    }
    
    if (object_energy < object_energy_threshold)
        {
        /*
        for(std::vector<Dendrite*>::iterator it = dendritebranch_list.begin(); it != dendritebranch_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, it->AddTemporalAdjustment(event_time), 100, 1);   // absorb energy
            }
            //        for(std::vector<DendriteBranch>::iterator it = dendritebranch_list.begin(); it != dendritebranch_list.end(); ++it) {
            //            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, it->AddTemporalAdjustment(event_time), 100, 1);   // absorb energy
         */
        }
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    if (duration_since_last_event > 1000)
        {
        Growth(event_time);
        object_energy_threshold = object_size * 1000;
        }
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

