    //
    //  soma.hpp
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef soma_hpp
#define soma_hpp

#include <chrono>
#include <iostream>
#include <vector>
#include "axonhillock.hpp"
#include "dendrite.hpp"
typedef std::chrono::high_resolution_clock Clock;

class soma
{
public:
    /** Default constructor */
    soma()
    {
    soma(std::chrono::high_resolution_clock::now(), 0);
    }
    
    soma(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, int val)
    {
    m_NeuronType = val;
    resetParameters(eventTime);
        // If every soma has an axonhillock, build an axonhillock for this soma
    m_addStatus = add_Axonhillock(eventTime);
    if(m_addStatus==0)
        {
        std::cout << "Axonhillock energy: " << m_AxonhillockList[0].GetEnergy() << std::endl;
        }
        // If every soma has a dendrite, build a couple of dendrites for this soma
    m_addStatus = add_Dendrite(eventTime);
    if(m_addStatus==0)
        {
        std::cout << "Dendrite(0) energy: " << m_DendriteList[0].GetEnergy() << std::endl;
        }
    m_addStatus = add_Dendrite(eventTime);
    if(m_addStatus==0)
        {
        std::cout << "Dendrite(1) energy: " << m_DendriteList[1].GetEnergy() << std::endl;
        }
    };
    /** Default destructor */
    virtual ~soma() {};
    
        // Unit of time resolution is 1ns.
        // Any single network function should have an output within 25ms
        // For simulation a 25ms function should complete in 25 seconds. A factor of 1000 dilation.
    double TimeFunction(double timeDelay, double timeDilation)
    {
    double timeCounter;
    timeCounter = timeDelay * timeDilation;
    return timeCounter;
    }
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    double GetEnergyInc() { return m_EnergyInc; }
    double GetEnergyDec() { return m_EnergyDec; }
    double GetEnergyLeak() { return m_EnergyLeak; }
    double GetEnergyThreshold() { return m_EnergyThreshold; }
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
    void SetEnergyInc(double val) { m_EnergyInc = val; }
    void SetEnergyDec(double val) { m_EnergyDec = val; }
    void SetEnergyLeak(double val) { m_EnergyLeak = val; }
    void SetEnergyThreshold(double val) { m_EnergyThreshold = val; }
    void Creation() {std::cout << "Soma created." << std::endl; }
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Energy = 0;
    AddEnergy(eventTime, 100);
    m_EnergyInc = 100;
    m_EnergyDec = 100;
    m_EnergyLeak = 1;
    m_EnergyThreshold = 1000;
    m_Size = 10;
    m_TimeDilation = 1;
    m_TimeThreshold = 1000;
    switch(m_NeuronType)
        {
            case 0:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            break;
            }
            case 1:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            break;
            }
            case 2:
            {
            m_Volume = 100;
            m_SurfaceArea = 100;
            break;
            }
        }
    
    }
    
    /*
     int add_Axonhillock (std::vector<axonhillock> *toAddto)
     {
     axonhillock myAxonhillock;
     std::copy(&myAxonhillock, &myAxonhillock + 1, std::back_inserter(*toAddto));
     return 0;
     }
     
     int add_Dendrite (std::vector<dendrite> *toAddto)
     {
     dendrite myDendrite;
     std::copy(&myDendrite, &myDendrite + 1, std::back_inserter(*toAddto));
     return 0;
     }
     */
    
    int add_Axonhillock(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_AxonhillockList.push_back(axonhillock(eventTime, m_NeuronType));
    return 0;
    }
    
    int add_Dendrite(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_DendriteList.push_back(dendrite(eventTime, m_NeuronType));
    return 0;
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

    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    adjust_Counters(eventTime);
            for(std::vector<axonhillock>::iterator it = m_AxonhillockList.begin(); it != m_AxonhillockList.end(); ++it)
                {
                it->Update(eventTime);
                }
            for(std::vector<dendrite>::iterator it = m_DendriteList.begin(); it != m_DendriteList.end(); ++it)
                {
                it->Update(eventTime);
                }
    
    if (m_Energy < m_EnergyThreshold)
        {
        for(std::vector<dendrite>::iterator it = m_DendriteList.begin(); it != m_DendriteList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, it->GrabEnergy(eventTime), 100, 1);
            }
        }
        // For forward propagation of energy to Axonhillock
    if (m_Energy >= m_EnergyThreshold)
        {
        std::cout << "Soma threshold crossed." << std::endl;
        for(std::vector<axonhillock>::iterator it = m_AxonhillockList.begin(); it != m_AxonhillockList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-m_EnergyThreshold)/m_AxonhillockList.size(), 100, 1);   // redistribute energy
            it->AddEnergy(eventTime, m_EnergyThreshold/m_AxonhillockList.size());
            }
            // Try back propagating to dendrites
        for(std::vector<dendrite>::iterator it = m_DendriteList.begin(); it != m_DendriteList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-(m_Energy - m_EnergyThreshold))/m_DendriteList.size(), 100, 1);   // redistribute energy
            it->AddEnergy(eventTime, (m_EnergyThreshold - m_EnergyThreshold)/m_DendriteList.size());
            }
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
    double m_Size;
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
    std::vector<axonhillock> m_AxonhillockList;
    std::vector<dendrite> m_DendriteList;
};

#endif /* soma_hpp */
