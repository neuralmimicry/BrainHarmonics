/*------------------------------------------------------------------------------*/
/* @file      spike.h                                                         */
/* @details   Pulse generator to simulate biological neuron spikes              */
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

#ifndef BRAINHARMONICS_SPIKE_H
#define BRAINHARMONICS_SPIKE_H

#include <stdio.h>
#include <vector>
#include "cognitivenetwork.h"

class Spike : public CognitiveNetwork
{
public:
    Spike() : Spike(0) {}
    
    Spike(unsigned int object_type) : Spike(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Spike(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    Spike(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each spike type will have its own parameter ranges. The default is 0
    spike_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Spike", spike_type);
    object_disabled = true;
    }

    virtual ~Spike()
    {
    
    }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    double GetSpikeHeightReset(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_spikeHeightReset; }
    void SetSpikeHeightReset(std::chrono::time_point<Clock> event_time, double val) { m_spikeHeightReset = val; }
    void spikeReset(std::chrono::time_point<Clock> event_time) { m_spikeHeight = m_spikeHeightReset; }
    
    double pollSpike(std::chrono::time_point<Clock> event_time)
    {
    m_spikeLoop++;
    if(m_spikeLoop > 100)
        {
        m_spikeLoop = 0;
        spikeReset(event_time);
        }
    
        m_spikeHeight = ((((m_attackPeak - m_attackBegin) / m_attackLength)) * m_spikeLoop) * (m_spikeLoop < m_attackLength);
        if(m_spikeLoop > m_attackLength && m_spikeLoop < (m_attackLength + m_sustainLength)) m_spikeHeight =((m_attackPeak - m_sustain) / m_sustainLength);
        if(m_spikeLoop > ( m_attackLength + m_sustainLength ) && m_spikeLoop < (m_attackLength + m_sustainLength + m_refactoryLength)) m_spikeHeight = ((m_sustain - m_refactoryBegin) / m_sustainLength);
    
    return m_spikeHeight;
    }
    
    int Update(std::chrono::time_point<Clock> event_time);

protected:
    
private:
    double m_attackBegin = 10;
    double m_attackLength = 10;
    double m_attackPeak = 80;
    double m_sustain = 75;
    double m_sustainLength = 1;
    double m_refactoryBegin = 10;
    double m_refactoryLength = 20;
    double m_refactoryEnd =8;
    double m_spikeHeight = 0;
    double m_spikeHeightReset = 0;
    double m_spikeLoop = 0;
    double object_energy;
    int spike_type;
    bool object_disabled = true;
    bool object_initialised = false;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
};

#endif // BRAINHARMONICS_SPIKE_H
