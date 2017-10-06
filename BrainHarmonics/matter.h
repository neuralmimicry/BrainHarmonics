/*------------------------------------------------------------------------------*/
/* @file      matter.h                                                          */
/* @details   The conventional elements of the periodic table                   */
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

#ifndef BRAINHARMONICS_MATTER_H
#define BRAINHARMONICS_MATTER_H

#include <iostream>
#include <vector>
#include "universe.h"

class Matter : public Universe
{
    friend class CompositeForceParticle;
public:
    Matter() : Matter(0) {}
    
    Matter(unsigned int object_type) : Matter(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Matter(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Matter(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitive_network type will have its own parameter ranges. The default is 0
    matter_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Matter", matter_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }
    
    
    /** Default destructor */
    virtual ~Matter() {}
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return matter_counter; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { matter_counter = val; }
    
    int Update(std::chrono::time_point<Clock> event_time);

protected:
private:
    unsigned int matter_counter; //!< Member variable "matter_counter"
    int matter_type;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    bool object_initialised;
    bool object_disabled;
};


#endif // BRAINHARMONICS_MATTER_H
