/*------------------------------------------------------------------------------*/
/* @file      dendritecleft.cc                                                  */
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

#include "dendritecleft.h"
#include "neuroreceptor.h"

bool DendriteCleft::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(dendritecleft_type < 1)
        {
        dendritecleft_type = 1;
        }

    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    object_energy_threshold = 200;
    object_size = 10;
    
    switch(dendritecleft_type)
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

/*
int DendriteCleft::ConnectSynapse(std::chrono::time_point<Clock> event_time, Synapse* link_synapse, double distance)
{
    s_SynapseDescription synapseConnection;
    synapseConnection.s_Synapse = link_synapse;
    synapseConnection.s_Distance = distance;
    m_SynapseList.push_back(synapseConnection);
    return 0;
}
*/

DendriteCleft*  DendriteCleft::CreateNeuroreceptor(std::chrono::time_point<Clock> event_time)
{
    if(neuroreceptor_list.size() < neuroreceptor_pool)
        {
        Neuroreceptor* new_object = new Neuroreceptor();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<DendriteCleft*> DendriteCleft::CreateNeuroreceptors(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(neuroreceptor_pool - int(neuroreceptor_list.size()), quantity);
    std::vector<DendriteCleft*> new_neuroreceptor_list;
    new_neuroreceptor_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            DendriteCleft* new_object = CreateNeuroreceptor(event_time);
            if(new_object != nullptr)
                {
                neuroreceptor_list.push_back(new_object);
                new_neuroreceptor_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_neuroreceptor_list;
}


std::vector<DendriteCleft*> DendriteCleft::CloneNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<DendriteCleft*>();
}

DendriteCleft*  DendriteCleft::CloneNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<DendriteCleft*> DendriteCleft::DestroyNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> destruction_list)
{
        // Function TBD
	return std::vector<DendriteCleft*>();
}

DendriteCleft*  DendriteCleft::DestroyNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* destroy_object)
{
        // Function TBD
	return nullptr;
}

DendriteCleft*  DendriteCleft::AddNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* add_object)
{
    if(add_object != nullptr)
        {
        neuroreceptor_list.push_back(add_object);
        return neuroreceptor_list.back();
        }
    else
        return nullptr;
}

std::vector<DendriteCleft*> DendriteCleft::AddNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(neuroreceptor_pool - int(neuroreceptor_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                DendriteCleft* result = AddNeuroreceptor(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return neuroreceptor_list;
}


DendriteCleft*  DendriteCleft::RemoveNeuroreceptor(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<DendriteCleft*> DendriteCleft::RemoveNeuroreceptors(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<DendriteCleft*>();
}

DendriteCleft*  DendriteCleft::GetNeuroreceptor(std::chrono::time_point<Clock> event_time, int selector)
{
    return neuroreceptor_list[selector];
}

std::vector<DendriteCleft*> DendriteCleft::GetNeuroreceptors(std::chrono::time_point<Clock> event_time)
{
    return neuroreceptor_list;
}


int DendriteCleft::GrowthSurface(std::chrono::time_point<Clock> event_time, double surf_change)
{
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &m_SurfaceArea, surf_change, 100, 0);
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, -100, 100, 0);
    return 0;
}

int DendriteCleft::GrowthVolume(std::chrono::time_point<Clock> event_time, double vol_change)
{
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &m_Volume, vol_change, 100, 0);
    int func_status = GrowthSurface(event_time, vol_change*0.1);
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, -100, 100, 0);
    return 0;
}

int DendriteCleft::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);

        auto visualisation_pointer = dynamic_cast<Solid*>(dynamic_cast<Neuron*>(visualisation_list[0]))->CreatePolyhedron(event_time);
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1);
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

        for(std::vector<DendriteCleft*>::iterator it = neuroreceptor_list.begin(); it != neuroreceptor_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
    if (object_energy < object_energy_threshold)
        {
        for(std::vector<DendriteCleft*>::iterator it = neuroreceptor_list.begin(); it != neuroreceptor_list.end(); ++it)
            {
            (*it)->AddTemporalAdjustment(event_time, &object_energy, 0, 100, 1);   // absorb energy
            }
        }
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    if (duration_since_last_event > 1000)
        {
        object_energy_threshold = object_size * 1000;
        }
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
