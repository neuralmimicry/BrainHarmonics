/*------------------------------------------------------------------------------*/
/* @file      monomer.cc                                                        */
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

#include "monomer.h"
#include "solid.h"

unsigned int Monomer::GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return monomer_counter; }

void Monomer::SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { monomer_counter = val; }

bool Monomer::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(monomer_type < 1)
        {
        monomer_type = 1;
        }
    
    object_energy = 10 * ((rand() % 30 + 85) / 100);
    object_energy_threshold = 2000 * ((rand() % 30 + 85) / 100);
    object_size = 1 * ((rand() % 30 + 85) / 100);

    
    switch(monomer_type)
    {
        case 0:
        {
            // Default - a non-channel
        object_size = 3 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 1:
        {
            // Sodium channel
        object_size = 2 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 2:
        {
            // Potassium channel
        object_size = 1 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 3:
        {
            // Calcium pump
        object_size = 1 * ((rand() % 30 + 85) / 100);
        break;
        }
    }
   
    return true;
}

int Monomer::AddSolid(std::chrono::time_point<Clock> event_time)
{
        //    Solid* new_object;
        //    solid_list.push_back(new_object);
    return 0;
}


int Monomer::Update(std::chrono::time_point<Clock> event_time)
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
        // Use GetPoint to enable movement across Synapse to MembraneChannel
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &GetPoint(event_time, 0)->object_energy, object_energy * 0.1, 10000, 1);
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - (object_energy * 0.1), 10000, 1);
}
        previous_event_time = event_time;
        }
    return 0;
}
