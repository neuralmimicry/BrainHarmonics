    //
    //  axonhillock.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_AXONHILLOCK_H
#define BRAINHARMONICS_AXONHILLOCK_H

    //#include <algorithm>
#include "soma.h"

class AxonHillock : public Soma
{
public:
    AxonHillock() : AxonHillock(0) {}
    
    AxonHillock(unsigned int object_type) : AxonHillock(object_type, std::chrono::high_resolution_clock::now()) {}
    
    AxonHillock(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Soma() {}
    
    AxonHillock(unsigned int object_type, std::chrono::time_point<Clock> event_time, Soma& soma_connector) : Soma(soma_connector)
    {
        // Each axonhillock type will have its own parameter ranges. The default is 0
    axonhillock_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "AxonHillock", axonhillock_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~AxonHillock() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    AxonHillock*  CreateAxon(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonHillock*> CreateAxons(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonHillock*  CloneAxon(std::chrono::time_point<Clock> event_time, AxonHillock* clone_object, double perfection_membership);
    
    std::vector<AxonHillock*> CloneAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> cloning_list, double perfection_membership);
    
    AxonHillock*  DestroyAxon(std::chrono::time_point<Clock> event_time, AxonHillock* destroy_object);
    
    std::vector<AxonHillock*> DestroyAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> destruction_list);
    
    AxonHillock*  AddAxon(std::chrono::time_point<Clock> event_time, AxonHillock* add_object);
    
    std::vector<AxonHillock*> AddAxons(std::chrono::time_point<Clock> event_time, std::vector<AxonHillock*> add_objects);
    
    AxonHillock*  RemoveAxon(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonHillock*> RemoveAxons(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonHillock*  GetAxon(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<AxonHillock*> GetAxons(std::chrono::time_point<Clock> event_time);
    
    int Growth(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<AxonHillock*> axon_list;

private:
    int m_NeuronType;
    int axonhillock_type;
    bool object_disabled;
    bool object_initialised;
    int axon_pool;
    double m_Volume;
    double m_SurfaceArea;
    int m_addStatus;
    double object_size;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;

    int duration_since_last_event;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double m_TimeDilation;
    double m_TimeThreshold;

};

#endif // BRAINHARMONICS_AXONHILLOCK_H
