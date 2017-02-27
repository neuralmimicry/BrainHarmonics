//
//  synapse.hpp
//  BrainHarmonics
//
//**  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef synapse_hpp
#define synapse_hpp

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include "neurotransmitter.hpp"
#include "neuroreceptor.hpp"
typedef std::chrono::high_resolution_clock Clock;

class synapse
{
public:
    /** Default constructor */
    synapse() {};
    /** Default destructor */
    virtual ~synapse() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    void AddEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, double val)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, val, 100, 0);     // Add energy
    add_TemporalAdjustment(eventTime, &m_Energy, -val, 1000, 1);   // Decay energy
    }
    double GrabEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, -m_Energy, 100, 1);     // Grab energy
    return m_Energy;
    }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Synapse created." << std::endl; }
    void resetParameters()
    {
    m_Energy = 0;
    
    }

    void SendBareSpike()
    {
    m_Energy += 1000;
    }
    
    int create_Neurotransmitter()
    {
    Neurotransmitter myNeurotransmitter;
    m_NeurotransmitterList.push_back(myNeurotransmitter);
    return 0;
    }
    
    int add_Neurotransmitter(Neurotransmitter *val)
    {
    m_NeurotransmitterList.push_back(*val);
    return 0;
    }

    int remove_Neurotransmitter(Neurotransmitter *val)
    {
    m_NeurotransmitterList.erase(std::remove(m_NeurotransmitterList.begin(), m_NeurotransmitterList.end(), *val), m_NeurotransmitterList.end());
    return 0;
    }
    
    void SendTransmitterSpike()
    {
    for (int nloop = 0; nloop < 100; nloop++)
        {
            create_Neurotransmitter();
        }
    SendBareSpike();
    }
    
    int add_Neuroreceptor(Neuroreceptor *val)
    {
    m_NeuroreceptorList.push_back(*val);
    return 0;
    }
    
    int remove_Neuroreceptor(Neuroreceptor *val)
    {
    m_NeuroreceptorList.erase(std::remove(m_NeuroreceptorList.begin(), m_NeuroreceptorList.end(), *val), m_NeuroreceptorList.end());
    return 0;
    }
    
    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    adjust_Counters(eventTime);
    
#pragma omp parallel
        {
#pragma omp single nowait
            {
            for(std::vector<Neurotransmitter>::iterator it = m_NeurotransmitterList.begin(); it != m_NeurotransmitterList.end(); ++it)
                {
#pragma omp task
                it->Update(eventTime);
                }
            }
        }
    
    if (m_Energy > 0)
        {
        for(std::vector<Neurotransmitter>::iterator it = m_NeurotransmitterList.begin(); it != m_NeurotransmitterList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-m_Energy)/m_NeurotransmitterList.size(), 100, 1);   // redistribute energy
            it->AddEnergy(eventTime, m_Energy/m_NeurotransmitterList.size());
            }
        }
    
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(eventTime - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_duration > 1000)
        {
        
        }
        // Clock duration does not consider parallel or serial operation
    m_oldClock = eventTime;
    return 0;
    }
    
    void add_TemporalAdjustment(std::chrono::time_point<std::chrono::high_resolution_clock> cb, double* ptc, double p, int i, int s)
    {
    s_CounterAdjustment myCounterAdjustment;
    myCounterAdjustment.s_CounterBegin = cb;        // What time does this event occur
    myCounterAdjustment.s_PointToCounter = ptc;     // Which counter to increment
    myCounterAdjustment.s_Pool = p;                 // Amount to adjust by
    myCounterAdjustment.s_Interval = i;             // Adjust over what time period
    myCounterAdjustment.s_Shape = s;                // Transfer function
    m_TemporalAdjustment.push_back(myCounterAdjustment);
    }
    
    void adjust_Counters(std::chrono::time_point<std::chrono::high_resolution_clock> currentTime)
    {
    int timeDifference;
    double incrementBy;
    for(std::vector<s_CounterAdjustment>::iterator it = m_TemporalAdjustment.begin(); it != m_TemporalAdjustment.end(); ++it)
        {
        timeDifference = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - it->s_CounterBegin).count();
        if (timeDifference > 0)
            {
            incrementBy = 1;
            switch(it->s_Shape)
                {
                    case 0:
                    {
                    incrementBy = it->s_Pool / (it->s_Interval / timeDifference);
                    break;
                    }
                    case 1:
                    {
                    incrementBy = it->s_Pool / (it->s_Interval / timeDifference);
                    break;
                    }
                }
            it->s_Pool -= incrementBy;
            if (it->s_Pool < 0 && incrementBy > 0)
                {
                incrementBy += it->s_Pool;
                }
            if (it->s_Pool > 0 && incrementBy < 0)
                {
                incrementBy -= it->s_Pool;
                }
            *it->s_PointToCounter += incrementBy;
                // Increment in nanoseconds?? Is this the right scale factor
            it->s_CounterBegin += std::chrono::nanoseconds(it->s_Interval);
            }
        else
            {
            it->s_Pool = 0;
            }
        
        }
        // Remove empty pools of adjustments
        //    m_TemporalAdjustment.erase(std::remove(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), [&](s_CounterAdjustment const & counter) { return counter.s_Pool == 0; }), m_TemporalAdjustment.end());
        // Remove adjusters when energy depleted
        //    m_TemporalAdjustment.erase(std::remove(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), [&](s_CounterAdjustment const & counter) { return *counter.s_PointToCounter == 0; }), m_TemporalAdjustment.end());
    }
    
    
protected:
private:
    int m_NeuronType;
    int m_addStatus;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_axonlength;
    double m_TimeDilation;
    double m_TimeThreshold;
    struct s_CounterAdjustment
    {
    s_CounterAdjustment() : s_CounterBegin(std::chrono::high_resolution_clock::now()), s_PointToCounter(0), s_Pool(0), s_Interval(0), s_Shape(0) {}
    std::chrono::time_point<std::chrono::high_resolution_clock> s_CounterBegin;
    double* s_PointToCounter;
    double s_Pool;
    int s_Interval;
    int s_Shape;
    };
    
    std::vector<s_CounterAdjustment> m_TemporalAdjustment;
    double m_ReduceBy;
    double m_ReducedBy;
    std::vector<Neurotransmitter> m_NeurotransmitterList;
    std::vector<Neuroreceptor> m_NeuroreceptorList;
};

#endif /* synapse_hpp */
