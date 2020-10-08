/*------------------------------------------------------------------------------*/
/* @file      membrane.cc                                                       */
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

#include "membrane.h"
#include "membranechannel.h"

void Membrane::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    membrane_type = object_type;
    Membrane::ResetParameters(event_time);
}

bool Membrane::ResetParameters(std::chrono::time_point<Clock> event_time)
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
    
        // If object instantiated without a type specified the set one.
    if(membrane_type < 1)
        {
        membrane_type = 1;
        }
    
    membranechannel_pool = 0;
    m_Volume = 100;
    m_SurfaceArea = 100;
    object_energy = 0;
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 100, 10000000, 0);     // Add energy
    object_energyInc = 100;
    object_energyDec = 100;
    object_energyLeak = 1;
    object_energy_threshold = 1000;
    object_size = 10;
    m_TimeDilation = 1;
    m_TimeThreshold = 1000;
    
    switch(membrane_type)
    {
        case 0:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        break;
        }
        case 1:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        break;
        }
        case 2:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        break;
        }
    }
    return true;
}

Membrane*  Membrane::CreateMembraneChannel(std::chrono::time_point<Clock> event_time)
{
    if(membranechannel_list.size() < membranechannel_pool)
        {
        MembraneChannel* new_object = new MembraneChannel();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Membrane*> Membrane::CreateMembraneChannels(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(membranechannel_pool - int(membranechannel_list.size()), quantity);
    std::vector<Membrane*> new_membranechannel_list;
    new_membranechannel_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Membrane* new_object = CreateMembraneChannel(event_time);
            if(new_object != nullptr)
                {
                membranechannel_list.push_back(new_object);
                new_membranechannel_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_membranechannel_list;
}


std::vector<Membrane*> Membrane::CloneMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<Membrane*>();
}

Membrane*  Membrane::CloneMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<Membrane*> Membrane::DestroyMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> destruction_list)
{
        // Function TBD
	return std::vector<Membrane*>();
}

Membrane*  Membrane::DestroyMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* destroy_object)
{
        // Function TBD
	return nullptr;
}

Membrane*  Membrane::AddMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* add_object)
{
    if(add_object != nullptr)
        {
        membranechannel_list.push_back(add_object);
        return membranechannel_list.back();
        }
    else
        return nullptr;
}

std::vector<Membrane*> Membrane::AddMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(membranechannel_pool - int(membranechannel_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Membrane* result = AddMembraneChannel(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return membranechannel_list;
}


Membrane*  Membrane::RemoveMembraneChannel(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Membrane*> Membrane::RemoveMembraneChannels(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<Membrane*>();
}

Membrane*  Membrane::GetMembraneChannel(std::chrono::time_point<Clock> event_time, int selector)
{
    return membranechannel_list[selector];
}

std::vector<Membrane*> Membrane::GetMembraneChannels(std::chrono::time_point<Clock> event_time)
{
    return membranechannel_list;
}



int Membrane::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);
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

int Membrane::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
	/*
	 * commented the following lines to avoid crash.
	 * Todo:- debug the cause and uncomment once fixed
	 */
        /*auto visualisation_pointer = dynamic_cast<Solid*>(dynamic_cast<Neuron*>(visualisation_list[0]))->CreatePolyhedron(event_time);
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_MEMBRANE_GEN1);
        visualisation_list.push_back(visualisation_pointer);*/
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

        for(std::vector<Membrane*>::iterator it = membranechannel_list.begin(); it != membranechannel_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }

    /*
     if (object_energy < object_energy_threshold)
     {

     }
     // For forward propagation of energy to Axonhillock
     if (object_energy >= object_energy_threshold)
     {
     std::cout << "Membrane threshold crossed." << std::endl;
     for(std::vector<MembraneChannel*>::iterator it = membranechannel_list.begin(); it != membranechannel_list.end(); ++it)
     {
     // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-object_energy_threshold)/membranechannel_list.size(), 100, 1);   // redistribute energy
     (*it)->AddTemporalAdjustment(event_time, object_energy_threshold/membranechannel_list.size());
     }

     }
     */
        Growth(event_time);
        object_energy_threshold = object_size * 1000;
        }
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

