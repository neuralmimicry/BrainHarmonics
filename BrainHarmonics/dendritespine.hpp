//
//  dendritespine.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 08/02/17.
//  Copyright © 2017 Paul Isaac's. All rights reserved.
//

#ifndef dendritespine_hpp
#define dendritespine_hpp

#include <iostream>
#include "dendritecleft.hpp"

class dendritespine
{
public:
    /** Default constructor */
    dendritespine()
    {
    dendritespine(0);
    }
    
    dendritespine(int val)
    {
    m_NeuronType = val;
    resetParameters();
    };
    /** Default destructor */
    virtual ~dendritespine() {};
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
    void Creation() {std::cout << "Dendrite spine created." << std::endl; }
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
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
};

#endif /* dendritespine_hpp */
