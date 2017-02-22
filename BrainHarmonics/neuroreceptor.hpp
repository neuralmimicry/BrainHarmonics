//
//  neuroreceptor.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//
// The Energy level used in this function only enables the receptor to activate.
// It does not necessarily mean that a spike will flow through. It depends what
// is waiting in the void beyond the membrane.
//
// Metabotropic Receptors and Ionotropic Receptor are possibilities
// The type of receptor can be defined by polymer connection or stated
// as an integer type.
//
// Metabotropic
// 1: Receptive to GABA neurotransmitters
// 2:
// Ionotropic
// 3: Cys-loop
// 4: Glutamate receptor
// 5: ATP-gated

    // Type-3 Serotonin receptor (5HT3-R)

#ifndef neuroreceptor_h
#define neuroreceptor_h

#include <iostream>
#include <chrono>
#include "polymer.h"
typedef std::chrono::high_resolution_clock Clock;

class Neuroreceptor : public Polymer
{
public:
    /** Default constructor */
    Neuroreceptor(const Polymer& p) : Polymer(p)
    {
        resetParameters();
    };
    /** Default destructor */
    virtual ~Neuroreceptor() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    bool getReceptorBindingState() { return m_boundReceptor; }
    int getReceptorType() { return m_typeReceptor; }
    bool getDisabled() { return m_Disabled; }
    int getIons() { return m_Ions; }
    
    void setReceptorBindingState(bool val) { m_boundReceptor = val; if (m_boundReceptor) { m_Energy = m_EnergyFull; } }
    void toggleReceptorBindingState() { m_boundReceptor = !m_boundReceptor; }
    void toggleDisabled() { m_Disabled = !m_Disabled; setReceptorBindingState(false); }
    void setDisabled(bool val) { m_Disabled = val; setReceptorBindingState(false); }
    void setReceptorType(int val) { m_typeReceptor = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void SetIons(int val) { m_Ions = val; }
    void Creation() {std::cout << "Neuroreceptor created." << std::endl; }
    
    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> val)
    {
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(val - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_Energy > 0)
        {
        if (getReceptorBindingState()) {
            
        }
        if (m_duration > 1000)
            {
            m_Energy -= 1;
            }
            if (m_Energy <= 0) {
                m_Energy = 0;
                m_Ions = 0;
                setReceptorBindingState(false);
            }
        }
        // Clock duration does not consider parallel or serial operation
    m_oldClock = val;
    }
    
    void resetParameters()
    {
    m_EnergyFull = 100;
    m_Energy = 0;
    m_Ions = 0;
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
    m_oldClock = Clock::now();
    }
protected:
private:
    int m_NeuronType;
    double m_Volume;
    double m_SurfaceArea;
    double m_Length;
    bool m_Disabled;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_EnergyFull;
    int m_Ions;
    bool m_boundReceptor; //!< Member variable "m_boundReceptor"
    int m_typeReceptor; //!< Member variable "m_typeReceptor"
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
};

#endif /* neuroreceptor_h */
