//
//  axonbouton.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef axonbouton_hpp
#define axonbouton_hpp

#include <iostream>
#include "synapticvesicle.hpp"
#include "synapse.hpp"

class axonbouton
{
public:
    /** Default constructor */
    axonbouton()
    {
    axonbouton(0);
    }
    
    axonbouton(int val)
    {
    m_NeuronType = val;
    resetParameters();

    };
    /** Default destructor */
    virtual ~axonbouton() {};
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
    void Creation() {std::cout << "Axon bouton created." << std::endl; }
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
protected:
private:
    int m_NeuronType;
    int m_addStatus;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    synapticvesicle m_synapticvesicle[100];
    synapse m_synapse;
};

#endif /* axonbouton_hpp */
