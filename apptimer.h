/*------------------------------------------------------------------------------*/
/* @file      apptimer.h                                                        */
/* @details   Simple application timer                                          */
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

#ifndef BRAINHARMONICS_APPTIMER_H
#define BRAINHARMONICS_APPTIMER_H

#include <iostream>
#include "universe.h"

class AppTimer : public virtual Universe
{
public:
    AppTimer() : AppTimer(0) {}
    
    AppTimer(unsigned int object_type) : AppTimer(object_type, std::chrono::high_resolution_clock::now()) {}
    
    AppTimer(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    AppTimer(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitive_network type will have its own parameter ranges. The default is 0
    apptimer_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "AppTimer", apptimer_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }
    
    /** Default destructor */
    virtual ~AppTimer() {}
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return apptimer_counter; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { apptimer_counter = val; }
    
protected:
private:
    unsigned int apptimer_counter; //!< Member variable "m_Counter"
    int apptimer_type;
    bool object_disabled;
    std::chrono::time_point<Clock> time_object_created;
};

#endif // BRAINHARMONICS_APPTIMER_H
