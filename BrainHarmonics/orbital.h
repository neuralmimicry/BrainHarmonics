    //
    //  orbital.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 17/03/17.
    //  Copyright © 2017 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_ORBITAL_H
#define BRAINHARMONICS_ORBITAL_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <math.h>               /**< For Sine, Cosine, Power, Fabs & Sqrt functions*/
#include <string>
#include <vector>
#include "dimension.h"

class Orbital : public Dimension
{
public:
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
    
    double m_Energy = 0; //!< Member variable "m_Energy"
    
    /** Default constructor */
    Orbital() {};
    
    Orbital(Dimension& od) : Dimension(od)
    {
    Orbital(od, std::chrono::high_resolution_clock::now(), 0);
    }
    
    Orbital(Dimension& od, std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, int val) : Dimension(od)
    {
    m_TemporalAdjustment.clear();
    m_OrbitalType = val;
    resetParameters(eventTime);
    Creation();
    };
    /** Default destructor */
    virtual ~Orbital() {};
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    double GetPosition() { return m_Position; }
    double GetPhase() { return m_Phase; }
    double GetTau() { return m_Tau; }
    
    void AddEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, double val)
    {
        //std::cout << " Before: " << m_Energy << std::endl;
    add_TemporalAdjustment(eventTime, &m_TemporalAdjustment, &m_Energy, val, 1000000000, 0);     // Add energy
                                                                                                 //    std::cout << "After: " << m_Energy << std::endl;
    add_TemporalAdjustment(eventTime, &m_TemporalAdjustment, &m_Energy, -val, 10000000000, 1);   // Decay energy
    }
    void DelEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, double val)
    {
        //    std::cout << "Before: " << m_Energy << std::endl;
    add_TemporalAdjustment(eventTime, &m_TemporalAdjustment, &m_Energy, -val, 10000000000, 1);     // Del energy
    }
    void SetPosition(double val) { m_Position = val; }
    void SetPhase(double val) { m_Phase = val; }
    void SetTau(double val) { m_Tau = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {
            //std::cout << "Orbit Type " << m_OrbitalType << " created." << std::endl;
    }
    
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Energy = 5.0f;
    m_Tau = int(50000000000000);
    m_Position = 0.0f;
    m_Phase = 0.0f;
    m_InternalClock = int(0);
    m_Duration = int(0);
    switch(m_OrbitalType)
        {
            case 0:
            {
            m_Tau = int(rand() % 50000000000000);
            break;
            }
            case 1:
            {
            m_Tau = int(70000000000000);
            break;
            }
            case 2:
            {
            m_Tau = int(50000000000000);
            break;
            }
        }
    m_OldClock = eventTime;
    }
    
    void CalcPosition(double Duration)
    {
    switch(m_OrbitalType)
        {
            case 0:
            {
            m_Position = sin((TWORAD * (m_Tau / Duration)) + m_Phase);
            break;
            }
            case 1:
            {
            m_Position = cos((TWORAD * (m_Tau / Duration)) + m_Phase);
            break;
            }
            case 2:
            {
            m_Position = tan((TWORAD * (m_Tau / Duration)) + m_Phase);
            break;
            }
        }
        //std::cout << "Position: " << m_Position << std::endl;
    }
    
    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
        // Step through each registered time dependent counter and adjust accordingly.
    adjust_Counters(eventTime);
    
        //      std::cout << "Orbital Energy: " << m_Energy << std::endl;
    
        // Only activate new position if there is energy available.
        // Calculate time since last function call. Time can be synthetic.
    m_Duration = int(std::chrono::duration_cast<std::chrono::nanoseconds>(eventTime - m_OldClock).count());
    
        //std::cout << "Duration: " << m_Duration << std::endl;
    
        // If duration is negative then attempt to reverse time. Reset and ignore position change.
        // Re-look at if forward and reverse time is enabled for simulations.
    if (m_Duration <= 0)
        {
        m_Duration = int(0);
        }

    
        // Reset energy counter if over ambitious counter adjustment. May require a relook if considering potential energy
    if (m_Energy < 0.0000001f)
        {
        m_Energy = 0.0f;
        }
    
    if (m_TemporalAdjustment.size() == 0 && m_Energy != 0)
        {
            // Reduce energy for each cycle
        DelEnergy(eventTime, m_Energy);
        }

    if (m_Energy > 0.0f)
        {
            //            std::cout << "Clock: " << m_InternalClock << "  Duration: " << m_Duration << std::endl;
        m_InternalClock += m_Duration;
        m_InternalClock = m_InternalClock % m_Tau;
            //std::cout << "Clock: " << m_InternalClock << "  Tau: " << m_Tau << std::endl;
        CalcPosition(m_InternalClock);
        }
    else
        {
        CalcPosition(m_Tau);
        }
    
        // Clock duration does not consider parallel or serial operation
    m_OldClock = eventTime;
    return 0;
    }
    
    void add_TemporalAdjustment(std::chrono::time_point<std::chrono::high_resolution_clock> cb, std::vector<s_CounterAdjustment> *toAddto, double *ptc, double p, int i, int s)
    {
    s_CounterAdjustment myCounterAdjustment;
    myCounterAdjustment.s_CounterBegin = cb;        // What time does this event occur
    myCounterAdjustment.s_PointToCounter = ptc;     // Which counter to increment
    myCounterAdjustment.s_Pool = p;                 // Amount to adjust by
    myCounterAdjustment.s_Interval = i;             // Adjust over what time period
    myCounterAdjustment.s_Shape = s;                // Transfer function
    std::copy(&myCounterAdjustment, &myCounterAdjustment + 1, std::back_inserter(*toAddto));
        //    m_TemporalAdjustment.push_back(myCounterAdjustment);
        //    std::cout << "Begin "  << std::endl;
    }
    
    void adjust_Counters(std::chrono::time_point<std::chrono::high_resolution_clock> currentTime)
    {
    int timeDifference = 0;
    double incrementBy = 0.0f;
    
        // std::cout << "No. of adjustments: " << m_TemporalAdjustment.size() << std::endl;
    
    for(std::vector<s_CounterAdjustment>::iterator it = m_TemporalAdjustment.begin(); it != m_TemporalAdjustment.end(); ++it)
        {
        if (it->s_Pool != 0.0f)
            {
            timeDifference = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - it->s_CounterBegin).count();
            if (timeDifference > 0)
                {
                incrementBy = 1.0f;
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
                    // std::cout << "Pool: " << it->s_Pool << "  Increment by: " << incrementBy << std::endl;
                it->s_Pool -= incrementBy;
                if (it->s_Pool < 0.0f && incrementBy > 0.0f)
                    {
                    incrementBy += it->s_Pool;
                    it->s_Pool = 0.0f;
                    }
                if (it->s_Pool > 0.0f && incrementBy < 0.0f)
                    {
                    incrementBy -= it->s_Pool;
                    it->s_Pool = 0.0f;
                    }
                *it->s_PointToCounter += incrementBy;
                it->s_CounterBegin = currentTime;
                if((incrementBy * incrementBy) < 0.000001f)
                    {
                    it->s_Pool = 0.0f;
                    }
                }
            else
                {
                if (timeDifference < 0)
                    {
                        //it->s_Pool = 0.0f;
                    }
                }
            }
        
        }
    
        // Remove empty pools of adjustments
    m_TemporalAdjustment.erase( std::remove_if(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), []( const s_CounterAdjustment& item) { return (item.s_Pool == 0 ); }), m_TemporalAdjustment.end());
        // Remove adjusters when energy depleted
    m_TemporalAdjustment.erase( std::remove_if(m_TemporalAdjustment.begin(), m_TemporalAdjustment.end(), [](const s_CounterAdjustment& item) { return (*item.s_PointToCounter <= 0.0f ); }), m_TemporalAdjustment.end());
    }
    
protected:
    
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    int m_OrbitalType;
    int m_Tau;
    double m_Position;
    double m_Phase;
    int m_Duration;
    int m_InternalClock;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_OldClock;
    
};

#endif // BRAINHARMONICS_ORBITAL_H
