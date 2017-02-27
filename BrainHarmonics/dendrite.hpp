    //
    //  dendrite.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef dendrite_hpp
#define dendrite_hpp

#include <chrono>
#include <iostream>
#include <math.h>       /* sqrt */
#include <vector>
    //#include "dendritebranch.hpp"
#include "dendritespine.hpp"
typedef std::chrono::high_resolution_clock Clock;

class dendrite
{
public:
    /** Default constructor */
    dendrite()
    {
    dendrite(std::chrono::high_resolution_clock::now(), 0);
    }
    
    dendrite(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, int val)
    {
    m_NeuronType = val;
    resetParameters(eventTime);
    };
    /** Default destructor */
    virtual ~dendrite() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    double getDendriteLength() { return m_dendriteLength; }
    double getDendriteDiameterStart() { return m_dendriteDiameterStart; }
    double getDendriteDiameterEnd() { return m_dendriteDiameterEnd; }
    double getMembraneResistance() { return m_membraneResistance; }
    double getMembraneCapacitance() { return m_membraneCapacitance; }
    double getInternalResistance() { return m_internalResistance; }
    double getPropagationVelocity() { return ( ( 1 / m_membraneCapacitance ) * sqrt((m_dendriteLength / ( 4 * m_membraneResistance * m_internalResistance ) ) ) ); }
    
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
    void setDendriteLength(double val) { m_dendriteLength = val; }
    void setDendriteDiameterStart(double val) { m_dendriteDiameterStart = val; }
    void setDendriteDiameterEnd(double val) { m_dendriteDiameterEnd = val; }
    void setMembraneResistance(double val) { m_membraneResistance = val; }
    void setMembraneCapacitance(double val) { m_membraneCapacitance = val; }
    void setInternalResistance(double val) { m_internalResistance = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Dendrite created." << std::endl; }
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
    m_EnergyThreshold = 500;
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
    
    }
    
    int growth(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    if (m_Energy > (m_EnergyThreshold * .9))
        {
        add_TemporalAdjustment(eventTime, &m_Size, 1, 10000, 0);
        }
    if (m_Energy < (m_EnergyThreshold * .1))
        {
        add_TemporalAdjustment(eventTime, &m_Size, -1, 10000, 0);
        }
    if (m_Size < 1)
        {
        m_Size = 1;
        }
    if (m_Size > 50)
        {
        m_Size = 50;
        }
    return 0;
    }
    
    int add_DendriteSpine(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_DendriteSpineList.push_back(dendritespine(eventTime, m_NeuronType));
    return 0;
    }
    
    int add_DendriteBranch(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
        //    m_DendriteBranchList.push_back(dendritebranch(eventTime, m_NeuronType));
    return 0;
    }
    
    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    adjust_Counters(eventTime);
#pragma omp parallel
        {
#pragma omp single nowait
            {
                //            for(std::vector<dendritebranch>::iterator it = m_DendriteBranchList.begin(); it != m_DendriteBranchList.end(); ++it)
                {
#pragma omp task
                    //                it->Update(eventTime);
                }
            }
#pragma omp single nowait
            {
            for(std::vector<dendritespine>::iterator it = m_DendriteSpineList.begin(); it != m_DendriteSpineList.end(); ++it)
                {
#pragma omp task
                it->Update(eventTime);
                }
            }
        }
    
    if (m_Energy < m_EnergyThreshold)
        {
        for(std::vector<dendritespine>::iterator it = m_DendriteSpineList.begin(); it != m_DendriteSpineList.end(); ++it)
            {
                add_TemporalAdjustment(eventTime, &m_Energy, it->GrabEnergy(eventTime), 100, 1);   // absorb energy
            }
            //        for(std::vector<dendritebranch>::iterator it = m_DendriteBranchList.begin(); it != m_DendriteBranchList.end(); ++it) {
            //            add_TemporalAdjustment(eventTime, &m_Energy, it->GrabEnergy(eventTime), 100, 1);   // absorb energy
        }
    
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(eventTime - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_duration > 1000)
        {
        growth(eventTime);
        m_EnergyThreshold = m_Size * 1000;
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
    double m_Length;
    double m_Size;
    double m_dendriteLength;  //!< Member variable "m_dendriteLength"
    double m_dendriteDiameterStart;  //!< Member variable "m_dendriteDiameterStart"
    double m_dendriteDiameterEnd;  //!< Member variable "m_dendriteDiameterEnd"
    double m_membraneResistance;
    double m_membraneCapacitance;
    double m_internalResistance;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_EnergyInc;
    double m_EnergyDec;
    double m_EnergyLeak;
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
        //    std::vector<dendritebranch> m_DendriteBranchList;
    std::vector<dendritespine> m_DendriteSpineList;
    
};

#endif /* dendrite_hpp */
