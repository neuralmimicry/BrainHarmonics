//
//  membrane.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_MEMBRANE_H
#define BRAINHARMONICS_MEMBRANE_H

#include <iostream>
#include <vector>
#include "neuron.h"
#include "polyhedron.h"

class Membrane : public Neuron
{
public:
    Membrane() : Membrane(0) {}
    
    Membrane(unsigned int object_type) : Membrane(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Membrane(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Neuron() {}
    
    Membrane(unsigned int object_type, std::chrono::time_point<Clock> event_time, Neuron& neuron_connector) : Neuron(neuron_connector)
    {
        // Each membrane type will have its own parameter ranges. The default is 0
    membrane_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Membrane", membrane_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Membrane() {}
    
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
    
    int GetMembraneChannelPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return membranechannel_pool; }
    int SetMembraneChannelPool(std::chrono::time_point<Clock> event_time, int set_pool) { membranechannel_pool = set_pool; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetEnergyInc(std::chrono::time_point<Clock> event_time, double val) { object_energyInc = val; }
    void SetEnergyDec(std::chrono::time_point<Clock> event_time, double val) { object_energyDec = val; }
    void SetEnergyLeak(std::chrono::time_point<Clock> event_time, double val) { object_energyLeak = val; }
    void SetEnergyThreshold(std::chrono::time_point<Clock> event_time, double val) { object_energy_threshold = val; }
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    Membrane*  CreateMembraneChannel(std::chrono::time_point<Clock> event_time);
    
    std::vector<Membrane*> CreateMembraneChannels(std::chrono::time_point<Clock> event_time, int quantity);
    
    Membrane*  CloneMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* clone_object, double perfection_membership);
    
    std::vector<Membrane*> CloneMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> cloning_list, double perfection_membership);
    
    Membrane*  DestroyMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* destroy_object);
    
    std::vector<Membrane*> DestroyMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> destruction_list);
    
    Membrane*  AddMembraneChannel(std::chrono::time_point<Clock> event_time, Membrane* add_object);
    
    std::vector<Membrane*> AddMembraneChannels(std::chrono::time_point<Clock> event_time, std::vector<Membrane*> add_objects);
    
    Membrane*  RemoveMembraneChannel(std::chrono::time_point<Clock> event_time);
    
    std::vector<Membrane*> RemoveMembraneChannels(std::chrono::time_point<Clock> event_time, int quantity);
    
    Membrane*  GetMembraneChannel(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Membrane*> GetMembraneChannels(std::chrono::time_point<Clock> event_time);
    
    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<Membrane*> membranechannel_list;
    std::vector<Solid*> visualisation_list;

private:
    int m_NeuronType;
    int membrane_type;
    int m_addStatus;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_disabled;
    bool object_initialised;
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
    
    int membranechannel_pool;
};

#endif // BRAINHARMONICS_MEMBRANE_H
