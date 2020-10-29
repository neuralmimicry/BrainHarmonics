/*------------------------------------------------------------------------------*/
/* @file      axonhillock.cc                                                    */
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

#include "axon.h"
#include "axonhillock.h"

void AxonHillock::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
	axonhillock_type = object_type;
    AxonHillock::ResetParameters(event_time);
}

bool AxonHillock::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(axonhillock_type < 1)
        {
        axonhillock_type = 1;
        }
    
   
    m_Volume = 100;
    m_SurfaceArea = 100;
    object_size = 10;
    object_energy_threshold = 100;
    switch(axonhillock_type)
    {
        case 0:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        object_size = 10;
        break;
        }
        case 1:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        object_size = 10;
        break;
        }
        case 2:
        {
        m_Volume = 100;
        m_SurfaceArea = 100;
        object_size = 10;
        break;
        }
    }
    return true;
}


AxonHillock*  AxonHillock::CreateAxon(std::chrono::time_point<Clock> event_time)
{
    if(axon_list.size() < axon_pool)
        {
        Axon* new_object = new Axon();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<AxonHillock*> AxonHillock::CreateAxons(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(axon_pool - int(axon_list.size()), quantity);
    std::vector<AxonHillock*> new_axon_list;
    new_axon_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            AxonHillock* new_object = CreateAxon(event_time);
            if(new_object != nullptr)
                {
                axon_list.push_back(new_object);
                new_axon_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_axon_list;
}


std::vector<AxonHillock*> AxonHillock::CloneAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<AxonHillock*>();
}

AxonHillock*  AxonHillock::CloneAxon(std::chrono::time_point<Clock> event_time, AxonHillock* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<AxonHillock*> AxonHillock::DestroyAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> destruction_list)
{
        // Function TBD
	return std::vector<AxonHillock*>();
}

AxonHillock*  AxonHillock::DestroyAxon(std::chrono::time_point<Clock> event_time, AxonHillock* destroy_object)
{
        // Function TBD
	return nullptr;
}

AxonHillock*  AxonHillock::AddAxon(std::chrono::time_point<Clock> event_time, AxonHillock* add_object)
{
    if(add_object != nullptr)
        {
        axon_list.push_back(add_object);
        return axon_list.back();
        }
    else
        return nullptr;
}

std::vector<AxonHillock*> AxonHillock::AddAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(axon_pool - int(axon_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                AxonHillock* result = AddAxon(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return axon_list;
}


AxonHillock*  AxonHillock::RemoveAxon(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<AxonHillock*> AxonHillock::RemoveAxons(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<AxonHillock*>();
}

AxonHillock*  AxonHillock::GetAxon(std::chrono::time_point<Clock> event_time, int selector)
{
    return axon_list[selector];
}

std::vector<AxonHillock*> AxonHillock::GetAxons(std::chrono::time_point<Clock> event_time)
{
    return axon_list;
}


int AxonHillock::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9));
    {
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);
    }
    if (object_energy < (object_energy_threshold * .1));
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

int AxonHillock::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
            // Attach a Dimension pointer to object for time based calculations
        time_dimension_pointer = AddDimension(event_time);
        time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
        object_initialised = ResetParameters(event_time);

        auto visualisation_pointer = dynamic_cast<Solid*>(dynamic_cast<Neuron*>(visualisation_list[0]))->CreatePolyhedron(event_time);
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1);
        visualisation_list.push_back(visualisation_pointer);

        AxonHillock* axon_pointer = CreateAxon(event_time);
        axon_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_AXON_GEN1);
        axon_list.push_back(axon_pointer);

        object_connection_list.push_back({TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1,0,TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_GEN1,0,1.0,1.0,1.0});

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

        for(std::vector<AxonHillock*>::iterator it = axon_list.begin(); it != axon_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
        for(std::vector<AxonHillock*>::iterator it = axon_list.begin(); it != axon_list.end(); ++it)
            {
            (*it)->AddTemporalAdjustment(event_time, &object_energy, (0-object_energy)/axon_list.size(), 100, 1);   // redistribute energy
            }
        Growth(event_time);
        object_energy_threshold = object_size * 1000;
        }
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
