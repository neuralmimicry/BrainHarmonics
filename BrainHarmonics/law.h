/*------------------------------------------------------------------------------*/
/* @file      law.h                                                             */
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

#ifndef BRAINHARMONICS_LAW_H
#define BRAINHARMONICS_LAW_H

#include <iostream>
#include "universe.h"

class Law : public Universe
{
public:
    Law() : Law(0) {}
    
    Law(unsigned int object_type) : Law(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Law(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Law(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each law type will have its own parameter ranges. The default is 0
    law_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Law", law_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Law() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time);
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val);
    
    int Update(std::chrono::time_point<Clock> event_time);
 
    void SetCharge(std::chrono::time_point<Clock> event_time, int val) final {}
    void SetSpin(std::chrono::time_point<Clock> event_time, int val) final {}
    double GetGravitation(std::chrono::time_point<Clock> event_time) final {}
    double GetWeak(std::chrono::time_point<Clock> event_time) final {}
    double GetWeakElectroweak(std::chrono::time_point<Clock> event_time) final {}
    double GetElectromagnetic(std::chrono::time_point<Clock> event_time) final {}
    double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) final {}
    double GetStrong(std::chrono::time_point<Clock> event_time) final {}
    double GetStrongFundamental(std::chrono::time_point<Clock> event_time) final {}
    double GetStrongResidual(std::chrono::time_point<Clock> event_time) final {}
    
    double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyWeak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrong(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) final {}
    
    void SetGravitation(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetWeak(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetStrong(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val) final {}
    void SetStrongResidual(std::chrono::time_point<Clock> event_time, double val) final {}
    
    void PollElementaryForce(std::chrono::time_point<Clock> event_time) final {}
    
        //    void SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val) final {}
    
        //    std::vector<double> GetPointPosition(std::chrono::time_point<Clock> event_time) final {}
    
        //    int GetCharge(std::chrono::time_point<Clock> event_time) final {}

protected:
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    int law_type;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_disabled;
    bool object_initialised;
    int duration_since_last_event;
};

#endif // BRAINHARMONICS_LAW_H
