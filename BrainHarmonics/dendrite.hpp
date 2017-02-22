//
//  dendrite.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef dendrite_hpp
#define dendrite_hpp

#include <iostream>
#include <math.h>       /* sqrt */
#include "dendritebranch.hpp"
#include "dendritespine.hpp"

class dendrite
{
public:
    /** Default constructor */
    dendrite()
    {
    dendrite(0);
    }
    
    dendrite(int val)
    {
    m_NeuronType = val;
    resetParameters();
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
    
    void setDendriteLength(double val) { m_dendriteLength = val; }
    void setDendriteDiameterStart(double val) { m_dendriteDiameterStart = val; }
    void setDendriteDiameterEnd(double val) { m_dendriteDiameterEnd = val; }
    void setMembraneResistance(double val) { m_membraneResistance = val; }
    void setMembraneCapacitance(double val) { m_membraneCapacitance = val; }
    void setInternalResistance(double val) { m_internalResistance = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Dendrite created." << std::endl; }
    void resetParameters()
    {
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_Length = 100;
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
protected:
private:
    int m_NeuronType;
    double m_Volume;
    double m_SurfaceArea;
    double m_Length;
    int m_addStatus;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
                     // Length in micro-metres, typical 10-400 between branches
    double m_dendriteLength;  //!< Member variable "m_dendriteLength"
    double m_dendriteDiameterStart;  //!< Member variable "m_dendriteDiameterStart"
    double m_dendriteDiameterEnd;  //!< Member variable "m_dendriteDiameterEnd"
    double m_membraneResistance;
    double m_membraneCapacitance;
    double m_internalResistance;
};

#endif /* dendrite_hpp */
