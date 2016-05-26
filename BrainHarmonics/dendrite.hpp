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

class dendrite
{
public:
    /** Default constructor */
    dendrite() {};
    /** Default destructor */
    virtual ~dendrite() {};
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    double getDendriteLength() { return m_dendriteLength; }

    void setDendriteLength(double val) { m_dendriteLength = val; }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void Creation() {std::cout << "Dendrite created." << std::endl; }
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
                     // Length in micro-metres, typical 10-400 between branches
    double m_dendriteLength;  //!< Member variable "m_dendriteLength"
};

#endif /* dendrite_hpp */
