    //
    //  dendrite.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_DENDRITE_H
#define BRAINHARMONICS_DENDRITE_H

#include "soma.h"

class Dendrite : public Soma
{
public:
    Dendrite() : Dendrite(0) {}
    
    Dendrite(unsigned int object_type) : Dendrite(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Dendrite(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Soma() {}
    
    Dendrite(unsigned int object_type, std::chrono::time_point<Clock> event_time, Soma& soma_connector) : Soma(soma_connector)
    {
        // Each dendrite type will have its own parameter ranges. The default is 0
    dendrite_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Dendrite", dendrite_type);
    object_disabled = true;
    }

    /** Default destructor */
    virtual ~Dendrite() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    double GetDendriteLength(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_dendriteLength; }
    double GetDendriteDiameterStart(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_dendriteDiameterStart; }
    double GetDendriteDiameterEnd(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_dendriteDiameterEnd; }
    double GetMembraneResistance(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_membraneResistance; }
    double GetMembraneCapacitance(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_membraneCapacitance; }
    double GetInternalResistance(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_internalResistance; }
    double GetPropagationVelocity(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return ( ( 1 / m_membraneCapacitance ) * sqrt((m_dendriteLength / ( 4 * m_membraneResistance * m_internalResistance ) ) ) ); }
    

    void setDendriteLength(std::chrono::time_point<Clock> event_time, double val) { m_dendriteLength = val; }
    void setDendriteDiameterStart(std::chrono::time_point<Clock> event_time, double val) { m_dendriteDiameterStart = val; }
    void setDendriteDiameterEnd(std::chrono::time_point<Clock> event_time, double val) { m_dendriteDiameterEnd = val; }
    void setMembraneResistance(std::chrono::time_point<Clock> event_time, double val) { m_membraneResistance = val; }
    void setMembraneCapacitance(std::chrono::time_point<Clock> event_time, double val) { m_membraneCapacitance = val; }
    void setInternalResistance(std::chrono::time_point<Clock> event_time, double val) { m_internalResistance = val; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
        
    Dendrite*  CreateDendriteBranch(std::chrono::time_point<Clock> event_time);
    
    std::vector<Dendrite*> CreateDendriteBranches(std::chrono::time_point<Clock> event_time, int quantity);
    
    Dendrite*  CloneDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* clone_object, double perfection_membership);
    
    std::vector<Dendrite*> CloneDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> cloning_list, double perfection_membership);
    
    Dendrite*  DestroyDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* destroy_object);
    
    std::vector<Dendrite*> DestroyDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> destruction_list);
    
    Dendrite*  AddDendriteBranch(std::chrono::time_point<Clock> event_time, Dendrite* add_object);
    
    std::vector<Dendrite*> AddDendriteBranches(std::chrono::time_point<Clock> event_time, std::vector<Dendrite*> add_objects);
    
    Dendrite*  RemoveDendriteBranch(std::chrono::time_point<Clock> event_time);
    
    std::vector<Dendrite*> RemoveDendriteBranches(std::chrono::time_point<Clock> event_time, int quantity);
    
    Dendrite*  GetDendriteBranch(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Dendrite*> GetDendriteBranches(std::chrono::time_point<Clock> event_time);

    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<Dendrite*> dendritebranch_list;

private:
    int m_NeuronType;
    int dendrite_type;
    bool object_disabled;
    bool object_initialised;
    int m_addStatus;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int dendritebranch_pool;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    double m_Length;
    double object_size;
    double m_dendriteLength;  //!< Member variable "m_dendriteLength"
    double m_dendriteDiameterStart;  //!< Member variable "m_dendriteDiameterStart"
    double m_dendriteDiameterEnd;  //!< Member variable "m_dendriteDiameterEnd"
    double m_membraneResistance;
    double m_membraneCapacitance;
    double m_internalResistance;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energyInc;
    double object_energyDec;
    double object_energyLeak;
    double object_energy_threshold;
    double m_TimeDilation;
    double m_TimeThreshold;
    
    
};

#endif // BRAINHARMONICS_DENDRITE_H
