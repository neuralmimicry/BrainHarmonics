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
    double GrabEnergy()
    {
    m_ReduceBy = 100;
    GrabEnergy(m_ReduceBy);
    }
    double GrabEnergy(double val)
    {
    m_ReducedBy = val;
    m_Energy -= m_ReducedBy;
    if (m_Energy < 0)
        {
        m_ReducedBy += m_Energy;
        m_Energy = 0;
        }
    return m_ReducedBy;
    }
    /** Set m_Counter
     * \param val New value to set
     */
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
    m_NeuroTransmitterList.push_back(myNeurotransmitter);
    return 0;
    }
    
    int add_Neurotransmitter(Neurotransmitter *val)
    {
    m_NeuroTransmitterList.push_back(*val);
    return 0;
    }

    int remove_Neurotransmitter(Neurotransmitter *val)
    {
    m_NeuroTransmitterList.erase(std::remove(m_NeuroTransmitterList.begin(), m_NeuroTransmitterList.end(), *val), m_NeuroTransmitterList.end());
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
    m_NeuroReceptorList.push_back(*val);
    return 0;
    }
    
    int remove_Neuroreceptor(Neuroreceptor *val)
    {
    m_NeuroReceptorList.erase(std::remove(m_NeuroReceptorList.begin(), m_NeuroReceptorList.end(), *val), m_NeuroReceptorList.end());
    return 0;
    }
    
    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> val)
    {
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(val - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_Energy > 0)
        {
        if (m_duration > 1000)
            {
            m_Energy -= 1;
            }
        if (m_Energy <= 0)
            {
            m_Energy = 0;
            }
        }
        // Clock duration does not consider parallel or serial operation
    m_oldClock = val;
    }
        
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_ReduceBy;
    double m_ReducedBy;
    std::vector<Neurotransmitter> m_NeuroTransmitterList;
    std::vector<Neuroreceptor> m_NeuroReceptorList;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    
};

#endif /* synapse_hpp */
