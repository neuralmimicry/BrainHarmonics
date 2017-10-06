/*------------------------------------------------------------------------------*/
/* @file      soma.cc                                                           */
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

#include "axonhillock.h"
#include "dendrite.h"
#include "soma.h"

void Soma::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    soma_type = object_type;
    Soma::ResetParameters(event_time);
}

bool Soma::ResetParameters(std::chrono::time_point<Clock> event_time)
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
    if(soma_type < 1)
        {
        soma_type = 1;
        }
    
    object_energy = 5.0;
    

    axonhillock_pool = 0;
    dendrite_pool = 0;
    m_Volume = 100;
    m_SurfaceArea = 100;
    object_energy = 10;
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 100, 10000000, 0);     // Add energy
    object_energyInc = 100;
    object_energyDec = 100;
    object_energyLeak = 1;
    object_energy_threshold = 1000;
    object_size = 10;
    m_TimeDilation = 1;
    m_TimeThreshold = 1000;

    switch(soma_type)
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
    
    previous_event_time = event_time;
    return true;
}

Soma*  Soma::CreateAxonHillock(std::chrono::time_point<Clock> event_time)
{
    if(axonhillock_list.size() < axonhillock_pool)
        {
        AxonHillock* new_object = new AxonHillock();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Soma*> Soma::CreateAxonHillocks(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(axonhillock_pool - int(axonhillock_list.size()), quantity);
    std::vector<Soma*> new_axonhillock_list;
    new_axonhillock_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Soma* new_object = CreateAxonHillock(event_time);
            if(new_object != nullptr)
                {
                axonhillock_list.push_back(new_object);
                new_axonhillock_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_axonhillock_list;
}


std::vector<Soma*> Soma::CloneAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Soma*  Soma::CloneAxonHillock(std::chrono::time_point<Clock> event_time, Soma* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Soma*> Soma::DestroyAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> destruction_list)
{
        // Function TBD
}

Soma*  Soma::DestroyAxonHillock(std::chrono::time_point<Clock> event_time, Soma* destroy_object)
{
        // Function TBD
}

Soma*  Soma::AddAxonHillock(std::chrono::time_point<Clock> event_time, Soma* add_object)
{
    if(add_object != nullptr)
        {
        axonhillock_list.push_back(add_object);
        return axonhillock_list.back();
        }
    else
        return nullptr;
}

std::vector<Soma*> Soma::AddAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(axonhillock_pool - int(axonhillock_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Soma* result = AddAxonHillock(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return axonhillock_list;
}


Soma*  Soma::RemoveAxonHillock(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Soma*> Soma::RemoveAxonHillocks(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Soma*  Soma::GetAxonHillock(std::chrono::time_point<Clock> event_time, int selector)
{
    return axonhillock_list[selector];
}

std::vector<Soma*> Soma::GetAxonHillocks(std::chrono::time_point<Clock> event_time)
{
    return axonhillock_list;
}


Soma*  Soma::CreateDendrite(std::chrono::time_point<Clock> event_time)
{
    if(dendrite_list.size() < dendrite_pool)
        {
        Dendrite* new_object = new Dendrite();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Soma*> Soma::CreateDendrites(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(dendrite_pool - int(dendrite_list.size()), quantity);
    std::vector<Soma*> new_dendrite_list;
    new_dendrite_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Soma* new_object = CreateDendrite(event_time);
            if(new_object != nullptr)
                {
                dendrite_list.push_back(new_object);
                new_dendrite_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_dendrite_list;
}


std::vector<Soma*> Soma::CloneDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Soma*  Soma::CloneDendrite(std::chrono::time_point<Clock> event_time, Soma* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Soma*> Soma::DestroyDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> destruction_list)
{
        // Function TBD
}

Soma*  Soma::DestroyDendrite(std::chrono::time_point<Clock> event_time, Soma* destroy_object)
{
        // Function TBD
}

Soma*  Soma::AddDendrite(std::chrono::time_point<Clock> event_time, Soma* add_object)
{
    if(add_object != nullptr)
        {
        dendrite_list.push_back(add_object);
        return dendrite_list.back();
        }
    else
        return nullptr;
}

std::vector<Soma*> Soma::AddDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(dendrite_pool - int(dendrite_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Soma* result = AddDendrite(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return dendrite_list;
}


Soma*  Soma::RemoveDendrite(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Soma*> Soma::RemoveDendrites(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Soma*  Soma::GetDendrite(std::chrono::time_point<Clock> event_time, int selector)
{
    return dendrite_list[selector];
}

std::vector<Soma*> Soma::GetDendrites(std::chrono::time_point<Clock> event_time)
{
    return dendrite_list;
}


int Soma::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);
        Soma* dendrite_pointer = CreateDendrite(event_time);
        dendrite_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_GEN1);
        dendrite_list.push_back(dendrite_pointer);
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

int Soma::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        
        auto parent_visualisation_pointer = dynamic_cast<Solid*>(parent_pointer->GetVisualisationList()[0]);
        auto visualisation_pointer = dynamic_cast<Solid*>(parent_visualisation_pointer->CreatePolyhedron(event_time));
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_GEN1);
        visualisation_list.push_back(visualisation_pointer);
        
        Soma* axonhillock_pointer = CreateAxonHillock(event_time);
        axonhillock_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_GEN1);
        axonhillock_list.push_back(axonhillock_pointer);
        
        object_connection_list.push_back({TYPE_SOLID_POLYHEDRON_SOMA_GEN1,0,TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1,0,1.0,1.0,1.0});
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
        for(std::vector<Soma*>::iterator it = axonhillock_list.begin(); it != axonhillock_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    for(std::vector<Soma*>::iterator it = dendrite_list.begin(); it != dendrite_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    /*
    if (object_energy < object_energy_threshold)
        {
        for(std::vector<Dendrite*>::iterator it = dendrite_list.begin(); it != dendrite_list.end(); ++it)
            {
            (*it)->AddTemporalAdjustment(event_time, &object_energy, it->AddTemporalAdjustment(event_time), 100, 1);
            }
        }
        // For forward propagation of energy to Axonhillock
    if (object_energy >= object_energy_threshold)
        {
        std::cout << "Soma threshold crossed." << std::endl;
        for(std::vector<AxonHillock*>::iterator it = axonhillock_list.begin(); it != axonhillock_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-object_energy_threshold)/axonhillock_list.size(), 100, 1);   // redistribute energy
            (*it)->AddTemporalAdjustment(event_time, object_energy_threshold/axonhillock_list.size());
            }
            // Try back propagating to dendrites
        for(std::vector<Soma*>::iterator it = dendrite_list.begin(); it != dendrite_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-(object_energy - object_energy_threshold))/dendrite_list.size(), 100, 1);   // redistribute energy
            
            (*it)->AddTemporalAdjustment(event_time, (object_energy_threshold - object_energy_threshold)/dendrite_list.size());
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
