/*------------------------------------------------------------------------------*/
/* @file      polymer.h                                                         */
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

#ifndef BRAINHARMONICS_POLYMER_H
#define BRAINHARMONICS_POLYMER_H

#include <iostream>
#include <vector>
#include "universe.h"

class Polymer : public Universe
{
    
public:
    Polymer() : Polymer(0) {}
    
    Polymer(unsigned int object_type) : Polymer(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Polymer(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Polymer(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each polymer type will have its own parameter ranges. The default is 0
    polymer_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Polymer", polymer_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Polymer() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return polymer_counter; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { polymer_counter = val; }

    void SetPolymerLabel (std::string val) { m_polymerLabel = val; }

    std::string GetPolymerLabel() { return m_polymerLabel; }

    int Update(std::chrono::time_point<Clock> event_time);

    
protected:
private:
    unsigned int polymer_counter; //!< Member variable "polymer_counter"
    std::string m_polymerLabel; //!< Member variable "m_polymerLabel"
    int polymer_type;
    bool object_disabled = true;
    bool object_initialised = false;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
};


#endif // BRAINHARMONICS_POLYMER_H
