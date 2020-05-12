//
//  SynapticVesicle.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_SYNAPTICVESICLE_H
#define BRAINHARMONICS_SYNAPTICVESICLE_H

#include <chrono>
#include <iostream>
#include "axonbouton.h"

class SynapticVesicle : public AxonBouton
{
public:
    SynapticVesicle() : SynapticVesicle(0) {}
    
    SynapticVesicle(unsigned int object_type) : SynapticVesicle(object_type, std::chrono::high_resolution_clock::now()) {}
    
    SynapticVesicle(unsigned int object_type, std::chrono::time_point<Clock> event_time) : AxonBouton() {}
    
    SynapticVesicle(unsigned int object_type, std::chrono::time_point<Clock> event_time, AxonBouton& axonbouton_connector) : AxonBouton(axonbouton_connector)
    {
        // Each synapticvesicle type will have its own parameter ranges. The default is 0
    synapticvesicle_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "SynapticVesicle", synapticvesicle_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~SynapticVesicle() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    int GetReleaseState(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ReleaseState; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    CognitiveNetwork*  CreateNeurotransmitter(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetNeurotransmitter(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetNeurotransmitters(std::chrono::time_point<Clock> event_time);

    int GrowthSurface(std::chrono::time_point<Clock> event_time, double surf_change);
    
    int GrowthVolume(std::chrono::time_point<Clock> event_time, double vol_change);

    void ReleaseNeurotransmitters(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<CognitiveNetwork*> neurotransmitter_list;
    
private:
    int m_NeuronType;
    int neurotransmitter_pool;
    int synapticvesicle_type;
    int m_addStatus;
    bool object_disabled;
    bool object_initialised;
    int m_ReleaseState;
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
};

#endif // BRAINHARMONICS_SYNAPTICVESICLE_H
