//
//  schwanncell.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_SCHWANNCELL_H
#define BRAINHARMONICS_SCHWANNCELL_H

#include <iostream>
#include <vector>
#include "interneuronspace.h"

class SchwannCell : public InterneuronSpace
{
    SchwannCell() : SchwannCell(0) {}
    
    SchwannCell(unsigned int object_type) : SchwannCell(object_type, std::chrono::high_resolution_clock::now()) {}
    
    SchwannCell(unsigned int object_type, std::chrono::time_point<Clock> event_time) : InterneuronSpace() {}
    
    SchwannCell(unsigned int object_type, std::chrono::time_point<Clock> event_time, InterneuronSpace& interneuronspace_connector) : InterneuronSpace(interneuronspace_connector)
    {
        // Each schwanncell type will have its own parameter ranges. The default is 0
    schwanncell_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "SchwannCell", schwanncell_type);
    object_disabled = true;
    }
    virtual ~SchwannCell() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    /** Set m_Counter
     * \param val New value to Set
     */
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }

    int Update(std::chrono::time_point<Clock> event_time);

protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    int schwanncell_type;
    bool object_disabled = true;
    bool object_initialised = false;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
};

#endif // BRAINHARMONICS_SCHWANNCELL_H
