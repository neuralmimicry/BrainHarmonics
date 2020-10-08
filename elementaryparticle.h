/*------------------------------------------------------------------------------*/
/* @file      elementaryparticle.h                                              */
/* @details   Bosons etc                                                        */
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

#ifndef BRAINHARMONICS_ELEMENTARYPARTICLE_H
#define BRAINHARMONICS_ELEMENTARYPARTICLE_H

#include <iostream>
#include <vector>
#include "universe.h"

class ElementaryParticle : public Universe
{
    friend class CompositeForceParticle;
public:
    ElementaryParticle() : ElementaryParticle(0) {}
    
    ElementaryParticle(unsigned int object_type) : ElementaryParticle(object_type, std::chrono::high_resolution_clock::now()) {}
    
    ElementaryParticle(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    ElementaryParticle(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitive_network type will have its own parameter ranges. The default is 0
    elementary_particle_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "ElementaryParticle", elementary_particle_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }
    
    
    
    /** Default destructor */
    virtual ~ElementaryParticle() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time)         { return elementary_particle_counter; }
    unsigned int GetType(std::chrono::time_point<Clock> event_time)            { return elementary_particle_type; }
    int GetCharge(std::chrono::time_point<Clock> event_time)                   { return elementary_particle_charge; }     // Values 0-6 to give possible -1 to +1 in 1/3 increments
    int GetSpin(std::chrono::time_point<Clock> event_time)                     { return elementary_particle_spin; }       // Values given in multiples of 1/2 from 0, i.e. a val of 3 = 1.5. Even numbers (& 0) = Bosons. Odd numbers = Fermions
    double GetMass(std::chrono::time_point<Clock> event_time)                  { return elementary_particle_mass; }       // In GeV. Can be zero
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { elementary_particle_counter = val; }
    void SetType(std::chrono::time_point<Clock> event_time, unsigned int val)    { elementary_particle_type = val; }
    void SetCharge(std::chrono::time_point<Clock> event_time, int val)           { elementary_particle_charge = val; }
    void SetSpin(std::chrono::time_point<Clock> event_time, int val)             { elementary_particle_spin = val; }
    void SetMassIndex(std::chrono::time_point<Clock> event_time, int val);
    
    void SetMass(std::chrono::time_point<Clock> event_time, double val);
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    void Update(std::chrono::time_point<Clock> event_time);

    
protected:

private:
    unsigned int elementary_particle_counter;           //!< Member variable "elementary_particle_counter"
    unsigned int elementary_particle_type;              //!< Member variable "elementary_particle_type"
    int elementary_particle_charge;                     //!< Member variable "elementary_particle_charge"
    int elementary_particle_spin;                       //!< Member variable "elementary_particle_spin"
    double elementary_particle_mass;                    //!< Member variable "elementary_particle_mass"
    int elementary_particle_mass_index;                 //!< Member variable "elementary_particle_mass_index"
    const double kUnitKgeV = 1.783E-36;
    const double kUnitKgMeV = 1.783E-30;
    const double kUnitKgGeV = 1.783E-27;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    bool object_initialised;
    bool object_disabled;
};

#endif // BRAINHARMONICS_ELEMENTARYPARTICLE_H
