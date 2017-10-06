/*------------------------------------------------------------------------------*/
/* @file      neuroreceptor.cc                                                  */
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

#include "neuroreceptor.h"
#include "neurotransmitter.h"

bool Neuroreceptor::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(neuroreceptor_type < 1)
        {
        neuroreceptor_type = 1;
        }
    
    object_energy = 10 * ((rand() % 30 + 85) / 100);
    object_energy_threshold = 2000 * ((rand() % 30 + 85) / 100);
    object_size = 1 * ((rand() % 30 + 85) / 100);
    object_energyFull = 100;
    m_Ions = 0;
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    
    switch(neuroreceptor_type)
    {
        case 0:
        {
        object_size = 3 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 1:
        {
        object_size = 2 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 2:
        {
        object_size = 1 * ((rand() % 30 + 85) / 100);
        break;
        }
    }
    return true;
}

CognitiveNetwork*  Neuroreceptor::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
    if(neurotransmitter_list.size() < neurotransmitter_pool)
        {
        Neurotransmitter* new_object = new Neurotransmitter();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> Neuroreceptor::CreateNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(neurotransmitter_pool - int(neurotransmitter_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_neurotransmitter_list;
    new_neurotransmitter_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateNeurotransmitter(event_time);
            if(new_object != nullptr)
                {
                neurotransmitter_list.push_back(new_object);
                new_neurotransmitter_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_neurotransmitter_list;
}


std::vector<CognitiveNetwork*> Neuroreceptor::CloneNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  Neuroreceptor::CloneNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> Neuroreceptor::DestroyNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  Neuroreceptor::DestroyNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  Neuroreceptor::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        neurotransmitter_list.push_back(add_object);
        return neurotransmitter_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> Neuroreceptor::AddNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(neurotransmitter_pool - int(neurotransmitter_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddNeurotransmitter(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return neurotransmitter_list;
}


CognitiveNetwork*  Neuroreceptor::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> Neuroreceptor::RemoveNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  Neuroreceptor::GetNeurotransmitter(std::chrono::time_point<Clock> event_time, int selector)
{
    return neurotransmitter_list[selector];
}

std::vector<CognitiveNetwork*> Neuroreceptor::GetNeurotransmitters(std::chrono::time_point<Clock> event_time)
{
    return neurotransmitter_list;
}


bool Neuroreceptor::CompatibilityCheck(std::chrono::time_point<Clock> event_time, int neurotransmitterType)
{
    switch(m_typeReceptor)
    {
        case 0:
        {
        if(neurotransmitterType >=0)
            {
            return true;
            }
        else
            {
            return false;
            }
        break;
        }
        case 1:
        {
        if(neurotransmitterType >=0)
            {
            return true;
            }
        else
            {
            return false;
            }
        break;
        }
        return false;
    }
    
}

int Neuroreceptor::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
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
            // Extra programming: Change 0 to correct point address
            // Use GetPoint to enable movement across Synapse to Neuroreceptor
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &GetPoint(event_time, 0)->object_energy, object_energy * 0.1, 10000, 1);
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - (object_energy * 0.1), 10000, 1);
        }
    

    /*
    for(std::vector<CognitiveNetwork*>::iterator it = neurotransmitter_list.begin(); it != neurotransmitter_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
    if (object_energy > 0)
        {
        for(std::vector<CognitiveNetwork*>::iterator it = neurotransmitter_list.begin(); it != neurotransmitter_list.end(); ++it)
            {
                //            // time_dimension_pointer->AddTemporalAdjustment(event_time, &temporal_adjustment_list, &object_energy, (0-object_energy)/neurotransmitter_list.size(), 100, 1);   // redistribute energy
            (*it)->AddTemporalAdjustment(event_time, object_energy/neurotransmitter_list.size());
            }
        }
*/    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    if (object_energy > 0)
        {
        if (GetReceptorBindingState(event_time))
            {
            }
        if (duration_since_last_event > 1000)
            {
            object_energy -= 1;
            }
        if (object_energy <= 0)
            {
            object_energy = 0;
            m_Ions = 0;
            SetReceptorBindingState(event_time, false);
            }
        }
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

