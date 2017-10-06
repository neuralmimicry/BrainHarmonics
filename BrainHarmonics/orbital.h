    //
    //  orbital.h
    //  BrainHarmonics
    //
    //  Created by Paul Isaac's on 17/03/17.
    //  Copyright © 2017 Paul Isaac's. All rights reserved.
    //

#ifndef BRAINHARMONICS_ORBITAL_H
#define BRAINHARMONICS_ORBITAL_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <math.h>               /**< For Sine, Cosine, Power, Fabs & Sqrt functions*/
#include <string>
#include <vector>
#include "cognitivenetwork.h"

class Orbital : public CognitiveNetwork
{
    friend class Neuron;
public:
    Orbital() : Orbital(0) {}
    
    Orbital(unsigned int object_type) : Orbital(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Orbital(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    Orbital(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each orbital type will have its own parameter ranges. The default is 0
    orbital_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Orbital", orbital_type);
    object_disabled = true;
    }
    virtual ~Orbital() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }
    double GetPosition(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Position; }
    double GetPhase(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Phase; }
    double GetTau(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Tau; }
    
    void SetPosition(std::chrono::time_point<Clock> event_time, double val) { m_Position = val; }
    void SetPhase(std::chrono::time_point<Clock> event_time, double val) { m_Phase = val; }
    void SetTau(std::chrono::time_point<Clock> event_time, double val) { m_Tau = val; }
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }
    void SetObjectType(std::chrono::time_point<Clock> event_time, int object_type);
    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    std::vector<CognitiveNetwork*> AddToNeuronList(CognitiveNetwork* neuron_pointer);
    
    std::vector<CognitiveNetwork*> AddNeuron(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> list_to_add);
    
    std::vector<CognitiveNetwork*> GetNeurons(std::chrono::time_point<Clock> event_time);

    void CalcPosition(std::chrono::time_point<Clock> event_time, double Duration);

    void UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> set_of_update_pointers, unsigned int pointer_type);
    
    virtual int Update(std::chrono::time_point<Clock> event_time);
        
protected:
    std::vector<CognitiveNetwork*> neuron_list;
    
private:
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy;
    int orbital_type;
    int m_Tau;
    double m_Position;
    double m_Phase;
    int m_Duration;
    int m_InternalClock;
    std::chrono::time_point<Clock> m_OldClock;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    bool object_disabled;
    bool object_initialised = false;
};


#endif // BRAINHARMONICS_ORBITAL_H
