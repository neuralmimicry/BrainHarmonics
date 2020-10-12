/*!
 * @file      universe.h
 * @details   Base class of all operations
 * @author    Paul B. Isaac's, authored 03-FEB-2016
 * @date      08-APR-2020
 * @copyright © 2020 Linaro Limited.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Using the hierarchical linking the aim is to develop the application to
 * relate to real-world physics. This will then ease mapping between simulation,
 * emulation and real-world universes.
 */

    // Handy conversions
#ifndef DEG2RAD
#define DEG2RAD 0.01745329252f  /**< Avoids having to recalculate a constant PI/180 */
#endif // DEG2RAD

#ifndef RAD2DEG
#define RAD2DEG 57.29577951f    /**< Avoids having to recalculate a constant 180/PI */
#endif // RAD2DEG

#ifndef ONERAD
#define ONERAD 3.14159265f    /**< Avoids having to recalculate */
#endif // ONERAD

#ifndef TWORAD
#define TWORAD 6.28318530f    /**< Avoids having to recalculate */
#endif // TWORAD

#ifndef BRAINHARMONICS_UNIVERSE_H
#define BRAINHARMONICS_UNIVERSE_H

#define TYPE_NEURON_GEN1                                                          1000000000
#define TYPE_NEURON_PYRAMIDAL_GEN1                                                1100000000
#define TYPE_NEURON_PYRAMIDAL_MEMBRANE_GEN1                                       1110000000
#define TYPE_NEURON_PYRAMIDAL_SOMA_GEN1                                           1120000000
#define TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_GEN1                               1121000000
#define TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_GEN1                                  1122000000
#define TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_DENDRITEBRANCH_GEN1                   1122100000
#define TYPE_NEURON_PYRAMIDAL_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1     1122110000
#define TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_AXON_GEN1                          1121100000
#define TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1               1121110000
#define TYPE_NEURON_PYRAMIDAL_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1    1121111000
#define TYPE_SOLID_NEURON_GEN1                                                    2100000000
#define TYPE_SOLID_POLYHEDRON_SOMA_GEN1                                           2110000000
#define TYPE_SOLID_POLYHEDRON_MEMBRANE_GEN1                                       2120000000
#define TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_GEN1                               2111000000
#define TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_GEN1                          2111100000
#define TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_GEN1               2111110000
#define TYPE_SOLID_POLYHEDRON_SOMA_AXONHILLOCK_AXON_AXONBRANCH_AXONBOUTON_GEN1    2111111000
#define TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_GEN1                                  2112000000
#define TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_GEN1                   2112100000
#define TYPE_SOLID_POLYHEDRON_SOMA_DENDRITE_DENDRITEBRANCH_DENDRITECLEFT_GEN1     2112110000

#include <chrono>
#include <iostream>
#include <math.h>       /* sqrt */
#include <vector>
class ElementaryParticle;

typedef std::chrono::high_resolution_clock Clock;

class Dimension;

class Universe
{
    friend Dimension;
public:
        // Specifies members that are visible to the member functions of the class, class instances, member functions of descendent classes, and their instances.
    
    
        // Set default object type if no parameter given
    Universe() : Universe(0) {}

    Universe(int interim_object_type) : Universe(std::chrono::high_resolution_clock::now(), interim_object_type) {}
    
        // Correct objects have timestamps and type assigned
    Universe(std::chrono::time_point<Clock> event_time, int object_type)
    {
    universe_type=object_type;
    
        // Call notification of creation of object
    Creation(event_time, "Universe", universe_type);
    
        // As the new object is constructed ensure all variables are initialised
    ResetParameters(event_time);
    }
    
    virtual ~Universe()
    {
    point_list.clear();
    solid_list.clear();
    matter_list.clear();
    composite_forceparticle_list.clear();
    elementary_force_list.clear();
    elementary_particle_list.clear();
    polymer_list.clear();
    monomer_list.clear();
    cognitive_network_list.clear();
    dimension_list.clear();
    }
    
        // The object has finite energy that can be redistributed to child objects to control information flow
    double GetEnergy(std::chrono::time_point<Clock> event_time);
    
