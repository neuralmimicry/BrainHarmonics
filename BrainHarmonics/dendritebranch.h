//
//  dendritebranch.h (Dendrite spines are considered small branches)
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_DENDRITEBRANCH_H
#define BRAINHARMONICS_DENDRITEBRANCH_H

#include "dendrite.h"

class DendriteBranch : public Dendrite
{
public:
    DendriteBranch() : DendriteBranch(0) {}
    
    DendriteBranch(unsigned int object_type) : DendriteBranch(object_type, std::chrono::high_resolution_clock::now()) {}
    
    DendriteBranch(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Dendrite() {}
    
    DendriteBranch(unsigned int object_type, std::chrono::time_point<Clock> event_time, Dendrite& dendrite_connector) : Dendrite(dendrite_connector)
    {
        // Each dendritebranch type will have its own parameter ranges. The default is 0
    dendritebranch_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "DendriteBranch", dendritebranch_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~DendriteBranch() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    DendriteBranch*  CreateDendriteCleft(std::chrono::time_point<Clock> event_time);
    
    std::vector<DendriteBranch*> CreateDendriteClefts(std::chrono::time_point<Clock> event_time, int quantity);
    
    DendriteBranch*  CloneDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* clone_object, double perfection_membership);
    
    std::vector<DendriteBranch*> CloneDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> cloning_list, double perfection_membership);
    
    DendriteBranch*  DestroyDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* destroy_object);
    
    std::vector<DendriteBranch*> DestroyDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> destruction_list);
    
    DendriteBranch*  AddDendriteCleft(std::chrono::time_point<Clock> event_time, DendriteBranch* add_object);
    
    std::vector<DendriteBranch*> AddDendriteClefts(std::chrono::time_point<Clock> event_time, std::vector<DendriteBranch*> add_objects);
    
    DendriteBranch*  RemoveDendriteCleft(std::chrono::time_point<Clock> event_time);
    
    std::vector<DendriteBranch*> RemoveDendriteClefts(std::chrono::time_point<Clock> event_time, int quantity);
    
    DendriteBranch*  GetDendriteCleft(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<DendriteBranch*> GetDendriteClefts(std::chrono::time_point<Clock> event_time);
    
    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<DendriteBranch*> dendritecleft_list;

private:
    int m_DendriteBranchType;
    int dendritebranch_type;
    int m_addStatus;
    int dendritecleft_pool;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
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
    bool object_disabled;
    bool object_initialised;

};

#endif // BRAINHARMONICS_DENDRITEBRANCH_H
