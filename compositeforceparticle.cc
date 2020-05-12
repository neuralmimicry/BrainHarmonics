/*------------------------------------------------------------------------------*/
/* @file      compositeforce.cc                                                 */
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

#include "compositeforceparticle.h"
#include "elementaryforce.h"
#include "elementaryparticle.h"

bool CompositeForceParticle::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(composite_forceparticle_type < 1)
        {
        composite_forceparticle_type = 1;
        }
    
    composite_forceparticle_counter = 0;
    composite_forceparticle_gravitation = 0;
    composite_forceparticle_weak = 0;
    composite_forceparticle_weak_electroweak = 0;
    composite_forceparticle_electromagnetic = 0;
    composite_forceparticle_electromagnetic_electroweak = 0;
    composite_forceparticle_strong = 0;
    composite_forceparticle_strong_fundamental = 0;
    composite_forceparticle_strong_residual = 0;
    return true;
}

void CompositeForceParticle::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<CompositeForceParticle*>::iterator update_iter;
    CompositeForceParticle* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<ElementaryParticle*>(*update_iter);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<ElementaryForce*>(*update_iter);
                break;
                }
            }
        update_pointer->Update(event_time);
        }
}

int CompositeForceParticle::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    
    if(event_time != previous_event_time)
        {
    UpdateCycle(event_time, elementary_particle_list, 1);
    UpdateCycle(event_time, elementary_force_list, 2);

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
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