        // Define new maximum energy available
    void SetEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer);
    
        // Transfer an energy sum to another object
    double UseEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer);
    
        // Transfer an energy sum from another object
    double ReturnEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer);
    
        // Announce an object has been created
    void Creation(std::chrono::time_point<Clock> event_time, std::string object_title, int object_type);
    
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);
    
        // Initialise object member variables to default values
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
        // Whilst the design of functions is to be asynchronous it helps for monitoring to have reference clocks
    std::chrono::time_point<std::chrono::high_resolution_clock> TheTimeNow();
    
        // Simulated time can be speeded up or slowed down. This function calculates the simulated time.
    std::chrono::time_point<std::chrono::high_resolution_clock> TheCalculatedTimeNow(std::chrono::time_point<std::chrono::high_resolution_clock> time_object_created_time, std::chrono::time_point<Clock> event_time, double calculated_scaled_time);
    
        // Define the length of time that this object should exist
    void SetLifespan(std::chrono::time_point<Clock> event_time, std::chrono::nanoseconds life_time);
    
        // Extend the lifetime of this object
    void ExtendLife(std::chrono::time_point<Clock> event_time, std::chrono::nanoseconds life_time);
    
        // Has lifespan expired?
    bool IsDead(std::chrono::time_point<Clock> event_time);
    
        // Manipulate objects that are direct children of this class
        // Future scope to add groupings of derived objects and hierarchy of derived objects for cross-communication
    std::vector<Universe*> AddDimensions(std::chrono::time_point<Clock> event_time, int quantity);

                Universe*  AddDimension(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetDimensions(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetDimension(std::chrono::time_point<Clock> event_time, int selector);

    
    std::vector<Universe*> AddElementaryParticles(std::chrono::time_point<Clock> event_time, int quantity);
    
    			Universe*  AddElementaryParticle(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetElementaryParticles(std::chrono::time_point<Clock> event_time);
    
    			Universe*  GetElementaryParticle(std::chrono::time_point<Clock> event_time, int selector);

    
    std::vector<Universe*> AddElementaryForces(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddElementaryForce(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetElementaryForces(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetElementaryForce(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddCompositeForceParticles(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddCompositeForceParticle(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetCompositeForceParticles(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetCompositeForceParticle(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddMatters(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddMatter(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetMatters(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetMatter(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddMonomers(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddMonomer(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetMonomers(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetMonomer(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddPolymers(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddPolymer(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetPolymers(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetPolymer(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddSolids(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddSolid(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetSolids(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetSolid(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddCognitiveNetworks(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddCognitiveNetwork(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetCognitiveNetworks(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetCognitiveNetwork(std::chrono::time_point<Clock> event_time, int selector);
    
    
    std::vector<Universe*> AddPoints(std::chrono::time_point<Clock> event_time, int quantity);
    
                Universe*  AddPoint(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetPoints(std::chrono::time_point<Clock> event_time);
    
                Universe*  GetPoint(std::chrono::time_point<Clock> event_time, int selector);

    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Universe*> set_of_update_pointers, unsigned int pointer_type);
    
    int Update(std::chrono::time_point<Clock> event_time);

        // Define virtual functions that are made available to all derived objects of the tree from another branch
        // The = 0; at the end of the virtual function means that the function Must be defined at least once in a derived object.
    virtual void AddTemporalAdjustment(std::chrono::time_point<Clock> event_time, double *point_to_counter, double pool, int interval, int shape);
    
    virtual void AdjustCounters(std::chrono::time_point<std::chrono::high_resolution_clock> currentTime);
    
    virtual void SetCharge(std::chrono::time_point<Clock> event_time, int val);
    virtual void SetSpin(std::chrono::time_point<Clock> event_time, int val);
    virtual double GetGravitation(std::chrono::time_point<Clock> event_time);
    virtual double GetWeak(std::chrono::time_point<Clock> event_time);
    virtual double GetWeakElectroweak(std::chrono::time_point<Clock> event_time);
    virtual double GetElectromagnetic(std::chrono::time_point<Clock> event_time);
    virtual double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time);
    virtual double GetStrong(std::chrono::time_point<Clock> event_time);
    virtual double GetStrongFundamental(std::chrono::time_point<Clock> event_time);
    virtual double GetStrongResidual(std::chrono::time_point<Clock> event_time);
    
    virtual double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyWeak(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyStrong(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val);
    virtual double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val);
    
    virtual void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val);
    virtual void SetGravitation(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetWeak(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetStrong(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val);
    virtual void SetStrongResidual(std::chrono::time_point<Clock> event_time, double val);
    
    virtual void PollElementaryForce(std::chrono::time_point<Clock> event_time);
    
        //    virtual void SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val);
    
        //    virtual std::vector<double> GetPointPosition(std::chrono::time_point<Clock> event_time);

        //    virtual int GetCharge(std::chrono::time_point<Clock> event_time);
    

    double object_energy;
    double object_energy_threshold;
    int object_size;
    Universe* time_dimension_pointer; // Pointer to dimension related to time for this object
    
protected:
        // Only the member functions of the class and its descendent classes can access protected members. The class instances are denied access to protected members.
    
    
        // Vectors of child objects to enable calling and connecting objects and functions of different branches
    std::vector<Universe*> cognitive_network_list;
    std::vector<Universe*> composite_forceparticle_list;
    std::vector<Universe*> dimension_list;
    std::vector<Universe*> elementary_force_list;
    std::vector<Universe*> elementary_particle_list;
    std::vector<Universe*> matter_list;
    std::vector<Universe*> monomer_list;
    std::vector<Universe*> polymer_list;
    std::vector<Universe*> solid_list;
    std::vector<Universe*> point_list;
    
private:
        // Only the member functions of the class can access the private members. The class instances are denied access to private members.
    bool object_initialised = false;
    int duration_since_last_event;
    int default_object_type;
    int test_subject_one = 0;
    int test_subject_two = 0;
    int universe_type;                   //!< Member variable "universe_type"
    double universe_energy;              //!< Member variable "universe_energy"
    double scaled_time;                  //!< Member variable "scaled_time"
    std::chrono::time_point<Clock> time_object_created;               //!< Member variable "time_object_created"
    std::chrono::time_point<Clock> object_expiration;            //!< Member variable "object_expiration"
    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::nanoseconds object_lifespan;              //!< Member variable "object_lifespan"
};

#endif // BRAINHARMONICS_UNIVERSE_H
