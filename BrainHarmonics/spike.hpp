/*------------------------------------------------------------------------------*/
/* @file      spike.hpp                                                         */
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

#ifndef spike_hpp
#define spike_hpp

#include <stdio.h>

class Spike
{
public:
    Spike()
    {
    
    };
    virtual ~Spike()
    {
    
    };
    
    double getSpikeHeightReset() { return m_spikeHeightReset; }
    double setSpikeHeightReset(double val) { m_spikeHeightReset = val; }
    void spikeReset() { m_spikeHeight = m_spikeHeightReset; }
    
    double pollSpike()
    {
    m_spikeLoop++;
    if(m_spikeLoop > 100)
        {
        m_spikeLoop = 0;
        spikeReset();
        }
    
        m_spikeHeight = ((((m_attackPeak - m_attackBegin) / m_attackLength)) * m_spikeLoop) * (m_spikeLoop < m_attackLength);
        if(m_spikeLoop > m_attackLength && m_spikeLoop < (m_attackLength + m_sustainLength)) m_spikeHeight =((m_attackPeak - m_sustain) / m_sustainLength);
        if(m_spikeLoop > ( m_attackLength + m_sustainLength ) && m_spikeLoop < (m_attackLength + m_sustainLength + m_refactoryLength)) m_spikeHeight = ((m_sustain - m_refactoryBegin) / m_sustainLength);
    
    return m_spikeHeight;
    }
    
    void creation()
    {
    
    }
    
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
};
#endif /* spike_hpp */
