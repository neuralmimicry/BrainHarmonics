    //
    //  neuroreceptor.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 03/02/16.
    //  Copyright © 2016 Paul Isaac's. All rights reserved.
    //
    // The Energy level used in this function only enables the receptor to activate.
    // It does not necessarily mean that a spike will flow through. It depends what
    // is waiting in the void beyond the membrane.
    //
    // Metabotropic Receptors and Ionotropic Receptor are possibilities
    // The type of receptor can be defined by dimension connection or stated
    // as an integer type.
    //
    // Metabotropic
    // 1: Receptive to GABA neurotransmitters
    // 2:
    // Ionotropic
    // 3: Cys-loop
    // 4: Glutamate receptor
    // 5: ATP-gated

    // Type-3 Serotonin receptor (5HT3-R)

#ifndef BRAINHARMONICS_NEURORECEPTOR_H
#define BRAINHARMONICS_NEURORECEPTOR_H

#include "dendritecleft.h"

class Neuroreceptor : public DendriteCleft
{
public:
    Neuroreceptor() : Neuroreceptor(0) {}
    
    Neuroreceptor(unsigned int object_type) : Neuroreceptor(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Neuroreceptor(unsigned int object_type, std::chrono::time_point<Clock> event_time) : DendriteCleft() {}
    
    Neuroreceptor(unsigned int object_type, std::chrono::time_point<Clock> event_time, DendriteCleft& dendritecleft_connector) : DendriteCleft(dendritecleft_connector)
    {
        // Each neuroreceptor type will have its own parameter ranges. The default is 0
    neuroreceptor_type = object_type;
    time_object_created = event_time;
    
        // Call to announce object creation
    Creation(time_object_created, "Neuroreceptor", neuroreceptor_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Neuroreceptor() {}

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    bool GetReceptorBindingState(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_boundReceptor; }
    int GetReceptorType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_typeReceptor; }
    bool GetDisabled(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_disabled; }
    int GetIons(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Ions; }
    
    void SetReceptorBindingState(std::chrono::time_point<Clock> event_time, bool val) { m_boundReceptor = val; if (m_boundReceptor) { object_energy = object_energyFull; } }
    void ToggleReceptorBindingState(std::chrono::time_point<Clock> event_time) { m_boundReceptor = !m_boundReceptor; }
    void ToggleDisabled(std::chrono::time_point<Clock> event_time) { object_disabled = !object_disabled; SetReceptorBindingState(event_time, false); }
    void SetDisabled(std::chrono::time_point<Clock> event_time, bool val) { object_disabled = val; SetReceptorBindingState(event_time, false); }
    void SetReceptorType(std::chrono::time_point<Clock> event_time, int val) { m_typeReceptor = val; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetIons(std::chrono::time_point<Clock> event_time, int val) { m_Ions = val; }
    
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

    bool CompatibilityCheck(std::chrono::time_point<Clock> event_time, int neurotransmitterType);
    
    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<CognitiveNetwork*> neurotransmitter_list;

private:
    int m_NeuronType;
    int neuroreceptor_type;
    int neurotransmitter_pool;
    int m_addStatus;
    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::time_point<Clock> time_object_created;
    int duration_since_last_event;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double m_TimeDilation;
    double m_TimeThreshold;

    double m_Length;
    bool object_initialised = false;
    bool object_disabled;
    double object_size = 0;
    double object_energyFull;
    int m_Ions;
    bool m_boundReceptor; //!< Member variable "m_boundReceptor"
    int m_typeReceptor; //!< Member variable "m_typeReceptor"

};

#endif // BRAINHARMONICS_NEURORECEPTOR_H
