/*------------------------------------------------------------------------------*/
/* @file      elementaryforce.h                                                 */
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

#ifndef BRAINHARMONICS_ELEMENTARYFORCE_H
#define BRAINHARMONICS_ELEMENTARYFORCE_H

#include <iostream>
#include <vector>
#include "universe.h"

class ElementaryForce : public Universe
{
    friend class CompositeForceParticle;
public:
    ElementaryForce() : ElementaryForce(0) {}
    
    ElementaryForce(unsigned int object_type) : ElementaryForce(object_type, std::chrono::high_resolution_clock::now()) {}
    
    ElementaryForce(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    ElementaryForce(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitive_network type will have its own parameter ranges. The default is 0
    elementary_force_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "ElementaryForce", elementary_force_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }
    

    /** Default destructor */
    virtual ~ElementaryForce()
    {
    }

        // Access elementary_force_counter
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time);
    double GetEnergy(std::chrono::time_point<Clock> event_time);
    double GetGravitation(std::chrono::time_point<Clock> event_time);
    double GetWeak(std::chrono::time_point<Clock> event_time);
    double GetWeakElectroweak(std::chrono::time_point<Clock> event_time);
    double GetElectromagnetic(std::chrono::time_point<Clock> event_time);
    double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time);
    double GetStrong(std::chrono::time_point<Clock> event_time);
    double GetStrongFundamental(std::chrono::time_point<Clock> event_time);
    double GetStrongResidual(std::chrono::time_point<Clock> event_time);
    
    double ApplyEnergy(std::chrono::time_point<Clock> event_time, double val);
    double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val);
    double ApplyWeak(std::chrono::time_point<Clock> event_time, double val);
    double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val);
    double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val);
    double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val);
    double ApplyStrong(std::chrono::time_point<Clock> event_time, double val);
    double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val);
    double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val);
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val);
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val);
    void SetGravitation(std::chrono::time_point<Clock> event_time, double val);
    void SetWeak(std::chrono::time_point<Clock> event_time, double val);
    void SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val);
    void SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val);
    void SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val);
    void SetStrong(std::chrono::time_point<Clock> event_time, double val);
    void SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val);
    void SetStrongResidual(std::chrono::time_point<Clock> event_time, double val);
    
    void PollElementaryForce(std::chrono::time_point<Clock> event_time);
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);

protected:

private:
    unsigned int elementary_force_counter; //!< Member variable "elementary_force_counter"
    int elementary_force_type;
    double elementary_force_energy;
    double elementary_force_gravitation;
    double elementary_force_weak;
    double elementary_force_weak_electroweak;
    double elementary_force_electromagnetic;
    double elementary_force_electromagnetic_electroweak;
    double elementary_force_strong;
    double elementary_force_strong_fundamental;
    double elementary_force_strong_residual;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_initialised;
    bool object_disabled;
    int duration_since_last_event;
    
    
};

#endif // BRAINHARMONICS_ELEMENTARYFORCE_H
