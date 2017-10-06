//
//  neurotransmitter.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_NEUROTRANSMITTER_H
#define BRAINHARMONICS_NEUROTRANSMITTER_H

//#include <algorithm>
#include <chrono>
#include <iostream>
#include "cognitivenetwork.h"

class Neurotransmitter : public CognitiveNetwork
{
public:
    Neurotransmitter() : Neurotransmitter(0) {}
    
    Neurotransmitter(unsigned int object_type) : Neurotransmitter(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Neurotransmitter(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    Neurotransmitter(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each neurotransmitter type will have its own parameter ranges. The default is 0
    neurotransmitter_type = object_type;
        // Each new object has its default parameters set here.
    object_initialised = ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Neurotransmitter", neurotransmitter_type);
    }
    
    /** Default destructor */
    virtual ~Neurotransmitter() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    int GetType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return neurotransmitter_type; }

    void SetType(std::chrono::time_point<Clock> event_time, int val) { neurotransmitter_type = val; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
private:
    int m_NeurotransmitterType;
    int neurotransmitter_type = 0;
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

#endif // BRAINHARMONICS_NEUROTRANSMITTER_H
