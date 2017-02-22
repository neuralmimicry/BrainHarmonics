//
//  axonhillock.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef axonhillock_hpp
#define axonhillock_hpp

#include <iostream>
#include "axon.hpp"

class axonhillock
{
public:
    /** Default constructor */
    axonhillock()
    {
    axonhillock(0);
    }
    
    axonhillock(int val)
    {
    m_NeuronType = val;
        // If every axonhillock has an axon, build an axon for this axonhillock
    m_addStatus = add_Axon();
    };
    /** Default destructor */
    virtual ~axonhillock() {};
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
    void Creation() {std::cout << "Axon Hillock created." << std::endl; }
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
    int add_Axon (std::vector<axon> *toAddto)
    {
    axon myAxon;
    std::copy(&myAxon, &myAxon + 1, std::back_inserter(*toAddto));
    return 0;
    }
*/
    
    int add_Axon()
    {
    m_AxonList.push_back(axon(m_NeuronType));
    return 0;
    }
    
    
protected:
private:
    int m_NeuronType;
    double m_Volume;
    double m_SurfaceArea;
    int m_addStatus;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    std::vector<axon> m_AxonList;
};

#endif /* axonhillock_hpp */
