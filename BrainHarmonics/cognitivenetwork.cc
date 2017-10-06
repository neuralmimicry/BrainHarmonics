/*------------------------------------------------------------------------------*/
/* @file      cognitivenetwork.cc                                               */
/* @details   Holding object for components of a network                        */
/* @author    Paul Isaac's                                                      */
/* @date      24.04.2017                                                        */
/* @Copyright © 2017 Paul Isaac's. All rights reserved.                         */
/*------------------------------------------------------------------------------*/

/* Code snippets used:                                                          */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com          */
/* The class defines a data point and the operations that can be carried out on */
/* it.                                                                          */
/* Using the hierarchical linking the aim is to develop the application to      */
/* relate to real-world physics. This will then ease mapping between simulation,*/
/* emulation and real-world universes.                                          */

#include "cognitiveinput.h"
#include "cognitivenetwork.h"
#include "cognitiveoutput.h"
#include "interneuronspace.h"
#include "neuron.h"
#include "neurotransmitter.h"
#include "orbital.h"
#include "synapse.h"

void CognitiveNetwork::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    cognitivenetwork_type = object_type;
    CognitiveNetwork::ResetParameters(event_time);
}

bool CognitiveNetwork::ResetParameters(std::chrono::time_point<Clock> event_time)
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
    if(cognitivenetwork_type < 1)
        {
        cognitivenetwork_type = 1;
        }
    
        // Each object is not available for use by default.
    interneuronspace_pool = 2;
    neuron_pool = 10;
    synapse_pool = 100;
    neurotransmitter_pool = 100;
    orbital_pool = 100;
    object_disabled = true;
    m_Counter = 0;
    m_GateKeeper = 0;
    m_ChannelMin = -1;
    m_ChannelMax = 1;
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 100, 10000000, 0);     // Add energy
    object_energy_threshold = 2000;
    object_size = 1;
    m_Spike = 1;
    m_RestingPotential = -70; // in millivolts
    m_Tag = 0;
    cognitivenetworkCapacity = 0;                   // Set initial type value
    
    switch(cognitivenetwork_type)
    {
        case 0:
        {
        m_RestingPotential = -80;
        object_size = 3;
        break;
        }
        case 1:
        {
        m_RestingPotential = -70;
        object_size = 2;
        break;
        }
        case 2:
        {
        m_RestingPotential = -60;
        object_size = 1;
        break;
        }
    }
    return true;
}

void CognitiveNetwork::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<CognitiveNetwork*>::iterator update_iter;
    CognitiveNetwork* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<CognitiveInput*>(*update_iter);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<CognitiveOutput*>(*update_iter);
                break;
                }
                case 3:
                {
                auto update_pointer = dynamic_cast<InterneuronSpace*>(*update_iter);
                break;
                }
                case 4:
                {
                auto update_pointer = dynamic_cast<Orbital*>(*update_iter);
                break;
                }
                case 5:
                {
                auto update_pointer = dynamic_cast<Neuron*>(*update_iter);
                break;
                }
                case 6:
                {
                auto update_pointer = dynamic_cast<Synapse*>(*update_iter);
                break;
                }
                case 7:
                {
                auto update_pointer = dynamic_cast<Neurotransmitter*>(*update_iter);
                break;
                }
            }
        update_pointer->Update(event_time);
        }
}


int CognitiveNetwork::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    if(event_time != previous_event_time)
        {

    std::cout << "C";
    UpdateCycle(event_time, cognitiveinput_list, 1);
    UpdateCycle(event_time, cognitiveoutput_list, 2);
    UpdateCycle(event_time, interneuronspace_list, 3);
    UpdateCycle(event_time, orbital_list, 4);
    UpdateCycle(event_time, neuron_list, 5);
    UpdateCycle(event_time, synapse_list, 6);
    UpdateCycle(event_time, neurotransmitter_list, 7);
    
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
        
        for(std::vector<CognitiveNetwork*>::iterator it = interneuronspace_list.begin(); it != interneuronspace_list.end(); ++it)
            {
            (*it)->Update(event_time);
            }
            //        growth(event_time);
        object_energy_threshold = object_size * 1000;
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}



