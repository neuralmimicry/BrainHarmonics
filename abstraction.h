/*------------------------------------------------------------------------------*/
/* @file      abstraction.h                                                     */
/* @details   Bundle together smaller items as singular larger objects          */
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

#ifndef BRAINHARMONICS_ABSTRACTION_H
#define BRAINHARMONICS_ABSTRACTION_H

#include <vector>
#include "universe.h"

class Abstraction : public Universe
{
    public:
        /** Default constructor */
        Abstraction();
        /** Default destructor */
        virtual ~Abstraction();
        /** Access m_Counter
         * \return The current value of m_Counter
         */
        unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
        /** Set m_Counter
         * \param val New value to Set
         */
        void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    protected:
    private:
        unsigned int m_Counter; //!< Member variable "m_Counter"
};

#endif // BRAINHARMONICS_ABSTRACTION_H
