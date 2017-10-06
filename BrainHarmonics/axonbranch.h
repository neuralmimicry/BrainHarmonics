    //
    //  AxonBranch.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 16/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_AXONBRANCH_H
#define BRAINHARMONICS_AXONBRANCH_H

#include "axon.h"

class AxonBranch : public Axon
{
public:
    AxonBranch() : AxonBranch(0) {}
    
    AxonBranch(unsigned int object_type) : AxonBranch(object_type, std::chrono::high_resolution_clock::now()) {}
    
    AxonBranch(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Axon() {}
    
    AxonBranch(unsigned int object_type, std::chrono::time_point<Clock> event_time, Axon& axon_connector) : Axon(axon_connector)
    {
        // Each axonbranch type will have its own parameter ranges. The default is 0
    axonbranch_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "AxonBranch", axonbranch_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~AxonBranch() {}
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    AxonBranch*  CreateAxonBouton(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonBranch*> CreateAxonBoutons(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonBranch*  CloneAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* clone_object, double perfection_membership);
    
    std::vector<AxonBranch*> CloneAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> cloning_list, double perfection_membership);
    
    AxonBranch*  DestroyAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* destroy_object);
    
    std::vector<AxonBranch*> DestroyAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> destruction_list);
    
    AxonBranch*  AddAxonBouton(std::chrono::time_point<Clock> event_time, AxonBranch* add_object);
    
    std::vector<AxonBranch*> AddAxonBoutons(std::chrono::time_point<Clock> event_time, std::vector<AxonBranch*> add_objects);
    
    AxonBranch*  RemoveAxonBouton(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonBranch*> RemoveAxonBoutons(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonBranch*  GetAxonBouton(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<AxonBranch*> GetAxonBoutons(std::chrono::time_point<Clock> event_time);

    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> val);
    
protected:
    std::vector<AxonBranch*> axonbouton_list;

private:
    int axonbranch_type;
    int m_addStatus;
    int axonbouton_pool;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;

    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double m_TimeDilation;
    double m_TimeThreshold;
    double object_size;
    bool object_disabled;
    bool object_initialised;
    double object_energy_threshold;
    

};

#endif // BRAINHARMONICS_AXONBRANCH_H
