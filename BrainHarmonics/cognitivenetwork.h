    //
    //  cognitivenetwork.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_COGNITIVENETWORK_H
#define BRAINHARMONICS_COGNITIVENETWORK_H

#include "dimension.h"
#include "universe.h"

class CognitiveNetwork : public Universe
{
public:
        // Object must be attached to a parent. Default constructor () not applicable.
    CognitiveNetwork() : CognitiveNetwork(0) {}
    
    CognitiveNetwork(unsigned int object_type) : CognitiveNetwork(object_type, std::chrono::high_resolution_clock::now()) {}
    
    CognitiveNetwork(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    CognitiveNetwork(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each cognitivenetwork type will have its own parameter ranges. The default is 0
    cognitivenetwork_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "CognitiveNetwork", cognitivenetwork_type);
    
    }
    
    /** Default destructor */
    virtual ~CognitiveNetwork() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time)         { return cognitivenetworkCounter; }
    int GetCapacity(std::chrono::time_point<Clock> event_time)         { return cognitivenetworkCapacity; }
    void SetCapacity(std::chrono::time_point<Clock> event_time, int val)         { cognitivenetworkCapacity = val; }
    int GetUsage(std::chrono::time_point<Clock> event_time)         { return cognitivenetworkUsage; }
    void SetUsage(std::chrono::time_point<Clock> event_time, int val)         { cognitivenetworkUsage = val; }
    
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    double GetGateKeeper(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_GateKeeper; }
    double GetChannelMin(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ChannelMin; }
    double GetChannelMax(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_ChannelMax; }
    bool GetDisabled(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_disabled; }
    int GetObjectType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return cognitivenetwork_type; }
    double GetRestingPotential(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_RestingPotential; }
    int GetCognitiveNetworkDeviceTag(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Tag; }
    
    void SetCounter(std::chrono::time_point<Clock> event_time, int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetGateKeeper(std::chrono::time_point<Clock> event_time, double val) { m_GateKeeper = val; }
    void SetChannelMin(std::chrono::time_point<Clock> event_time, double val) { m_ChannelMin = val; }
    void SetChannelMax(std::chrono::time_point<Clock> event_time, double val) { m_ChannelMax = val; }
    void SetDisabled(std::chrono::time_point<Clock> event_time, bool val) { object_disabled = val; }
    void toggleDisabled(std::chrono::time_point<Clock> event_time) { object_disabled = !object_disabled; }
    
    int GetOrbitalPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return orbital_pool; }
    int GetNeuronPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return neuron_pool; }
    int GetSynapsePool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return synapse_pool; }
    int GetNeurotransmitterPool(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return neurotransmitter_pool; }
    
    void SetOrbitalPool(std::chrono::time_point<Clock> event_time, int set_pool) { orbital_pool = set_pool; }
    void SetNeuronPool(std::chrono::time_point<Clock> event_time, int set_pool) { neuron_pool = set_pool; }
    void SetSynapsePool(std::chrono::time_point<Clock> event_time, int set_pool) { synapse_pool = set_pool; }
    void SetNeurotransmitterPool(std::chrono::time_point<Clock> event_time, int set_pool) { neurotransmitter_pool = set_pool; }

    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);
    
    void SetCognitiveNetworkDeviceTag(std::chrono::time_point<Clock> event_time, int val) { m_Tag = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> set_of_update_pointers, unsigned int pointer_type);
    
     int Update(std::chrono::time_point<Clock> event_time);
    
    
    CognitiveNetwork* CreateCognitiveInput(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateCognitiveInputs(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddCognitiveInput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddCognitiveInputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveCognitiveInput(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveCognitiveInputs(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetCognitiveInput(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetCognitiveInputs(std::chrono::time_point<Clock> event_time);
    

    CognitiveNetwork* CreateCognitiveOutput(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateCognitiveOutputs(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddCognitiveOutput(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddCognitiveOutputs(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveCognitiveOutput(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveCognitiveOutputs(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetCognitiveOutput(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetCognitiveOutputs(std::chrono::time_point<Clock> event_time);
    

    CognitiveNetwork*  CreateInterneuronSpace(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateInterneuronSpaces(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddInterneuronSpace(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddInterneuronSpaces(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveInterneuronSpace(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveInterneuronSpaces(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetInterneuronSpace(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetInterneuronSpaces(std::chrono::time_point<Clock> event_time);

    
    CognitiveNetwork*  CreateOrbital(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateOrbitals(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddOrbital(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddOrbitals(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveOrbital(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveOrbitals(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetOrbital(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetOrbitals(std::chrono::time_point<Clock> event_time);

    
    CognitiveNetwork*  CreateNeuron(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateNeurons(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroyNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroyNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddNeuron(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddNeurons(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveNeuron(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveNeurons(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetNeuron(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetNeurons(std::chrono::time_point<Clock> event_time);
    
    
    CognitiveNetwork*  CreateSynapse(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> CreateSynapses(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  CloneSynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership);
    
    std::vector<CognitiveNetwork*> CloneSynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership);
    
    CognitiveNetwork*  DestroySynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object);
    
    std::vector<CognitiveNetwork*> DestroySynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list);
    
    CognitiveNetwork*  AddSynapse(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object);
    
    std::vector<CognitiveNetwork*> AddSynapses(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects);
    
    CognitiveNetwork*  RemoveSynapse(std::chrono::time_point<Clock> event_time);
    
    std::vector<CognitiveNetwork*> RemoveSynapses(std::chrono::time_point<Clock> event_time, int quantity);
    
    CognitiveNetwork*  GetSynapse(std::chrono::time_point<Clock> event_time, int selector);
    
    std::vector<CognitiveNetwork*> GetSynapses(std::chrono::time_point<Clock> event_time);
    
    
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
    
    void SetCharge(std::chrono::time_point<Clock> event_time, int val) final {}
     void SetSpin(std::chrono::time_point<Clock> event_time, int val) final {}
     double GetGravitation(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetWeak(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetWeakElectroweak(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetElectromagnetic(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetStrong(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetStrongFundamental(std::chrono::time_point<Clock> event_time) final {return 0;}
     double GetStrongResidual(std::chrono::time_point<Clock> event_time) final {return 0;}
    
     double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyWeak(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyStrong(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
     double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) final {return 0;}
    
     void SetGravitation(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetWeak(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetStrong(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val) final {}
     void SetStrongResidual(std::chrono::time_point<Clock> event_time, double val) final {}
    
     void PollElementaryForce(std::chrono::time_point<Clock> event_time) final {}
    
        //     void SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val) final {}
    
        //     std::vector<double> GetPointPosition(std::chrono::time_point<Clock> event_time) final {}
    
        //     int GetCharge(std::chrono::time_point<Clock> event_time) final {}

protected:
    std::vector<Dimension*> dimension_list;
    std::vector<CognitiveNetwork*> cognitiveinput_list;
    std::vector<CognitiveNetwork*> cognitiveoutput_list;
    std::vector<CognitiveNetwork*> interneuronspace_list;
    std::vector<CognitiveNetwork*> orbital_list;
    std::vector<CognitiveNetwork*> neuron_list;
    std::vector<CognitiveNetwork*> synapse_list;
    std::vector<CognitiveNetwork*> neurotransmitter_list;
 
private:
    int cognitivenetwork_type;
    int m_Tag;
    double object_size;
    double m_RestingPotential;
    bool object_disabled;
    bool object_initialised;
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
    
    unsigned int cognitivenetworkCounter;           //!< Member variable "elementaryParticleCounter"
    int cognitivenetworkCapacity;
    int cognitivenetworkUsage;
    
        // How many of each components allowed in the cognitive network
    int interneuronspace_pool = 1;
    int cognitiveinput_pool = 1;
    int cognitiveoutput_pool = 1;
    int orbital_pool;
    int neuron_pool;
    int synapse_pool;
    int neurotransmitter_pool;
    
     struct OrbitalConnection
     {
     int orbital_one;
     int orbital_two;
     double orbital_connection_strength;
     double orbital_connection_modifier;
     bool orbital_spike;
     double orbital_one_position;
     double orbital_two_position;
     };
     
     std::vector<OrbitalConnection> orbital_connection_list;
    
};

#endif /* BRAINHARMONICS_COGNITIVENETWORK_H */
