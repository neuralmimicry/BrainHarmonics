//
//  dendritecleft.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef dendritecleft_hpp
#define dendritecleft_hpp

#include <iostream>

class dendritecleft
{
public:
    /** Default constructor */
    dendritecleft();
    /** Default destructor */
    virtual ~dendritecleft();
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
    void Creation() {std::cout << "Dendritic Synaptic Cleft created." << std::endl; }
protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
};

#endif /* dendritecleft_hpp */
