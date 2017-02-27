//
//  neuroreceptor.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//
// The Energy level used in this function only enables the receptor to activate.
// It does not necessarily mean that a spike will flow through. It depends what
// is waiting in the void beyond the membrane.
//
// Metabotropic Receptors and Ionotropic Receptor are possibilities
// The type of receptor can be defined by polymer connection or stated
// as an integer type.
//
// Metabotropic
// 1: Receptive to GABA neurotransmitters
// 2:
// Ionotropic
// 3: Cys-loop
// 4: Glutamate receptor
// 5: ATP-gated

    // Type-3 Serotonin receptor (5HT3-R)

#ifndef neuroreceptor_h
#define neuroreceptor_h

#include <iostream>
#include <chrono>
#include "neurotransmitter.hpp"
#include "polymer.h"
typedef std::chrono::high_resolution_clock Clock;

class Neuroreceptor : public Polymer
{
public:
    /** Default constructor */
    Neuroreceptor(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, const Polymer& p) : Polymer(p)
    {
        resetParameters(eventTime);
    };
    /** Default destructor */
    virtual ~Neuroreceptor() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    bool getReceptorBindingState() { return m_boundReceptor; }
    int getReceptorType() { return m_typeReceptor; }
    bool getDisabled() { return m_Disabled; }
    int getIons() { return m_Ions; }
    
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
    void setReceptorBindingState(bool val) { m_boundReceptor = val; if (m_boundReceptor) { m_Energy = m_EnergyFull; } }
    void toggleReceptorBindingState() { m_boundReceptor = !m_boundReceptor; }
    void toggleDisabled() { m_Disabled = !m_Disabled; setReceptorBindingState(false); }
    void setDisabled(bool val) { m_Disabled = val; setReceptorBindingState(false); }
    void setReceptorType(int val) { m_typeReceptor = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void SetIons(int val) { m_Ions = val; }
    void Creation() {std::cout << "Neuroreceptor created." << std::endl; }
    
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_EnergyFull = 100;
    m_Energy = 0;
    m_Ions = 0;
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    m_EnergyThreshold = 100;
    switch(m_NeuronType)
        {
            case 0:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            m_Length = 100;
            break;
            }
            case 1:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            m_Length = 100;
            break;
            }
            case 2:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            m_Length = 100;
            break;
            }
        }
    m_oldClock = Clock::now();
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
    if (m_Energy > 0)
        {
        if (getReceptorBindingState())
            {
            }
        if (m_duration > 1000)
            {
            m_Energy -= 1;
            }
        if (m_Energy <= 0)
            {
            m_Energy = 0;
            m_Ions = 0;
            setReceptorBindingState(false);
            }
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
    int m_addStatus;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    double m_Volume;
    double m_SurfaceArea;
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
    double m_Length;
    bool m_Disabled;
    double m_EnergyFull;
    int m_Ions;
    bool m_boundReceptor; //!< Member variable "m_boundReceptor"
    int m_typeReceptor; //!< Member variable "m_typeReceptor"
    std::vector<Neurotransmitter> m_NeurotransmitterList;
};

#endif /* neuroreceptor_h */
