//
//  soma.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef soma_hpp
#define soma_hpp

#include <iostream>
#include <vector>
#include "axonhillock.hpp"
#include "dendrite.hpp"

class soma
{
public:
    /** Default constructor */
    soma()
    {
    soma(0);
    }
    
    soma(int val)
    {
    m_NeuronType = val;
    resetParameters();
        // If every soma has an axonhillock, build an axonhillock for this soma
    m_addStatus = add_Axonhillock();
        // If every soma has a dendrite, build a couple of dendrites for this soma
    m_addStatus = add_Dendrite();
    m_addStatus = add_Dendrite();
    };
    /** Default destructor */
    virtual ~soma() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    /** Set m_Counter
     * \param val New value to set
     */
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Soma created." << std::endl; }
    void resetParameters()
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
    
    int add_Axonhillock()
    {
    m_AxonhillockList.push_back(axonhillock(m_NeuronType));
    return 0;
    }

    int add_Dendrite()
    {
    m_DendriteList.push_back(dendrite(m_NeuronType));
    return 0;
    }
    
protected:
private:
    int m_NeuronType;
    int m_addStatus;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    std::vector<axonhillock> m_AxonhillockList;
    std::vector<dendrite> m_DendriteList;
};

#endif /* soma_hpp */
