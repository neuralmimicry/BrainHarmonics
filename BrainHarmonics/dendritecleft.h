//
//  dendritecleft.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_DENDRITECLEFT_H
#define BRAINHARMONICS_DENDRITECLEFT_H

#include "dendritebranch.h"

class DendriteCleft : public DendriteBranch
{
public:
    DendriteCleft() : DendriteCleft(0) {}
    
    DendriteCleft(unsigned int object_type) : DendriteCleft(object_type, std::chrono::high_resolution_clock::now()) {}
    
    DendriteCleft(unsigned int object_type, std::chrono::time_point<Clock> event_time) : DendriteBranch() {}
    
    DendriteCleft(unsigned int object_type, std::chrono::time_point<Clock> event_time, DendriteBranch& dendritebranch_connector) : DendriteBranch(dendritebranch_connector)
    {
        // Each dendritecleft type will have its own parameter ranges. The default is 0
    dendritecleft_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "DendriteCleft", dendritecleft_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~DendriteCleft() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    DendriteCleft*  CreateNeuroreceptor(std::chrono::time_point<Clock> event_time);
    
    std::vector<DendriteCleft*> CreateNeuroreceptors(std::chrono::time_point<Clock> event_time, int quantity);
    
    DendriteCleft*  CloneNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* clone_object, double perfection_membership);
    
    std::vector<DendriteCleft*> CloneNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> cloning_list, double perfection_membership);
    
    DendriteCleft*  DestroyNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* destroy_object);
    
    std::vector<DendriteCleft*> DestroyNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> destruction_list);
    
    DendriteCleft*  AddNeuroreceptor(std::chrono::time_point<Clock> event_time, DendriteCleft* add_object);
    
    std::vector<DendriteCleft*> AddNeuroreceptors(std::chrono::time_point<Clock> event_time, std::vector<DendriteCleft*> add_objects);
    
    DendriteCleft*  RemoveNeuroreceptor(std::chrono::time_point<Clock> event_time);
    
    std::vector<DendriteCleft*> RemoveNeuroreceptors(std::chrono::time_point<Clock> event_time, int quantity);
    
    DendriteCleft*  GetNeuroreceptor(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<DendriteCleft*> GetNeuroreceptors(std::chrono::time_point<Clock> event_time);
    
    int GrowthSurface(std::chrono::time_point<Clock> event_time, double surf_change);
    
    int GrowthVolume(std::chrono::time_point<Clock> event_time, double vol_change);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<DendriteCleft*> neuroreceptor_list;

private:
    int dendritecleft_type;
    int m_addStatus;
    int neuroreceptor_pool;
    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::time_point<Clock> time_object_created;
    bool object_disabled;
    bool object_initialised;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    double m_Length;
    double object_size; //!< Member variable "object_size" Area of cleft (assumed to be circular due to pressure equalisation)
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

/*
    struct s_SynapseDescription
    {
    Synapse* s_Synapse;
    double s_Distance;
    }
    std::vector<s_SynapseDescription> m_SynapseList;
 */
};

#endif // BRAINHARMONICS_DENDRITECLEFT_H
