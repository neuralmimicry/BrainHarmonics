//
//  neuroreceptor.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//
// Metabotropic Receptors and Ionotropic Receptor are possibilities

#ifndef neuroreceptor_h
#define neuroreceptor_h

#include <iostream>
#include "polymer.h"

class Neuroreceptor : public Polymer
{
public:
    /** Default constructor */
    Neuroreceptor(const Polymer& p) : Polymer(p) {};
    /** Default destructor */
    virtual ~Neuroreceptor() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    bool getReceptorBindingState() { return m_boundReceptor; }

    void setReceptorBindingState(bool val) { m_boundReceptor = val; }
    void toggleReceptorBindingState() { m_boundReceptor = !m_boundReceptor; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Neuroreceptor created." << std::endl; }
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    bool m_boundReceptor; //!< Member variable "m_boundReceptor"
};

#endif /* neuroreceptor_h */
