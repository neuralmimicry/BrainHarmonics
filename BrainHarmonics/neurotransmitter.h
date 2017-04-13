//
//  neurotransmitter.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef neurotransmitter_hpp
#define neurotransmitter_hpp

//#include <algorithm>
#include <chrono>
#include <iostream>
#include "polymer.h"
typedef std::chrono::high_resolution_clock Clock;

class Neurotransmitter : public Polymer
{
public:
    /** Default constructor */
    Neurotransmitter()
    {
    Neurotransmitter(std::chrono::high_resolution_clock::now(), *new Polymer());
    }
    
    Neurotransmitter(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    Neurotransmitter(eventTime, *new Polymer());
    }
    
    Neurotransmitter(const Polymer& p) : Polymer(p)
    {
    Neurotransmitter(std::chrono::high_resolution_clock::now(), p);
    }
    
    Neurotransmitter(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, const Polymer& p) : Polymer(p)
    {
    resetParameters(eventTime);
    }
    
    /** Default destructor */
    virtual ~Neurotransmitter() {};
    void AddEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, double val)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, val, 100, 0);     // Add energy
    add_TemporalAdjustment(eventTime, &m_Energy, -val, 1000, 1);   // Decay energy
    }
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    int GetType() { return m_TransmitterType; }

    void SetType(int val) { m_TransmitterType = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Neurotransmitter created." << std::endl; }
    
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Counter = 0;
    AddEnergy(eventTime, 100);
    m_EnergyThreshold = 2000;
    m_Size = 1;
    m_TransmitterType = 0;
    switch(m_NeuronType)
        {
            case 0:
            {
            m_Size = 3;
            break;
            }
            case 1:
            {
            m_Size = 2;
            break;
            }
            case 2:
            {
            m_Size = 1;
            break;
            }
        }
    
    }

    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    adjust_Counters(eventTime);
    
    if (m_Energy > 0)
        {
            {
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
    /*
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
     */
        // Remove empty pools of adjustments
        //    m_TemporalAdjustment.erase(std::remove(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), [&](s_CounterAdjustment const & counter) { return counter.s_Pool == 0; }), m_TemporalAdjustment.end());
        // Remove adjusters when energy depleted
        //    m_TemporalAdjustment.erase(std::remove(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), [&](s_CounterAdjustment const & counter) { return *counter.s_PointToCounter == 0; }), m_TemporalAdjustment.end());
    }
    
    
protected:
private:
    int m_NeuronType;
    int m_TransmitterType;
    int m_addStatus;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    double m_Volume;
    double m_SurfaceArea;
    double m_Size;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_EnergyThreshold;
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
};

#endif /* neurotransmitter_hpp */
