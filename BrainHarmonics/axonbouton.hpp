//
//  axonbouton.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef axonbouton_hpp
#define axonbouton_hpp

#include <chrono>
#include <iostream>
#include "polymer.h"
#include "synapse.hpp"
#include "synapticvesicle.hpp"
typedef std::chrono::high_resolution_clock Clock;

class axonbouton : Polymer
{
public:
    /** Default constructor */
    axonbouton()
    {
    axonbouton(Clock::now(), 0);
    }
    
    axonbouton(std::chrono::time_point<Clock> eventTime)
    {
    axonbouton(eventTime, 0);
    }
    
    axonbouton(std::chrono::time_point<Clock> eventTime, int val)
    {
    axonbouton(eventTime, val, *new Polymer());
    }
    
    axonbouton(const Polymer& p) : Polymer(p)
    {
    axonbouton(Clock::now(), 0, p);
    }
    
    axonbouton(std::chrono::time_point<Clock> eventTime, int val, const Polymer& p) : Polymer(p)
    {
    m_NeuronType = val;
    resetParameters(eventTime);
    }
    /** Default destructor */
    virtual ~axonbouton() {};
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
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Axon bouton created." << std::endl; }
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Volume = 100;
    m_SurfaceArea = 100;
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
    
    int ConnectSynapse(std::chrono::time_point<Clock> eventTime, synapse* link_synapse, double distance)
    {
    s_SynapseDescription synapseConnection;
    synapseConnection.s_Synapse = link_synapse;
    synapseConnection.s_Distance = distance;
    m_SynapseList.push_back(synapseConnection);
    return 0;
    }
    
    int growth_Surface(std::chrono::time_point<Clock> eventTime, double surf_change)
    {
    add_TemporalAdjustment(eventTime, &m_SurfaceArea, surf_change, 100, 0);
    add_TemporalAdjustment(eventTime, &m_Energy, -100, 100, 0);
    return 0;
    }
    
    int growth_Volume(std::chrono::time_point<Clock> eventTime, double vol_change)
    {
    add_TemporalAdjustment(eventTime, &m_Volume, vol_change, 100, 0);
    int func_status = growth_Surface(eventTime, vol_change*0.1);
    add_TemporalAdjustment(eventTime, &m_Energy, -100, 100, 0);
    return 0;
    }
    
    int Update(std::chrono::time_point<Clock> eventTime)
    {
    int release_State;
    adjust_Counters(eventTime);
    
            for(std::vector<synapticvesicle>::iterator it = m_SynapticVesicleList.begin(); it != m_SynapticVesicleList.end(); ++it)
                {
                it->Update(eventTime);
                }
    
    if (m_Energy > 0)
        {
        for(std::vector<synapticvesicle>::iterator it = m_SynapticVesicleList.begin(); it != m_SynapticVesicleList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-(m_Energy/2))/m_SynapticVesicleList.size(), 100, 1);   // redistribute energy
            it->AddEnergy(eventTime, m_Energy/m_SynapticVesicleList.size());
            }
        }
    
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(eventTime - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_duration > 1000)
        {
        for(std::vector<synapticvesicle>::iterator it = m_SynapticVesicleList.begin(); it != m_SynapticVesicleList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-(m_Energy/2))/m_SynapticVesicleList.size(), 100, 1);   // redistribute energy
            release_State = it->GetReleaseState(eventTime);
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
    std::vector<synapticvesicle> m_SynapticVesicleList;
    
    struct s_SynapseDescription
    {
    synapse* s_Synapse;
    double s_Distance;
    };
    std::vector<s_SynapseDescription> m_SynapseList;
};

#endif /* axonbouton_hpp */
