    //
    //  axon.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_AXON_H
#define BRAINHARMONICS_AXON_H

#include "axonhillock.h"

class Axon : public AxonHillock
{
public:
    Axon() : Axon(0) {}
    
    Axon(unsigned int object_type) : Axon(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Axon(unsigned int object_type, std::chrono::time_point<Clock> event_time) : AxonHillock() {}
    
    Axon(unsigned int object_type, std::chrono::time_point<Clock> event_time, AxonHillock& axonhillock_connector) : AxonHillock(axonhillock_connector)
    {
        // Each axon type will have its own parameter ranges. The default is 0
    axon_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Axon", axon_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Axon() {}
    /** Access m_Counter
     * \return The current value of m_Counter
     */
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    Axon*  CreateAxonBranch(std::chrono::time_point<Clock> event_time);
    
    std::vector<Axon*> CreateAxonBranches(std::chrono::time_point<Clock> event_time, int quantity);
    
    Axon*  CloneAxonBranch(std::chrono::time_point<Clock> event_time, Axon* clone_object, double perfection_membership);
    
    std::vector<Axon*> CloneAxonBranches(std::chrono::time_point<Clock> event_time, std::vector<Axon*> cloning_list, double perfection_membership);
    
    Axon*  DestroyAxonBranch(std::chrono::time_point<Clock> event_time, Axon* destroy_object);
    
    std::vector<Axon*> DestroyAxonBranches(std::chrono::time_point<Clock> event_time, std::vector<Axon*> destruction_list);
    
    Axon*  AddAxonBranch(std::chrono::time_point<Clock> event_time, Axon* add_object);
    
    std::vector<Axon*> AddAxonBranches(std::chrono::time_point<Clock> event_time, std::vector<Axon*> add_objects);
    
    Axon*  RemoveAxonBranch(std::chrono::time_point<Clock> event_time);
    
    std::vector<Axon*> RemoveAxonBranches(std::chrono::time_point<Clock> event_time, int quantity);
    
    Axon*  GetAxonBranch(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Axon*> GetAxonBranches(std::chrono::time_point<Clock> event_time);
    
    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<Axon*> axonbranch_list;

private:
    int axon_type;
    int m_addStatus;
    int axonbranch_pool;
    bool object_disabled;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_initialised = false;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    double object_size;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double m_axonlength;
    double m_TimeDilation;
    double m_TimeThreshold;

};

#endif // BRAINHARMONICS_AXON_H
