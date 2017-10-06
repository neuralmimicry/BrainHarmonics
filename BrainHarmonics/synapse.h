    //
    //  synapse.h
    //  BrainHarmonics
    //
    //**  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_SYNAPSE_H
#define BRAINHARMONICS_SYNAPSE_H

    //#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include "cognitivenetwork.h"

class Synapse : public CognitiveNetwork
{
public:
    Synapse() : Synapse(0) {}
    
    Synapse(unsigned int object_type) : Synapse(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Synapse(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    Synapse(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each synapse type will have its own parameter ranges. The default is 0
    synapse_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    object_initialised = ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Synapse", synapse_type);
    object_disabled = true;
    }
    
    /** Default destructor */
    virtual ~Synapse() {}
    
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    int GetTauCyclesAdd(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_TauCyclesAdd; }
    int GetTauCyclesDecay(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_TauCyclesDecay; }
    int GetChargeType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ChargeType; }
    int GetDischargeType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_DischargeType; }
    int GetSynapseDeviceTag(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Tag; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetTauCyclesAdd(std::chrono::time_point<Clock> event_time, int val) { m_TauCyclesAdd = val; }
    void SetTauCyclesDecay(std::chrono::time_point<Clock> event_time, int val) { m_TauCyclesDecay = val; }
    void SetChargeType(std::chrono::time_point<Clock> event_time, int val) { m_ChargeType = val; }
    void SetDischargeType(std::chrono::time_point<Clock> event_time, int val) { m_DischargeType = val; }

    void SetSynapseDeviceTag(std::chrono::time_point<Clock> event_time, int val) { m_Tag = val; }
    
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

    int GetDemand(std::chrono::time_point<Clock> event_time);
    
    double GetDistance(std::chrono::time_point<Clock> event_time, int val);
    
    int GetAllocatedSynapse(std::chrono::time_point<Clock> event_time);
    
    double GetMinimumDistance(std::chrono::time_point<Clock> event_time);
    
    void GetSynapseList(std::chrono::time_point<Clock> event_time);
    
    void SetDemand(std::chrono::time_point<Clock> event_time, int val);
    
    void SetNeuron(std::chrono::time_point<Clock> event_time, int val);
    
        //    void AddDistance(Neuron *synapse, double val);
        
    /*
     int AddSynapse(std::vector<Synapse> *toAddto, std::vector<CognitiveNetwork> *aPartof, int arrayEntry);
     */
    

    void SendBareSpike(std::chrono::time_point<Clock> event_time);
    
    void SendTransmitterSpike(std::chrono::time_point<Clock> event_time);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<CognitiveNetwork*> neurotransmitter_list;

private:
    int synapse_type;
    double object_size;
    double object_energy;
    double object_energy_threshold;
    int m_NeuronType;
    int neurotransmitter_pool;
    int m_Tag;
    int m_addStatus;
    int m_TauCyclesAdd;
    int m_TauCyclesDecay;
    int m_ChargeType;
    int m_DischargeType;
    bool object_disabled;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_axonlength;
    double m_TimeDilation;
    double m_TimeThreshold;
    bool object_initialised = false;

    double m_ReduceBy;
    double m_ReducedBy;
    
    struct s_BindList
    {
        //    Neurotransmitter* neurotransmitter;
        //    Neuroreceptor* neuroreceptor;
    };
    
    std::vector<s_BindList> m_BindList;
    
    
    int synapseCounter;           //!< Member variable "synapseCounter"
    int synapseDemand;
    double minimumDistance;
    
    struct NearbyNeuron
    {
        // Neuron* nearbyNeuron;
    double distanceToNeuron;
    double synapseGravitationalAttraction;
    bool synapseAllocated;
    };
    
    std::vector<NearbyNeuron> neuronList;
    std::vector<NearbyNeuron>::iterator it;

    
};

#endif // BRAINHARMONICS_SYNAPSE_H
