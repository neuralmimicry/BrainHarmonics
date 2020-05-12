    //
    //  soma.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_SOMA_H
#define BRAINHARMONICS_SOMA_H

#include "neuron.h"
#include "polyhedron.h"

class Soma : public Neuron
{
    friend class Dimension;
    
public:
    Soma() : Soma(0) {}
    
    Soma(unsigned int object_type) : Soma(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Soma(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Neuron() {}
    
    Soma(unsigned int object_type, std::chrono::time_point<Clock> event_time, Neuron& neuron_connector) : Neuron(neuron_connector)
    {
        // Each soma type will have its own parameter ranges. The default is 0
    parent_pointer = &neuron_connector;
    soma_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Soma", soma_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Soma() {}
    
        // Unit of time resolution is 1ns.
        // Any single network function should have an output within 25ms
        // For simulation a 25ms function should complete in 25 seconds. A factor of 1000 dilation.
    double TimeFunction(double timeDelay, double timeDilation)
    {
    double timeCounter;
    timeCounter = timeDelay * timeDilation;
    return timeCounter;
    }
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    double GetEnergyInc(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energyInc; }
    double GetEnergyDec(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energyDec; }
    double GetEnergyLeak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energyLeak; }
    double GetEnergyThreshold(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy_threshold; }

    int GetAxonHillockPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return axonhillock_pool; }
    void SetAxonHillockPool(std::chrono::time_point<Clock> event_time, int set_pool) { axonhillock_pool = set_pool; }

    int GetDendritePool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return dendrite_pool; }
    void SetDendritePool(std::chrono::time_point<Clock> event_time, int set_pool) { dendrite_pool = set_pool; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetEnergyInc(std::chrono::time_point<Clock> event_time, double val) { object_energyInc = val; }
    void SetEnergyDec(std::chrono::time_point<Clock> event_time, double val) { object_energyDec = val; }
    void SetEnergyLeak(std::chrono::time_point<Clock> event_time, double val) { object_energyLeak = val; }
    void SetEnergyThreshold(std::chrono::time_point<Clock> event_time, double val) { object_energy_threshold = val; }
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    Soma*  CreateAxonHillock(std::chrono::time_point<Clock> event_time);
    
    std::vector<Soma*> CreateAxonHillocks(std::chrono::time_point<Clock> event_time, int quantity);
    
    Soma*  CloneAxonHillock(std::chrono::time_point<Clock> event_time, Soma* clone_object, double perfection_membership);
    
    std::vector<Soma*> CloneAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> cloning_list, double perfection_membership);
    
    Soma*  DestroyAxonHillock(std::chrono::time_point<Clock> event_time, Soma* destroy_object);
    
    std::vector<Soma*> DestroyAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> destruction_list);
    
    Soma*  AddAxonHillock(std::chrono::time_point<Clock> event_time, Soma* add_object);
    
    std::vector<Soma*> AddAxonHillocks(std::chrono::time_point<Clock> event_time, std::vector<Soma*> add_objects);
    
    Soma*  RemoveAxonHillock(std::chrono::time_point<Clock> event_time);
    
    std::vector<Soma*> RemoveAxonHillocks(std::chrono::time_point<Clock> event_time, int quantity);
    
    Soma*  GetAxonHillock(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Soma*> GetAxonHillocks(std::chrono::time_point<Clock> event_time);
    
    Soma*  CreateDendrite(std::chrono::time_point<Clock> event_time);
    
    std::vector<Soma*> CreateDendrites(std::chrono::time_point<Clock> event_time, int quantity);
    
    Soma*  CloneDendrite(std::chrono::time_point<Clock> event_time, Soma* clone_object, double perfection_membership);
    
    std::vector<Soma*> CloneDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> cloning_list, double perfection_membership);
    
    Soma*  DestroyDendrite(std::chrono::time_point<Clock> event_time, Soma* destroy_object);
    
    std::vector<Soma*> DestroyDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> destruction_list);
    
    Soma*  AddDendrite(std::chrono::time_point<Clock> event_time, Soma* add_object);
    
    std::vector<Soma*> AddDendrites(std::chrono::time_point<Clock> event_time, std::vector<Soma*> add_objects);
    
    Soma*  RemoveDendrite(std::chrono::time_point<Clock> event_time);
    
    std::vector<Soma*> RemoveDendrites(std::chrono::time_point<Clock> event_time, int quantity);
    
    Soma*  GetDendrite(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Soma*> GetDendrites(std::chrono::time_point<Clock> event_time);
    
    int Growth(std::chrono::time_point<Clock> event_time);

    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<Soma*> axonhillock_list;
    std::vector<Soma*> dendrite_list;
        //std::vector<Solid*> visualisation_list;

    struct ObjectConnection
    {
    int object_one_type;
    int object_one;
    int object_two_type;
    int object_two;
    double object_connection_strength;
    double object_connection_modifier;
    double object_two_position;
    };
    
    std::vector<ObjectConnection> object_connection_list;
    
private:
    Neuron* parent_pointer;
    int m_NeuronType;
    int soma_type;
    int m_addStatus;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_disabled = true;
    bool object_initialised = false;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    double object_size;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energyInc;
    double object_energyDec;
    double object_energyLeak;
    double object_energy_threshold;
    double m_TimeDilation;
    double m_TimeThreshold;

    int axonhillock_pool;
    int dendrite_pool;
    
};

#endif // BRAINHARMONICS_SOMA_H
