/*------------------------------------------------------------------------------*/
/* @file      polymer.h                                                         */
/* @details   Assign structure for scalar values                                */
/* @author    Paul Isaac's                                                      */
/* @date      16.02.2016                                                        */
/* @Copyright © 2016 Paul Isaac's. All rights reserved.                         */
/*------------------------------------------------------------------------------*/

/* Code snippets used:                                                          */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com          */
/* The class defines a data point and the operations that can be carried out on */
/* it.                                                                          */
/* Using the hierarchical linking the aim is to develop the application to      */
/* relate to real-world physics. This will then ease mapping between simulation,*/
/* emulation and real-world universes.                                          */

#ifndef POLYMER_H
#define POLYMER_H

#include <iostream>
#include <vector>
#include "monomer.h"

class Polymer : public Monomer
{
    
public:
    /** Default constructor */
    Polymer(Monomer& mm) : Monomer(mm) {
            //std::cout << "Polymer connected to Monomer @ " << &mm << std::endl;
        //        std::copy(&mm, &mm + 1, std::back_inserter(polymermonomerlist));
    };
    /** Default destructor */
    virtual ~Polymer() {};
    
    unsigned int getCounter() { return polymerCounter; }
    
    void setCounter(unsigned int val) { polymerCounter = val; }
    /*
     void add_monomer(std::vector<monomer> *aPartof, int arrayEntry)
     {
     monomer myMonomer((*aPartof)[arrayEntry]);
     // Use copy not push_back otherwise data is destroyed on exiting function
     std::copy(&myMonomer, &myMonomer + 1, std::back_inserter(polymermonomerlist));
     }
     */
        //    std::vector<monomer *> getMonomerList() { return polymermonomerlist; }
    
    void creation() {std::cout << "Polymer added." << std::endl; }
    
protected:
private:
        //    std::vector<monomer*> polymermonomerlist;
        //    std::vector<monomer*>::const_iterator polymermonomerlistiterator;
    
    unsigned int polymerCounter; //!< Member variable "polymerCounter"
};


#endif // POLYMER_H
