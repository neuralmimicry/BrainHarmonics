    //
    //  neuron.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef neuron_h
#define neuron_h

#include <iostream>
#include <vector>

class neuron
{
public:
    /** Default constructor */
    neuron()
    {
    m_Counter = 0;
    m_GateKeeper = 0;
    m_ChannelMin = -1;
    m_ChannelMax = 1;
    m_Energy = 0;
    m_Spike = 1;
    };
    /** Default destructor */
    virtual ~neuron() {};
    
    int getCounter() { return m_Counter; }
    double getEnergy() { return m_Energy; }
    double getGateKeeper() { return m_GateKeeper; }
    double getChannelMin() { return m_ChannelMin; }
    double getChannelMax() { return m_ChannelMax; }
    
    
    void setCounter(int val) { m_Counter = val; }
    void setEnergy(double val) { m_Energy = val; }
    void setGateKeeper(double val) { m_GateKeeper = val; }
    void setChannelMin(double val) { m_ChannelMin = val; }
    void setChannelMax(double val) { m_ChannelMax = val; }

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
    
    void creation() {std::cout << "Neuron created." << std::endl; }
    
protected:
    
private:
    int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_Spike; //!< Member variable "m_Spike"
    double m_GateKeeper; //!< Member variable "m_GateKeeper"
    double m_ChannelMin; //!< Member variable "m_ChannelMin"
    double m_ChannelMax; //!< Member variable "m_ChannelMax"
    std::vector<neuron*> m_ConnectionList;
    std::vector<int> m_ConnectionLifetime;
};


#endif /* neuron_h */
