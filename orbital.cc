/*------------------------------------------------------------------------------*/
/* @file      orbital.cc                                                        */
/* @details   Holding object for components of a cognitive loop                 */
/* @author    Paul Isaac's                                                      */
/* @date      16.02.2017                                                        */
/* @Copyright © 2017 Paul Isaac's. All rights reserved.                         */
/*------------------------------------------------------------------------------*/

/* Code snippets used:                                                          */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com          */
/* The class defines a data point and the operations that can be carried out on */
/* it.                                                                          */
/* Using the hierarchical linking the aim is to develop the application to      */
/* relate to real-world physics. This will then ease mapping between simulation,*/
/* emulation and real-world universes.                                          */

#include "neuron.h"
#include "orbital.h"

void Orbital::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    orbital_type = object_type;
    Orbital::ResetParameters(event_time);
}

bool Orbital::ResetParameters(std::chrono::time_point<Clock> event_time)
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
    if(orbital_type < 1)
        {
        orbital_type = 1;
        }
    
    object_energy = 5.0;
    m_Tau = int(50000000000000);
    m_Position = 0.0;
    m_Phase = 0.0;
    m_InternalClock = int(0);
    m_Duration = int(0);
    switch(orbital_type)
    {
        case 0:
        {
        m_Tau = int(rand() % 50000000000000);
        break;
        }
        case 1:
        {
        m_Tau = int(70000000000000);
        break;
        }
        case 2:
        {
        m_Tau = int(50000000000000);
        break;
        }
    }
    previous_event_time = event_time;
    return true;
}

std::vector<CognitiveNetwork*> Orbital::AddToNeuronList(CognitiveNetwork* neuron_pointer)
{
    neuron_list.push_back(neuron_pointer);
    return neuron_list;
}

std::vector<CognitiveNetwork*> Orbital::AddNeuron(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> list_to_add)
{
    for (int nloop = 0; nloop < list_to_add.size(); nloop++)
        {
        AddToNeuronList(list_to_add[nloop]);
        }
    
    return neuron_list;
}

std::vector<CognitiveNetwork*> Orbital::GetNeurons(std::chrono::time_point<Clock> event_time)
{
    return neuron_list;
}

void Orbital::CalcPosition(std::chrono::time_point<Clock> event_time, double Duration)
{
    switch(orbital_type)
    {
        case 0:
        {
        m_Position = sin((TWORAD * (m_Tau / Duration)) + m_Phase);
        break;
        }
        case 1:
        {
        m_Position = cos((TWORAD * (m_Tau / Duration)) + m_Phase);
        break;
        }
        case 2:
        {
        m_Position = tan((TWORAD * (m_Tau / Duration)) + m_Phase);
        break;
        }
    }
        //std::cout << "Position: " << m_Position << std::endl;
}

void Orbital::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<CognitiveNetwork*>::iterator update_iter;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<Neuron*>(*update_iter);
                if (update_pointer != nullptr)
                	update_pointer->Update(event_time);
                break;
                }
            }
        }
}

int Orbital::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    
    if(event_time != previous_event_time)
        {
    UpdateCycle(event_time, neuron_list, 1);
    
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
        m_InternalClock += m_Duration;
        m_InternalClock = m_InternalClock % m_Tau;
            //std::cout << "Clock: " << m_InternalClock << "  Tau: " << m_Tau << std::endl;
        CalcPosition(event_time, m_InternalClock);
        }
    else
        {
        CalcPosition(event_time, m_Tau);
        }
    
        // Clock duration does not consider parallel or serial operation
    m_OldClock = event_time;
        previous_event_time = event_time;
        }
    return 0;
}
