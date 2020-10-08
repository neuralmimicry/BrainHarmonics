/*------------------------------------------------------------------------------*/
/* @file      axonbranch.cc                                                     */
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

#include "axonbranch.h"
#include "axonbouton.h"

bool AxonBranch::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(axonbranch_type < 1)
        {
        axonbranch_type = 1;
        }
    

    m_Volume = 100;
    m_SurfaceArea = 100;
    switch(axonbranch_type)
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

AxonBranch*  AxonBranch::CreateAxonBouton(std::chrono::time_point<Clock> event_time)
{
    if(axonbouton_list.size() < axonbouton_pool)
        {
        AxonBouton* new_object = new AxonBouton();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<AxonBranch*> AxonBranch::CreateAxonBoutons(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(axonbouton_pool - int(axonbouton_list.size()), quantity);
    std::vector<AxonBranch*> new_axonbouton_list;
    new_axonbouton_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            AxonBranch* new_object = CreateAxonBouton(event_time);
            if(new_object != nullptr)
                {
                axonbouton_list.push_back(new_object);
                new_axonbouton_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_axonbouton_list;
}


std::vector<AxonBranch*> AxonBranch::CloneAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<AxonBranch*>();
}

AxonBranch*  AxonBranch::CloneAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<AxonBranch*> AxonBranch::DestroyAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> destruction_list)
{
        // Function TBD
	return std::vector<AxonBranch*>();
}

AxonBranch*  AxonBranch::DestroyAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* destroy_object)
{
        // Function TBD
	return nullptr;
}

AxonBranch*  AxonBranch::AddAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* add_object)
{
    if(add_object != nullptr)
        {
        axonbouton_list.push_back(add_object);
        return axonbouton_list.back();
        }
    else
        return nullptr;
}

std::vector<AxonBranch*> AxonBranch::AddAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(axonbouton_pool - int(axonbouton_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                AxonBranch* result = AddAxonBouton(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return axonbouton_list;
}


AxonBranch*  AxonBranch::RemoveAxonBouton(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<AxonBranch*> AxonBranch::RemoveAxonBoutons(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<AxonBranch*>();
}

AxonBranch*  AxonBranch::GetAxonBouton(std::chrono::time_point<Clock> event_time, int selector)
{
    return axonbouton_list[selector];
}

std::vector<AxonBranch*> AxonBranch::GetAxonBoutons(std::chrono::time_point<Clock> event_time)
{
    return axonbouton_list;
}

int AxonBranch::Growth(std::chrono::time_point<Clock> event_time)
{
    if (object_energy > (object_energy_threshold * .9))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, 1, 10000, 0);     // Add energy
        AxonBranch* axonbouton_pointer = CreateAxonBouton(event_time);
        axonbouton_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1);
        axonbouton_list.push_back(axonbouton_pointer);
        
        object_connection_list.push_back({TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1,0,TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1,0,1.0,1.0,1.0});
        
        }
    if (object_energy < (object_energy_threshold * .1))
        {
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_size, -1, 10000, 0);     // Release energy
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

int AxonBranch::Update(std::chrono::time_point<Clock> event_time)
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
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1);
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

        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
