/*------------------------------------------------------------------------------*/
/* @file      compositeforceparticle.h                                          */
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

#ifndef BRAINHARMONICS_COMPOSITEFORCEPARTICLE_H
#define BRAINHARMONICS_COMPOSITEFORCEPARTICLE_H

#include <iostream>
#include <vector>
#include "universe.h"

class CompositeForceParticle : public Universe
{
public:
    CompositeForceParticle() : CompositeForceParticle(0) {}
    
    CompositeForceParticle(unsigned int object_type) : CompositeForceParticle(object_type, std::chrono::high_resolution_clock::now()) {}
    
    CompositeForceParticle(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    CompositeForceParticle(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitive_network type will have its own parameter ranges. The default is 0
    composite_forceparticle_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "CompositeForceParticle", composite_forceparticle_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }

    /** Default destructor */
    virtual ~CompositeForceParticle() {}
    /** Access composite_force_counter
     * \return The current value of composite_force_counter
     */
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_counter; }
    double GetGravitation(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_gravitation; }
    double GetWeak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_weak; }
    double GetWeakElectroweak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_weak_electroweak; }
    double GetElectromagnetic(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_electromagnetic; }
    double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_electromagnetic_electroweak; }
    double GetStrong(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_strong; }
    double GetStrongFundamental(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_strong_fundamental; }
    double GetStrongResidual(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return composite_forceparticle_strong_residual; }
    
    double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyWeak(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyStrong(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) { return val; }
    double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) { return val; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { composite_forceparticle_counter = val; }
    void SetGravitation(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_gravitation = val; }
    void SetWeak(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_weak = val; }
    void SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_weak_electroweak = val; }
    void SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_electromagnetic = val; }
    void SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_electromagnetic_electroweak = val; }
    void SetStrong(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_strong = val; }
    void SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_strong_fundamental = val; }
    void SetStrongResidual(std::chrono::time_point<Clock> event_time, double val) {composite_forceparticle_strong_residual = val; }

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    CompositeForceParticle*  CreateElementaryParticle(std::chrono::time_point<Clock> event_time);
    
    std::vector<CompositeForceParticle*> CreateElementaryParticles(std::chrono::time_point<Clock> event_time, int quantity);
    
    CompositeForceParticle*  CloneElementaryParticle(std::chrono::time_point<Clock> event_time, CompositeForceParticle* clone_object, double perfection_membership);
    
    std::vector<CompositeForceParticle*> CloneElementaryParticles(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> cloning_list, double perfection_membership);
    
    CompositeForceParticle*  DestroyElementaryParticle(std::chrono::time_point<Clock> event_time, CompositeForceParticle* destroy_object);
    
    std::vector<CompositeForceParticle*> DestroyElementaryParticles(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> destruction_list);
    
    CompositeForceParticle*  AddElementaryParticle(std::chrono::time_point<Clock> event_time, CompositeForceParticle* add_object);
    
    std::vector<CompositeForceParticle*> AddElementaryParticles(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> add_objects);
    
    CompositeForceParticle*  RemoveElementaryParticle(std::chrono::time_point<Clock> event_time);
    
    std::vector<CompositeForceParticle*> RemoveElementaryParticles(std::chrono::time_point<Clock> event_time, int quantity);
    
    CompositeForceParticle*  GetElementaryParticle(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CompositeForceParticle*> GetElementaryParticles(std::chrono::time_point<Clock> event_time);
    
    CompositeForceParticle*  CreateElementaryForce(std::chrono::time_point<Clock> event_time);
    
    std::vector<CompositeForceParticle*> CreateElementaryForces(std::chrono::time_point<Clock> event_time, int quantity);
    
    CompositeForceParticle*  CloneElementaryForce(std::chrono::time_point<Clock> event_time, CompositeForceParticle* clone_object, double perfection_membership);
    
    std::vector<CompositeForceParticle*> CloneElementaryForces(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> cloning_list, double perfection_membership);
    
    CompositeForceParticle*  DestroyElementaryForce(std::chrono::time_point<Clock> event_time, CompositeForceParticle* destroy_object);
    
    std::vector<CompositeForceParticle*> DestroyElementaryForces(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> destruction_list);
    
    CompositeForceParticle*  AddElementaryForce(std::chrono::time_point<Clock> event_time, CompositeForceParticle* add_object);
    
    std::vector<CompositeForceParticle*> AddElementaryForces(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> add_objects);
    
    CompositeForceParticle*  RemoveElementaryForce(std::chrono::time_point<Clock> event_time);
    
    std::vector<CompositeForceParticle*> RemoveElementaryForces(std::chrono::time_point<Clock> event_time, int quantity);
    
    CompositeForceParticle*  GetElementaryForce(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CompositeForceParticle*> GetElementaryForces(std::chrono::time_point<Clock> event_time);
    
    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CompositeForceParticle*> set_of_update_pointers, unsigned int pointer_type);
    
    int Update(std::chrono::time_point<Clock> event_time);

protected:
    std::vector<CompositeForceParticle*> elementary_particle_list;
    std::vector<CompositeForceParticle*> elementary_force_list;
    
private:
    unsigned int composite_forceparticle_counter; //!< Member variable "composite_force_counter"
    int composite_forceparticle_type;
    int duration_since_last_event;
    double composite_forceparticle_gravitation;
    double composite_forceparticle_weak;
    double composite_forceparticle_weak_electroweak;
    double composite_forceparticle_electromagnetic;
    double composite_forceparticle_electromagnetic_electroweak;
    double composite_forceparticle_strong;
    double composite_forceparticle_strong_fundamental;
    double composite_forceparticle_strong_residual;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_disabled;
    bool object_initialised;
};

#endif // BRAINHARMONICS_COMPOSITEFORCEPARTICLE_H
