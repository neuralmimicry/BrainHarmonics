/*------------------------------------------------------------------------------*/
/* @file      axonbouton.cc                                                     */
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

#include "axonbouton.h"
#include "synapse.h"
#include "synapticvesicle.h"

bool AxonBouton::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(axonbouton_type < 1)
        {
        axonbouton_type = 1;
        }

    m_Volume = 100;
    m_SurfaceArea = 100;
    switch(axonbouton_type)
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

AxonBouton*  AxonBouton::CreateSynapticVesicle(std::chrono::time_point<Clock> event_time)
{
    if(synapticvesicle_list.size() < synapticvesicle_pool)
        {
        SynapticVesicle* new_object = new SynapticVesicle();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<AxonBouton*> AxonBouton::CreateSynapticVesicles(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(synapticvesicle_pool - int(synapticvesicle_list.size()), quantity);
    std::vector<AxonBouton*> new_synapticvesicle_list;
    new_synapticvesicle_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            AxonBouton* new_object = CreateSynapticVesicle(event_time);
            if(new_object != nullptr)
                {
                synapticvesicle_list.push_back(new_object);
                new_synapticvesicle_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_synapticvesicle_list;
}


std::vector<AxonBouton*> AxonBouton::CloneSynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<AxonBouton*>();
}

AxonBouton*  AxonBouton::CloneSynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<AxonBouton*> AxonBouton::DestroySynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> destruction_list)
{
        // Function TBD
	return std::vector<AxonBouton*>();
}

AxonBouton*  AxonBouton::DestroySynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* destroy_object)
{
        // Function TBD
	return nullptr;
}

AxonBouton*  AxonBouton::AddSynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* add_object)
{
    if(add_object != nullptr)
        {
        synapticvesicle_list.push_back(add_object);
        return synapticvesicle_list.back();
        }
    else
        return nullptr;
}

std::vector<AxonBouton*> AxonBouton::AddSynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(synapticvesicle_pool - int(synapticvesicle_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                AxonBouton* result = AddSynapticVesicle(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return synapticvesicle_list;
}


AxonBouton*  AxonBouton::RemoveSynapticVesicle(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<AxonBouton*> AxonBouton::RemoveSynapticVesicles(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<AxonBouton*>();
}

AxonBouton*  AxonBouton::GetSynapticVesicle(std::chrono::time_point<Clock> event_time, int selector)
{
    return synapticvesicle_list[selector];
}

std::vector<AxonBouton*> AxonBouton::GetSynapticVesicles(std::chrono::time_point<Clock> event_time)
{
    return synapticvesicle_list;
}

int AxonBouton::GrowthSurface(std::chrono::time_point<Clock> event_time, double surf_change)
{
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &m_SurfaceArea, surf_change, 100, 0);
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, -100, 100, 0);
    return 0;
}

int AxonBouton::GrowthVolume(std::chrono::time_point<Clock> event_time, double vol_change)
{
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &m_Volume, vol_change, 100, 0);
    int func_status = GrowthSurface(event_time, vol_change*0.1);
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, -100, 100, 0);
    return 0;
}

int AxonBouton::Update(std::chrono::time_point<Clock> event_time)
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
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1);
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

    int release_State;
    
    for(std::vector<AxonBranch*>::iterator it = axonbouton_list.begin(); it != axonbouton_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
    if (object_energy > 0)
        {
        for(std::vector<AxonBranch*>::iterator it = axonbouton_list.begin(); it != axonbouton_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-(object_energy/2))/axonbouton_list.size(), 100, 1);   // redistribute energy
                                                                                                                       //            (*it)->AddTemporalAdjustment(event_time, object_energy/axonbouton_list.size());
            }
        }
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    if (duration_since_last_event > 1000)
        {
        for(std::vector<AxonBranch*>::iterator it = axonbouton_list.begin(); it != axonbouton_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-(object_energy/2))/axonbouton_list.size(), 100, 1);   // redistribute(*it)->GetReleaseState(event_time);
            }
        }
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
