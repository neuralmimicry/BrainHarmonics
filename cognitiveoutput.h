//
//  cognitiveoutput.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_COGNITIVEOUTPUT_H
#define BRAINHARMONICS_COGNITIVEOUTPUT_H

//#include <algorithm>
#include <chrono>
#include <iostream>
#include "cognitivenetwork.h"

class CognitiveOutput : public CognitiveNetwork
{
public:
    CognitiveOutput() : CognitiveOutput(0) {}
    
    CognitiveOutput(unsigned int object_type) : CognitiveOutput(object_type, std::chrono::high_resolution_clock::now()) {}
    
    CognitiveOutput(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    CognitiveOutput(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each cognitiveoutput type will have its own parameter ranges. The default is 0
    cognitiveoutput_type = object_type;
        // Each new object has its default parameters set here.
    object_initialised = ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "CognitiveOutput", cognitiveoutput_type);
    }
    
    /** Default destructor */
    virtual ~CognitiveOutput() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    int GetType() { return cognitiveoutput_type; }

    void SetType(int val) { cognitiveoutput_type = val; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }

    double TakeEnergy(std::chrono::time_point<Clock> event_time)
    {
    // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - object_energy, 1000, 1);
    return object_energy;
    }

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
private:
    int m_CognitiveOutputType;
    int cognitiveoutput_type = 0;
    int m_addStatus;
    std::chrono::time_point<Clock> time_object_created = std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero());
    std::chrono::time_point<Clock> previous_event_time;
    bool object_disabled = true;
    bool object_initialised = false;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    double object_size;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double m_TimeDilation;
    double m_TimeThreshold;
    
};

#endif // BRAINHARMONICS_COGNITIVEOUTPUT_H