CognitiveNetwork* CognitiveNetwork::CreateCognitiveInput(std::chrono::time_point<Clock> event_time)
{
    if(cognitiveinput_list.size() < cognitiveinput_pool)
        {
        CognitiveInput* new_object = new CognitiveInput();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateCognitiveInputs(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(cognitiveinput_pool - int(cognitiveinput_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_cognitiveinput_list;
    new_cognitiveinput_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateCognitiveInput(event_time);
            if(new_object != nullptr)
                {
                cognitiveinput_list.push_back(new_object);
                new_cognitiveinput_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_cognitiveinput_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        cognitiveinput_list.push_back(add_object);
        return interneuronspace_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(cognitiveinput_pool - int(cognitiveinput_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddCognitiveInput(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return cognitiveinput_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveCognitiveInput(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveCognitiveInputs(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetCognitiveInput(std::chrono::time_point<Clock> event_time, int selector)
{
    return cognitiveinput_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetCognitiveInputs(std::chrono::time_point<Clock> event_time)
{
    return cognitiveinput_list;
}


CognitiveNetwork* CognitiveNetwork::CreateCognitiveOutput(std::chrono::time_point<Clock> event_time)
{
    if(cognitiveoutput_list.size() < cognitiveoutput_pool)
        {
        CognitiveOutput* new_object = new CognitiveOutput();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateCognitiveOutputs(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(cognitiveoutput_pool - int(cognitiveoutput_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_cognitiveoutput_list;
    new_cognitiveoutput_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateCognitiveOutput(event_time);
            if(new_object != nullptr)
                {
                cognitiveoutput_list.push_back(new_object);
                new_cognitiveoutput_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_cognitiveoutput_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        cognitiveoutput_list.push_back(add_object);
        return interneuronspace_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(cognitiveoutput_pool - int(cognitiveoutput_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddCognitiveOutput(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return cognitiveoutput_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveCognitiveOutput(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveCognitiveOutputs(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetCognitiveOutput(std::chrono::time_point<Clock> event_time, int selector)
{
    return cognitiveoutput_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetCognitiveOutputs(std::chrono::time_point<Clock> event_time)
{
    return cognitiveoutput_list;
}




CognitiveNetwork*  CognitiveNetwork::CreateInterneuronSpace(std::chrono::time_point<Clock> event_time)
{
    if(interneuronspace_list.size() < interneuronspace_pool)
        {
        InterneuronSpace* new_object = new InterneuronSpace();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateInterneuronSpaces(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(interneuronspace_pool - int(interneuronspace_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_interneuronspace_list;
    new_interneuronspace_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateInterneuronSpace(event_time);
            if(new_object != nullptr)
                {
                interneuronspace_list.push_back(new_object);
                new_interneuronspace_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_interneuronspace_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        interneuronspace_list.push_back(add_object);
        return interneuronspace_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(interneuronspace_pool - int(interneuronspace_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddInterneuronSpace(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return interneuronspace_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveInterneuronSpace(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveInterneuronSpaces(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetInterneuronSpace(std::chrono::time_point<Clock> event_time, int selector)
{
    return interneuronspace_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetInterneuronSpaces(std::chrono::time_point<Clock> event_time)
{
    return interneuronspace_list;
}


CognitiveNetwork*  CognitiveNetwork::CreateOrbital(std::chrono::time_point<Clock> event_time)
{
    if(orbital_list.size() < orbital_pool)
        {
        Orbital* new_object = new Orbital();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateOrbitals(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(orbital_pool - int(orbital_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_orbital_list;
    new_orbital_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateOrbital(event_time);
            if(new_object != nullptr)
                {
                orbital_list.push_back(new_object);
                new_orbital_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_orbital_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        orbital_list.push_back(add_object);
        return orbital_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(orbital_pool - int(orbital_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddOrbital(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return orbital_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveOrbital(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveOrbitals(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetOrbital(std::chrono::time_point<Clock> event_time, int selector)
{
    return orbital_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetOrbitals(std::chrono::time_point<Clock> event_time)
{
    return orbital_list;
}



CognitiveNetwork*  CognitiveNetwork::CreateNeuron(std::chrono::time_point<Clock> event_time)
{
    if(neuron_list.size() < neuron_pool)
        {
        Neuron* new_object = new Neuron();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateNeurons(std::chrono::time_point<Clock> event_time, int quantity)
{
        //std::cout << "To create: " << quantity;
        //std::cout << " from pool: " << neuron_pool;
        //std::cout << " with already: " << int(neuron_list.size());
    quantity = std::min(int(neuron_pool - int(neuron_list.size())), int(quantity));
        //std::cout << " Allowed: " << quantity;
    std::vector<CognitiveNetwork*> new_neuron_list;
    new_neuron_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateNeuron(event_time);
            if(new_object != nullptr)
                {
                neuron_list.push_back(new_object);
                new_neuron_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
        //std::cout << " Created: " << new_neuron_list.size() << std::endl;
    return new_neuron_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        neuron_list.push_back(add_object);
        return neuron_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(neuron_pool - int(neuron_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddNeuron(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return neuron_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveNeuron(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveNeurons(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetNeuron(std::chrono::time_point<Clock> event_time, int selector)
{
    return neuron_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetNeurons(std::chrono::time_point<Clock> event_time)
{
    return neuron_list;
}


CognitiveNetwork*  CognitiveNetwork::CreateSynapse(std::chrono::time_point<Clock> event_time)
{
    if(synapse_list.size() < synapse_pool)
        {
        Synapse* new_object = new Synapse();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateSynapses(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(synapse_pool - int(synapse_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_synapse_list;
    new_synapse_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateSynapse(event_time);
            if(new_object != nullptr)
                {
                synapse_list.push_back(new_object);
                new_synapse_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_synapse_list;
}


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneSynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneSynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroySynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroySynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddSynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        synapse_list.push_back(add_object);
        return synapse_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddSynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(synapse_pool - int(synapse_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddSynapse(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return synapse_list;
}


CognitiveNetwork*  CognitiveNetwork::RemoveSynapse(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveSynapses(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetSynapse(std::chrono::time_point<Clock> event_time, int selector)
{
    return synapse_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetSynapses(std::chrono::time_point<Clock> event_time)
{
    return synapse_list;
}


CognitiveNetwork*  CognitiveNetwork::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
    if(neurotransmitter_list.size() < neurotransmitter_pool)
        {
        Neurotransmitter* new_object = new Neurotransmitter();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::CreateNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
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


std::vector<CognitiveNetwork*> CognitiveNetwork::CloneNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::CloneNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<CognitiveNetwork*> CognitiveNetwork::DestroyNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::DestroyNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        neurotransmitter_list.push_back(add_object);
        return neurotransmitter_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::AddNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
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


CognitiveNetwork*  CognitiveNetwork::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> CognitiveNetwork::RemoveNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

CognitiveNetwork*  CognitiveNetwork::GetNeurotransmitter(std::chrono::time_point<Clock> event_time, int selector)
{
    return neurotransmitter_list[selector];
}

std::vector<CognitiveNetwork*> CognitiveNetwork::GetNeurotransmitters(std::chrono::time_point<Clock> event_time)
{
    return neurotransmitter_list;
}

