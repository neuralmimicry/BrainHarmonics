    //
    //  neuron.hpp
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef neuron_hpp
#define neuron_hpp

#include <chrono>
#include <iostream>
#include <vector>
#include "soma.hpp"
typedef std::chrono::high_resolution_clock Clock;

class neuron
{
public:
    /** Default constructor */
    neuron()
    {
        // Default neuron type selected.
    neuron(std::chrono::high_resolution_clock::now(), 0);
    }
    
    neuron(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, int val)
    {
    m_NeuronType = val;
        // Each neuron type will have its own parameter ranges. The default is 0, Pyramidal neuron
    resetParameters(eventTime);
    m_Disabled = true;
        // If every neuron has a soma, build a soma for this neuron
        //m_addStatus = add_Soma(&m_SomaList);
    m_addStatus = add_Soma(eventTime);
    if(m_addStatus==0)
        {
        std::cout << "Soma energy: " << m_SomaList[0].GetEnergy() << std::endl;
    m_Disabled = false;
        }
    };
    /** Default destructor */
    virtual ~neuron() {};
    
    int getCounter() { return m_Counter; }
    double getEnergy() { return m_Energy; }
    double getGateKeeper() { return m_GateKeeper; }
    double getChannelMin() { return m_ChannelMin; }
    double getChannelMax() { return m_ChannelMax; }
    bool getDisabled() { return m_Disabled; }
    int getNeuronType() { return m_NeuronType; }
    double getRestingPotential() { return m_RestingPotential; }
    
    void AddEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, double val)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, val, 100, 0);     // Add energy
    add_TemporalAdjustment(eventTime, &m_Energy, -val, 1000, 1);   // Decay energy
    }
    void setCounter(int val) { m_Counter = val; }
    void setEnergy(double val) { m_Energy = val; }
    void setGateKeeper(double val) { m_GateKeeper = val; }
    void setChannelMin(double val) { m_ChannelMin = val; }
    void setChannelMax(double val) { m_ChannelMax = val; }
    void setDisabled(bool val) { m_Disabled = val; }
    void toggleDisabled() { m_Disabled = !m_Disabled; }
    void setNeuronType(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, int val) { m_NeuronType = val; resetParameters(eventTime); }
    
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Counter = 0;
    m_GateKeeper = 0;
    m_ChannelMin = -1;
    m_ChannelMax = 1;
    AddEnergy(eventTime, 100);
    m_EnergyThreshold = 2000;
    m_Size = 1;
    m_Spike = 1;
    m_RestingPotential = -70; // in millivolts
    switch(m_NeuronType)
        {
            case 0:
            {
            m_RestingPotential = -80;
            m_Size = 3;
            break;
            }
            case 1:
            {
            m_RestingPotential = -70;
            m_Size = 2;
            break;
            }
            case 2:
            {
            m_RestingPotential = -60;
            m_Size = 1;
            break;
            }
        }
    
    }
        //    void addConnection(std::vector<neuron*> val) { m_ConnectionList.push_back(&val); }
    
    bool openGate(double val)
    {
    if((val >= m_ChannelMin && val <= m_ChannelMax) or m_Energy > 0.1)
        {
        if((val >= m_ChannelMin && val <= m_ChannelMax))
            {
            m_Energy = m_Energy + m_Spike;
            return true;
            }
        }
    else
        {
        m_Energy = m_Energy * 0.99;
        }
    return false;
    }
    
    void Creation()
    {
    std::cout << "Neuron created." << std::endl;
    }
    
    /*
     int add_Soma (std::vector<soma> *toAddto)
     {
     soma mySoma(m_NeuronType);
     std::copy(&mySoma, &mySoma + 1, std::back_inserter(*toAddto));
     return 0;
     }
     */
    int add_Soma(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_SomaList.push_back(soma(eventTime, m_NeuronType));
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
    
#pragma omp parallel
        {
#pragma omp single nowait
            {
            for(std::vector<soma>::iterator it = m_SomaList.begin(); it != m_SomaList.end(); ++it)
                {
#pragma omp task
                it->Update(eventTime);
                }
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
/*    for(std::vector<s_CounterAdjustment>::iterator it = m_TemporalAdjustment.begin(); it != m_TemporalAdjustment.end(); ++it)
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
    double m_Size;
    double m_RestingPotential;
    bool m_Disabled;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    int m_addStatus;
    int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_EnergyThreshold;
    double m_Spike; //!< Member variable "m_Spike"
    double m_GateKeeper; //!< Member variable "m_GateKeeper"
    double m_ChannelMin; //!< Member variable "m_ChannelMin"
    double m_ChannelMax; //!< Member variable "m_ChannelMax"
    std::vector<soma> m_SomaList;
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


#endif /* neuron_hpp */
