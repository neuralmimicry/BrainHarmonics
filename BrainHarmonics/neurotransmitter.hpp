//
//  neurotransmitter.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef neurotransmitter_hpp
#define neurotransmitter_hpp

#include <iostream>
#include "polymer.h"

class Neurotransmitter : public Polymer
{
public:
    /** Default constructor */
    Neurotransmitter() {};
    Neurotransmitter(const Polymer& p) : Polymer(p) {};
    /** Default destructor */
    virtual ~Neurotransmitter() {};
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
    void Creation() {std::cout << "Neurotransmitter created." << std::endl; }
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
};

#endif /* neurotransmitter_hpp */
