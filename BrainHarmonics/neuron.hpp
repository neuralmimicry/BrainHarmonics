    //
    //  neuron.hpp
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef neuron_hpp
#define neuron_hpp

#include <iostream>
#include <vector>
#include "soma.hpp"

class neuron
{
public:
    /** Default constructor */
    neuron()
    {
        // Default neuron type selected.
    neuron(1);
    }
    
    neuron(int val)
    {
    m_NeuronType = val;
        // Each neuron type will have its own parameter ranges. The default is 0, Pyramidal neuron
    resetParameters();
    m_Disabled = true;
    m_Counter = 0;
    m_GateKeeper = 0;
    m_ChannelMin = -1;
    m_ChannelMax = 1;
    m_Energy = 0;
    m_Spike = 1;
        // If every neuron has a soma, build a soma for this neuron
        //m_addStatus = add_Soma(&m_SomaList);
    m_addStatus = add_Soma();
    m_Disabled = false;
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
    
    void setCounter(int val) { m_Counter = val; }
    void setEnergy(double val) { m_Energy = val; }
    void setGateKeeper(double val) { m_GateKeeper = val; }
    void setChannelMin(double val) { m_ChannelMin = val; }
    void setChannelMax(double val) { m_ChannelMax = val; }
    void setDisabled(bool val) { m_Disabled = val; }
    void toggleDisabled() { m_Disabled = !m_Disabled; }
    void setNeuronType(int val) { m_NeuronType = val; resetParameters(); }
    
    void resetParameters()
    {
    m_RestingPotential = -70; // in millivolts
    switch(m_NeuronType)
        {
            case 0:
            {
            m_RestingPotential = -80;
            break;
            }
            case 1:
            {
            m_RestingPotential = -70;
            break;
            }
            case 2:
            {
            m_RestingPotential = -60;
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
    int add_Soma()
    {
    m_SomaList.push_back(soma(m_NeuronType));
    return 0;
    }

protected:
    
private:
    int m_NeuronType;
    double m_RestingPotential;
    bool m_Disabled;
    int m_addStatus;
    int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_Spike; //!< Member variable "m_Spike"
    double m_GateKeeper; //!< Member variable "m_GateKeeper"
    double m_ChannelMin; //!< Member variable "m_ChannelMin"
    double m_ChannelMax; //!< Member variable "m_ChannelMax"
    std::vector<soma> m_SomaList;
};


#endif /* neuron_hpp */
