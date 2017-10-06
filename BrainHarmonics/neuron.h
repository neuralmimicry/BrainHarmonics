    //
    //  neuron.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_NEURON_H
#define BRAINHARMONICS_NEURON_H

#include "cognitivenetwork.h"

class Neuron : public CognitiveNetwork
{
    friend class Orbital;
public:
    Neuron() : Neuron(0) {}
    
    Neuron(unsigned int object_type) : Neuron(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Neuron(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    Neuron(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each neuron type will have its own parameter ranges. The default is 0
    neuron_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Neuron", neuron_type);
    object_disabled = true;
    }

    /** Default destructor */
    virtual ~Neuron() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time)         { return neuronCounter; }
    int GetCapacity(std::chrono::time_point<Clock> event_time)         { return neuronCapacity; }
    void SetCapacity(std::chrono::time_point<Clock> event_time, int val)         { neuronCapacity = val; }
    int GetUsage(std::chrono::time_point<Clock> event_time)         { return neuronUsage; }
    void SetUsage(std::chrono::time_point<Clock> event_time, int val)         { neuronUsage = val; }

    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    double GetGateKeeper(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_GateKeeper; }
    double GetChannelMin(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ChannelMin; }
    double GetChannelMax(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ChannelMax; }
    bool GetDisabled(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_disabled; }
    int GetNeuronType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return neuron_type; }
    double GetRestingPotential(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_RestingPotential; }
    int GetNeuronDeviceTag(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Tag; }
    
    int GetSomaPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return soma_pool; }
    int SetSomaPool(std::chrono::time_point<Clock> event_time, int set_pool) { soma_pool = set_pool; }

    void SetCounter(std::chrono::time_point<Clock> event_time, int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetGateKeeper(std::chrono::time_point<Clock> event_time, double val) { m_GateKeeper = val; }
    void SetChannelMin(std::chrono::time_point<Clock> event_time, double val) { m_ChannelMin = val; }
    void SetChannelMax(std::chrono::time_point<Clock> event_time, double val) { m_ChannelMax = val; }
    void SetDisabled(std::chrono::time_point<Clock> event_time, bool val) { object_disabled = val; }
    void toggleDisabled(std::chrono::time_point<Clock> event_time) { object_disabled = !object_disabled; }
    void SetNeuronType(std::chrono::time_point<Clock> event_time, int val) { neuron_type = val; ResetParameters(event_time); }
    void SetNeuronDeviceTag(std::chrono::time_point<Clock> event_time, int val) { m_Tag = val; }
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    bool OpenGate(std::chrono::time_point<Clock> event_time, double val);
    
    Neuron*  CreateSoma(std::chrono::time_point<Clock> event_time);
    
    std::vector<Neuron*> CreateSomas(std::chrono::time_point<Clock> event_time, int quantity);
    
    Neuron*  CloneSoma(std::chrono::time_point<Clock> event_time, Neuron* clone_object, double perfection_membership);
    
    std::vector<Neuron*> CloneSomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> cloning_list, double perfection_membership);
    
    Neuron*  DestroySoma(std::chrono::time_point<Clock> event_time, Neuron* destroy_object);
    
    std::vector<Neuron*> DestroySomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> destruction_list);
    
    Neuron*  AddSoma(std::chrono::time_point<Clock> event_time, Neuron* add_object);
    
    std::vector<Neuron*> AddSomas(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> add_objects);
    
    Neuron*  RemoveSoma(std::chrono::time_point<Clock> event_time);
    
    std::vector<Neuron*> RemoveSomas(std::chrono::time_point<Clock> event_time, int quantity);
    
    Neuron*  GetSoma(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Neuron*> GetSomas(std::chrono::time_point<Clock> event_time);
    
    
    Neuron*  CreateMembrane(std::chrono::time_point<Clock> event_time);
    
    std::vector<Neuron*> CreateMembranes(std::chrono::time_point<Clock> event_time, int quantity);
    
    Neuron*  CloneMembrane(std::chrono::time_point<Clock> event_time, Neuron* clone_object, double perfection_membership);
    
    std::vector<Neuron*> CloneMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> cloning_list, double perfection_membership);
    
    Neuron*  DestroyMembrane(std::chrono::time_point<Clock> event_time, Neuron* destroy_object);
    
    std::vector<Neuron*> DestroyMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> destruction_list);
    
    Neuron*  AddMembrane(std::chrono::time_point<Clock> event_time, Neuron* add_object);
    
    std::vector<Neuron*> AddMembranes(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> add_objects);
    
    Neuron*  RemoveMembrane(std::chrono::time_point<Clock> event_time);
    
    std::vector<Neuron*> RemoveMembranes(std::chrono::time_point<Clock> event_time, int quantity);
    
    Neuron*  GetMembrane(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<Neuron*> GetMembranes(std::chrono::time_point<Clock> event_time);

    int Growth(std::chrono::time_point<Clock> event_time);
    
    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Neuron*> set_of_update_pointers, unsigned int pointer_type);
    
    void UpdateCycle2(std::chrono::time_point<Clock> event_time, std::vector<Universe*> set_of_update_pointers, unsigned int pointer_type);

    int Update(std::chrono::time_point<Clock> event_time);
    
    std::vector<Universe*> GetVisualisationList() { return visualisation_list; }
    
protected:
    std::vector<Neuron*> soma_list;
    std::vector<Neuron*> membrane_list;
    std::vector<Universe*> visualisation_list;

    struct ObjectConnection
    {
    int object_one_type;
    int object_one;
    int object_two_type;
    int object_two;
    double object_connection_strength;
    double object_connection_modifier;
    double object_two_position;
    };
    
    std::vector<ObjectConnection> object_connection_list;

private:
    int neuron_type;
    int m_Tag;
    int membrane_pool = 1;
    double object_size;
    double m_RestingPotential;
    bool object_initialised;
    bool object_disabled;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    int m_addStatus;
    int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double m_Spike; //!< Member variable "m_Spike"
    double m_GateKeeper; //!< Member variable "m_GateKeeper"
    double m_ChannelMin; //!< Member variable "m_ChannelMin"
    double m_ChannelMax; //!< Member variable "m_ChannelMax"

    double m_TimeDilation;
    double m_TimeThreshold;
    
    unsigned int neuronCounter;           //!< Member variable "elementaryParticleCounter"
    int neuronCapacity;
    int neuronUsage;
    
    int soma_pool = 1;

};

#endif /* BRAINHARMONICS_NEURON_H */
