    //
    //  AxonBouton.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 16/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_AXONBOUTON_H
#define BRAINHARMONICS_AXONBOUTON_H

#include "axonbranch.h"

class AxonBouton : public AxonBranch
{
public:
    AxonBouton() : AxonBouton(0) {}
    
    AxonBouton(unsigned int object_type) : AxonBouton(object_type, std::chrono::high_resolution_clock::now()) {}
    
    AxonBouton(unsigned int object_type, std::chrono::time_point<Clock> event_time) : AxonBranch() {}
    
    AxonBouton(unsigned int object_type, std::chrono::time_point<Clock> event_time, AxonBranch& axonbranch_connector) : AxonBranch(axonbranch_connector)
    {
        // Each axonbouton type will have its own parameter ranges. The default is 0
    axonbouton_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "AxonBouton", axonbouton_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~AxonBouton() {}
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
        //    int ConnectSynapse(std::chrono::time_point<Clock> event_time, Synapse* link_synapse, double distance);
    
    AxonBouton*  CreateSynapticVesicle(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonBouton*> CreateSynapticVesicles(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonBouton*  CloneSynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* clone_object, double perfection_membership);
    
    std::vector<AxonBouton*> CloneSynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> cloning_list, double perfection_membership);
    
    AxonBouton*  DestroySynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* destroy_object);
    
    std::vector<AxonBouton*> DestroySynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> destruction_list);
    
    AxonBouton*  AddSynapticVesicle(std::chrono::time_point<Clock> event_time, AxonBouton* add_object);
    
    std::vector<AxonBouton*> AddSynapticVesicles(std::chrono::time_point<Clock> event_time, std::vector<AxonBouton*> add_objects);
    
    AxonBouton*  RemoveSynapticVesicle(std::chrono::time_point<Clock> event_time);
    
    std::vector<AxonBouton*> RemoveSynapticVesicles(std::chrono::time_point<Clock> event_time, int quantity);
    
    AxonBouton*  GetSynapticVesicle(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<AxonBouton*> GetSynapticVesicles(std::chrono::time_point<Clock> event_time);

    int GrowthSurface(std::chrono::time_point<Clock> event_time, double surf_change);
    
    int GrowthVolume(std::chrono::time_point<Clock> event_time, double vol_change);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
    
protected:
    std::vector<AxonBouton*> synapticvesicle_list;

private:
    int axonbouton_type;
    int m_addStatus;
    int synapticvesicle_pool;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;

    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double m_axonlength;
    double m_TimeDilation;
    double m_TimeThreshold;
    bool object_disabled;
    bool object_initialised;
};

#endif // BRAINHARMONICS_AXONBOUTON_H
