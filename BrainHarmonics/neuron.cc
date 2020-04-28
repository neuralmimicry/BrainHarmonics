/*------------------------------------------------------------------------------*/
/* @file      neuron.cc                                                         */
/* @details   Holding object for components of a neuron                         */
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

#include "neuron.h"
#include "membrane.h"
#include "soma.h"

void Neuron::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    neuron_type = object_type;
    Neuron::ResetParameters(event_time);
}

bool Neuron::ResetParameters(std::chrono::time_point<Clock> event_time)
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
    if(neuron_type < 1)
        {
        neuron_type = 1;
        }

    soma_pool = 1;
    membrane_pool = 1;
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
    neuronCapacity = 0;                   // Set initial type value
    
    switch(neuron_type)
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
    //    void addConnection(std::vector<neuron*> val) { m_ConnectionList.push_back(&val); }

bool Neuron::OpenGate(std::chrono::time_point<Clock> event_time, double val)
{
    if((val >= m_ChannelMin && val <= m_ChannelMax) or object_energy > 0.1)
        {
        if((val >= m_ChannelMin && val <= m_ChannelMax))
            {
            object_energy = object_energy + m_Spike;
            return true;
            }
        }
    else
        {
        object_energy = object_energy * 0.99;
        }
    return false;
}

Neuron*  Neuron::CreateSoma(std::chrono::time_point<Clock> event_time)
{
    if(soma_list.size() < soma_pool)
        {
        Soma* new_object = new Soma();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Neuron*> Neuron::CreateSomas(std::chrono::time_point<Clock> event_time, int quantity)
{
        //std::cout << "To create: " << quantity;
        //std::cout << " from pool: " << soma_pool;
        //std::cout << " with already: " << int(soma_list.size());
    quantity = std::min(int(soma_pool - int(soma_list.size())), int(quantity));
        //std::cout << " Allowed: " << quantity;
    std::vector<Neuron*> new_soma_list;
    new_soma_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Neuron* new_object = CreateSoma(event_time);
            if(new_object != nullptr)
                {
                soma_list.push_back(new_object);
                new_soma_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_soma_list;
}


std::vector<Neuron*> Neuron::CloneSomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Neuron*  Neuron::CloneSoma(std::chrono::time_point<Clock> event_time, Neuron* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Neuron*> Neuron::DestroySomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> destruction_list)
{
        // Function TBD
}

Neuron*  Neuron::DestroySoma(std::chrono::time_point<Clock> event_time, Neuron* destroy_object)
{
        // Function TBD
}

Neuron*  Neuron::AddSoma(std::chrono::time_point<Clock> event_time, Neuron* add_object)
{
    if(add_object != nullptr)
        {
        soma_list.push_back(add_object);
        return soma_list.back();
        }
    else
        return nullptr;
}

std::vector<Neuron*> Neuron::AddSomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(soma_pool - int(soma_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Neuron* result = AddSoma(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return soma_list;
}


Neuron*  Neuron::RemoveSoma(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Neuron*> Neuron::RemoveSomas(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Neuron*  Neuron::GetSoma(std::chrono::time_point<Clock> event_time, int selector)
{
    return soma_list[selector];
}

std::vector<Neuron*> Neuron::GetSomas(std::chrono::time_point<Clock> event_time)
{
    return soma_list;
}


Neuron*  Neuron::CreateMembrane(std::chrono::time_point<Clock> event_time)
{
    if(membrane_list.size() < membrane_pool)
        {
        Membrane* new_object = new Membrane();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<Neuron*> Neuron::CreateMembranes(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(int(membrane_pool - int(membrane_list.size())), int(quantity));
    std::vector<Neuron*> new_membrane_list;
    new_membrane_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            Neuron* new_object = CreateMembrane(event_time);
            if(new_object != nullptr)
                {
                membrane_list.push_back(new_object);
                new_membrane_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_membrane_list;
}


std::vector<Neuron*> Neuron::CloneMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> cloning_list, double perfection_membership)
{
        // Function TBD
}

Neuron*  Neuron::CloneMembrane(std::chrono::time_point<Clock> event_time, Neuron* clone_object, double perfection_membership)
{
        // Function TBD
}

std::vector<Neuron*> Neuron::DestroyMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> destruction_list)
{
        // Function TBD
}

Neuron*  Neuron::DestroyMembrane(std::chrono::time_point<Clock> event_time, Neuron* destroy_object)
{
        // Function TBD
}

Neuron*  Neuron::AddMembrane(std::chrono::time_point<Clock> event_time, Neuron* add_object)
{
    if(add_object != nullptr)
        {
        membrane_list.push_back(add_object);
        return membrane_list.back();
        }
    else
        return nullptr;
}

std::vector<Neuron*> Neuron::AddMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(membrane_pool - int(membrane_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                Neuron* result = AddMembrane(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return membrane_list;
}


Neuron*  Neuron::RemoveMembrane(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<Neuron*> Neuron::RemoveMembranes(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
}

Neuron*  Neuron::GetMembrane(std::chrono::time_point<Clock> event_time, int selector)
{
    return membrane_list[selector];
}

std::vector<Neuron*> Neuron::GetMembranes(std::chrono::time_point<Clock> event_time)
{
    return membrane_list;
}


int Neuron::Growth(std::chrono::time_point<Clock> event_time)
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

void Neuron::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> set_of_update_pointers, unsigned int pointer_type)
{
        //    std::vector<Neuron*>::iterator update_iter;
    for(Neuron* update_iter : set_of_update_pointers)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<Soma*>(update_iter);
		if(update_pointer != nullptr)
                    update_pointer->Update(event_time);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<Membrane*>(update_iter);
		if(update_pointer != nullptr)
                    update_pointer->Update(event_time);
                break;
                }
            }
        }
}

void Neuron::UpdateCycle2(std::chrono::time_point<Clock> event_time, std::vector<Universe*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<Universe*>::iterator update_iter;
    Universe* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<Solid*>(*update_iter);
                break;
                }
            }
	if(update_pointer != nullptr)
            update_pointer->Update(event_time);
        }
}

int Neuron::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    std::cout << "N";
    if(!object_initialised)
        {
            //std::cout << "Initialising neuron..." << std::endl;
        object_initialised = ResetParameters(event_time);
        
        auto visualisation_pointer = dynamic_cast<Solid*>(AddSolid(event_time));
        visualisation_pointer->SetObjectType(event_time, TYPE_SOLID_NEURON_GEN1);
        visualisation_list.push_back(visualisation_pointer);
        
        auto soma_pointer = dynamic_cast<Soma*>(CreateSomas(event_time, 1)[0]);
        soma_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_SOMA_GEN1);
        soma_list.push_back(soma_pointer);
        
        auto membrane_pointer = dynamic_cast<Membrane*>(CreateMembranes(event_time, 1)[0]);
        membrane_pointer->SetObjectType(event_time, TYPE_NEURON_PYRAMIDAL_MEMBRANE_GEN1);
        membrane_list.push_back(membrane_pointer);
        }

    if(event_time != previous_event_time)
        {
    UpdateCycle(event_time, soma_list, 1);
    UpdateCycle(event_time, membrane_list, 2);
    UpdateCycle2(event_time, visualisation_list, 1);
    
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
    
    for(std::vector<Neuron*>::iterator it = soma_list.begin(); it != soma_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
        Growth(event_time);
        object_energy_threshold = object_size * 1000;
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
