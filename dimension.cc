/*------------------------------------------------------------------------------*/
/* @file      dimension.cc                                                      */
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

#include "dimension.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Dimension::TheTimeNow()
{
    return (Universe::TheCalculatedTimeNow(time_object_created, Universe::TheTimeNow(), scale_time));
}

void Dimension::SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { dimensionCounter = val; }
void Dimension::SetScale(std::chrono::time_point<Clock> event_time, double val) { dimension_scale = val; }
void Dimension::SetTime(std::chrono::time_point<Clock> event_time, double val) { dimension_time_counter = val; }
void Dimension::SetOffset(std::chrono::time_point<Clock> event_time, double val) { dimension_offset = val; }

void Dimension::IncScale(std::chrono::time_point<Clock> event_time, double val)
{
    dimension_scale += val;
    if (dimension_scale > 1000) { dimension_scale = 1000; }
}

void Dimension::DecScale(std::chrono::time_point<Clock> event_time, double val)
{
    dimension_scale -= val;
    if (dimension_scale < 10) { dimension_scale = 10; }
}

void Dimension::IncTime(std::chrono::time_point<Clock> event_time, double val)
{
    dimension_time_counter += val;
    if (dimension_time_counter > 1000) { dimension_time_counter = 1000; }
}

void Dimension::DecTime(std::chrono::time_point<Clock> event_time, double val)
{
    dimension_time_counter -= val;
    if (dimension_time_counter < 10) { dimension_time_counter = 10; }
}

void Dimension::IncOffset(std::chrono::time_point<Clock> event_time, double val) { dimension_offset += val; }

void Dimension::DecOffset(std::chrono::time_point<Clock> event_time, double val) { dimension_offset -= val; }

void Dimension::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
    dimension_type = object_type;
    Dimension::ResetParameters(event_time);
}

bool Dimension::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(dimension_type < 1)
        {
        dimension_type = 1;
        }

    scale_time = 1.0; // Default clock tick, normal time.
    dimension_scale = 100;
    dimension_time_counter = 100;
    dimension_offset = 0;
    temporal_adjustment_list.clear();

    switch(dimension_type)
    {
        case 0:
        {
            // Blank
        scale_time = 1.0; // Default clock tick, normal time.
        dimension_scale = 100;
        dimension_time_counter = 100;
        dimension_offset = 0;
        break;
        }
        case 1:
        {
        scale_time = 1.0; // Default clock tick, normal time.
        dimension_scale = 100;
        dimension_time_counter = 100;
        dimension_offset = 0;
        break;
        }
    }
    return true;
}

void Dimension::AddTemporalAdjustment(std::chrono::time_point<Clock> event_time, double *point_to_counter, double pool, int interval, int shape)
{
    CounterAdjustment* myCounterAdjustment = new CounterAdjustment;
    myCounterAdjustment->counter_begin = event_time;              // What time does this event occur
    myCounterAdjustment->counter_last_update = event_time;              // What time does this event occur
    myCounterAdjustment->counter_end = event_time + std::chrono::nanoseconds(interval);              // What time does this event occur
    myCounterAdjustment->point_to_counter = point_to_counter;     // Which counter to increment
    myCounterAdjustment->pool = pool;                             // Amount to adjust by
    myCounterAdjustment->interval = interval;                     // Adjust over what time period
    myCounterAdjustment->shape = shape;                           // Transfer function
                                                   //std::copy(&myCounterAdjustment, &myCounterAdjustment + 1, std::back_inserter(toAddto));
    temporal_adjustment_list.push_back(myCounterAdjustment);
}

void Dimension::AdjustCounters(std::chrono::time_point<Clock> event_time)
{
    int time_difference;
    int time_elapsed;
    double increment_counter_by;
    
    for(std::vector<CounterAdjustment*>::iterator it = temporal_adjustment_list.begin(); it != temporal_adjustment_list.end(); ++it)
        {
            // Calculate time duration from counter begin to event time
        time_elapsed = int(std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - (*it)->counter_begin).count());
            // Calculate time duration from last update to event time
        time_difference = int(std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - (*it)->counter_last_update).count());
            // Reset increment count to zero
        increment_counter_by = 0.0;
            // Proceed if time is not in the past and has at least moved forward 1 nanosecond
            if (time_difference > 0)
                {
                    // Calculate the portion of time remaining for the pool to influence the counter
                time_difference = std::min(time_difference, int(std::chrono::duration_cast<std::chrono::nanoseconds>((*it)->counter_end - (*it)->counter_last_update).count()));
                    // Option to modify how the counter is incremented. Perhaps with a sigmoid function?
                switch((*it)->shape)
                    {
                        case 0:
                        {
                        increment_counter_by = (*it)->pool / ((*it)->interval / time_difference);
                        break;
                        }
                        case 1:
                        {
                        increment_counter_by = (*it)->pool / ((*it)->interval / time_difference);
                        break;
                        }
                    }
                    // Update the counter
                *(*it)->point_to_counter += increment_counter_by;
                (*it)->counter_last_update = event_time;
                }
        }
    
        // Remove time lapsed adjustments

    for (std::vector<CounterAdjustment*>::iterator it = temporal_adjustment_list.begin(); it != temporal_adjustment_list.end(); )
        {
        if( (*it)->counter_end > event_time )
            {
            delete * it;
            it = temporal_adjustment_list.erase(it);
            }
        else
            {
            ++it;
            }
        }
    
        //temporal_adjustment_list.erase( std::remove_if(temporal_adjustment_list.begin(), temporal_adjustment_list.end(), [event_time]( const CounterAdjustment& item) { return (item.counter_end <= event_time ); }), temporal_adjustment_list.end());
}

int Dimension::Update(std::chrono::time_point<Clock> event_time)
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
        }
        previous_event_time = event_time;
        }
    return 0;
}