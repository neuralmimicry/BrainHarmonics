//
//  axon.hpp
//  BrainHarmonics
//
//  Created by Paul Isaac's on 03/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef axon_hpp
#define axon_hpp

#include <iostream>
#include "axonbranch.hpp"
#include "axonbouton.hpp"

class axon
{
public:
    /** Default constructor */
    axon()
    {
    axon(0);
    }
    
    axon(int val)
    {
    m_NeuronType = val;
    resetParameters();
        // If every axon has an axonbranch, build an axonbranch for this axon
        //    m_addStatus = add_AxonBranch(&m_AxonBranchList);
        // If every axon has an axonbouton, build an axonbouton for this axon
        //    m_addStatus = add_AxonBouton(&m_AxonBoutonList);
    };
    /** Default destructor */
    virtual ~axon() {};
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
    void Creation() {std::cout << "Axon created." << std::endl; }

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
    int add_AxonBranch (std::vector<axonbranch> *toAddto)
    {
    axonbranch myAxonBranch;
    std::copy(&myAxonBranch, &myAxonBranch + 1, std::back_inserter(*toAddto));
    return 0;
    }

    int add_AxonBouton (std::vector<axonbouton> *toAddto)
        {
            axonbouton myAxonBouton;
            std::copy(&myAxonBouton, &myAxonBouton + 1, std::back_inserter(*toAddto));
        return 0;
        }
*/
    
    int add_AxonBranch()
    {
    m_AxonBranchList.push_back(axonbranch(m_NeuronType));
    return 0;
    }
    
    int add_AxonBouton()
    {
    m_AxonBoutonList.push_back(axonbouton(m_NeuronType));
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
    double m_axonlength;
    std::vector<axonbranch> m_AxonBranchList;
    std::vector<axonbouton> m_AxonBoutonList;
};

#endif /* axon_hpp */
