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
#include "polymer.h"
#include "neurotransmitter.h"
#include "neuroreceptor.h"
typedef std::chrono::high_resolution_clock Clock;

class Synapse : Polymer
{
public:
    Synapse()
    {
    Synapse(GetTime(), *new Polymer());
    }
    
    Synapse(std::chrono::time_point<Clock> eventTime)
    {
    Synapse(eventTime, *new Polymer());
    }
    
    Synapse(const Polymer& p) : Polymer(p)
    {
    Synapse(GetTime(), p);
    }
    
    Synapse(std::chrono::time_point<Clock> eventTime, const Polymer& p) : Polymer(p)
    {
    ResetParameters(eventTime);
    }
    /** Default destructor */
    virtual ~Synapse() {};
    
    unsigned int GetCounter() { return m_Counter; }
    double GetEnergy() { return m_Energy; }
    int GetTauCyclesAdd() { return m_TauCyclesAdd; }
    int GetTauCyclesDecay() { return m_TauCyclesDecay; }
    int GetChargeType() { return m_ChargeType; }
    int GetDischargeType() { return m_DischargeType; }
    int GetSynapseDeviceTag() { return m_Tag; }
    
    void AddEnergy(std::chrono::time_point<Clock> eventTime, double val)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, val, m_TauCyclesAdd, m_ChargeType);     // Add energy
    add_TemporalAdjustment(eventTime, &m_Energy, -val, m_TauCyclesDecay, m_DischargeType);   // Decay energy
    }
    double GrabEnergy(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    add_TemporalAdjustment(eventTime, &m_Energy, -m_Energy, m_TauCyclesAdd, m_DischargeType);     // Grab energy
    return m_Energy;
    }
    void SetCounter(unsigned int val) { m_Counter = val; }
    void SetEnergy(double val) { m_Energy = val; }
    void SetTauCyclesAdd(int val) { m_TauCyclesAdd = val; }
    void SetTauCyclesDecay(int val) { m_TauCyclesDecay = val; }
    void SetChargeType(int val) { m_ChargeType = val; }
    void SetDischargeType(int val) { m_DischargeType = val; }
    void Creation() {std::cout << "Synapse created." << std::endl; }
    void SetSynapseDeviceTag(int val) { m_Tag = val; }
    
    void resetParameters(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Counter = 0;
    m_Energy = 0;
    m_TauCyclesAdd = 100; // Time frame that it takes for a value to be added (avoiding instantaneous addition)
    m_TauCyclesDecay = 1000; // Time frame that it takes for a value to decay
    m_ChargeType = 0;
    m_DischargeType = 1;
    synapseDemand = 0;                   /** set initial type value              */
    }
    
    int getDemand() { return synapseDemand; }
    
    double getDistance(int val) { return (double)neuronList[val].distanceToNeuron; }
    
    int getAllocatedNeuron() { synapseCounter = 0;
        for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
            if((*it).synapseAllocated == false) synapseCounter++; else break;
        }
        return synapseCounter;
    }
    
    double getMinimumDistance() { minimumDistance = 1000;
        for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
            if((*it).distanceToNeuron != 0 && (*it).distanceToNeuron < minimumDistance) minimumDistance = (*it).distanceToNeuron;
        }
        return minimumDistance;
    }
    
    void getNeuronList() {
        for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
            std::cout << (*it).distanceToNeuron << std::endl;
        }
    }
    
    void setDemand(int val) { synapseDemand = val; }
    
    void setNeuron(int val) { neuronList[val].synapseAllocated = true; }
    
    void addDistance(Neuron *neuron, double val)
    {
    NearbyNeuron addNeuron;
    addNeuron.nearbyNeuron = neuron;
    addNeuron.distanceToNeuron = val;
        // Add 0.001 to avoid divide by zero
    addNeuron.synapseGravitationalAttraction = synapseDemand / ( (val + 0.001) * (val + 0.001) );
    addNeuron.synapseAllocated = false;
    neuronList.push_back(addNeuron);
    }
    
    void creation() { }
    
    unsigned int getCounter()         { return synapseCounter; }
    
    /*
     int add_ElementaryParticle(std::vector<ElementaryParticle> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
     {
     ElementaryParticle myElementaryParticle((*aPartof)[arrayEntry]);
     // Use move not push_back otherwise data is destroyed on exiting function
     std::copy(&myElementaryParticle, &myElementaryParticle + 1, std::back_inserter(*toAddto));
     
     return 0;
     }
     */
    

    void SendBareSpike(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    m_Energy += 1000;
    }
    
    int add_Neurotransmitter(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, Neurotransmitter *val)
    {
    m_NeurotransmitterList.push_back(*val);
    return 0;
    }
    
    int create_Neurotransmitter(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    Neurotransmitter myNeurotransmitter(eventTime);
    add_Neurotransmitter(eventTime, &myNeurotransmitter);
    return 0;
    }
    
    int remove_Neurotransmitter(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, Neurotransmitter *val)
    {
        //m_NeurotransmitterList.erase(std::remove(m_NeurotransmitterList.begin(), m_NeurotransmitterList.end(), *val), m_NeurotransmitterList.end());
    return 0;
    }
    
    void SendTransmitterSpike(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    for (int nloop = 0; nloop < 100; nloop++)
        {
        create_Neurotransmitter(eventTime);
        }
    SendBareSpike(eventTime);
    }
    
    int add_Neuroreceptor(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, Neuroreceptor *val)
    {
    m_NeuroreceptorList.push_back(*val);
    return 0;
    }
    
    int remove_Neuroreceptor(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime, Neuroreceptor *val)
    {
        //m_NeuroreceptorList.erase(std::remove(m_NeuroreceptorList.begin(), m_NeuroreceptorList.end(), *val), m_NeuroreceptorList.end());
    return 0;
    }
    
    int Update(std::chrono::time_point<std::chrono::high_resolution_clock> eventTime)
    {
    bool bindingFound;
    adjust_Counters(eventTime);
    
    for(std::vector<Neurotransmitter>::iterator it = m_NeurotransmitterList.begin(); it != m_NeurotransmitterList.end(); ++it)
        {
        it->Update(eventTime);
        }
    
    if (m_Energy > 0)
        {
        for(std::vector<Neurotransmitter>::iterator it = m_NeurotransmitterList.begin(); it != m_NeurotransmitterList.end(); ++it)
            {
            add_TemporalAdjustment(eventTime, &m_Energy, (0-m_Energy)/m_NeurotransmitterList.size(), 100, 1);   // redistribute energy
            it->AddEnergy(eventTime, m_Energy/m_NeurotransmitterList.size());
            }
        }
    
    m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(eventTime - m_oldClock).count();
    if (m_duration < 0)
        {
        m_duration = 0;
        }
    if (m_duration > 1000)
        {
        for(std::vector<Neuroreceptor>::iterator it_receptor = m_NeuroreceptorList.begin(); it_receptor != m_NeuroreceptorList.end(); ++it_receptor)
            {
            bindingFound = false;
            for(std::vector<s_BindList>::iterator it_bindrec = m_BindList.begin(); it_bindrec != m_BindList.end(); ++it_bindrec)
                {
                if (it_bindrec->m_Neuroreceptor == &(*it_receptor))
                    {
                    bindingFound = true;
                    }
                }
            if(!bindingFound)
                {
                for(std::vector<Neurotransmitter>::iterator it_transmitter = m_NeurotransmitterList.begin(); it_transmitter != m_NeurotransmitterList.end(); ++it_transmitter)
                    {
                    for(std::vector<s_BindList>::iterator it_bindrec = m_BindList.begin(); it_bindrec != m_BindList.end(); ++it_bindrec)
                        {
                        if (it_bindrec->m_Neurotransmitter == &(*it_transmitter))
                            {
                            bindingFound = true;
                            }
                        }
                    if(!bindingFound)
                        {
                        if (it_receptor->CompatibilityCheck(it_transmitter->GetType()))
                            {
                            s_BindList newBinding;
                            newBinding.m_Neuroreceptor = &(*it_receptor);
                            newBinding.m_Neurotransmitter = &(*it_transmitter);
                            m_BindList.push_back(newBinding);
                            }
                        }
                    }
                }
            }
        }
        // Clock duration does not consider parallel or serial operation
    m_oldClock = eventTime;
    return 0;
    }
    
protected:
private:
    int m_NeuronType;
    int m_Tag;
    int m_addStatus;
    int m_TauCyclesAdd;
    int m_TauCyclesDecay;
    int m_ChargeType;
    int m_DischargeType;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_oldClock;
    int m_duration;
    double m_Volume;
    double m_SurfaceArea;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double m_Energy; //!< Member variable "m_Energy"
    double m_axonlength;
    double m_TimeDilation;
    double m_TimeThreshold;
    struct s_CounterAdjustment
    {
    s_CounterAdjustment() : s_CounterBegin(std::chrono::high_resolution_clock::now()), s_PointToCounter(0), s_Pool(0), s_Interval(0), s_Shape(0) {}
    std::chrono::time_point<std::chrono::high_resolution_clock> s_CounterBegin;
    double* s_PointToCounter;
    double s_Pool;
    int s_Interval;
    int s_Shape;
    };
    
    std::vector<s_CounterAdjustment> m_TemporalAdjustment;
    double m_ReduceBy;
    double m_ReducedBy;
    std::vector<Neurotransmitter> m_NeurotransmitterList;
    std::vector<Neuroreceptor> m_NeuroreceptorList;
    
    struct s_BindList
    {
    Neurotransmitter* m_Neurotransmitter;
    Neuroreceptor* m_Neuroreceptor;
    };
    
    std::vector<s_BindList> m_BindList;
    
    
    int synapseCounter;           //!< Member variable "synapseCounter"
    int synapseDemand;
    double minimumDistance;
    
    struct NearbyNeuron
    {
    Neuron* nearbyNeuron;
    double distanceToNeuron;
    double synapseGravitationalAttraction;
    bool synapseAllocated;
    };
    
    std::vector<NearbyNeuron> neuronList;
    std::vector<NearbyNeuron>::iterator it;

    
};


class Synapse : public Neuron
{
public:
    /** Default constructor */
    Synapse(Neuron& cw) : Neuron(cw) {
            //std::cout << "Synapse connected to Neuron @ " << &cw << std::endl;
        synapseDemand = 0;                   /** set initial type value              */
            //        std::copy(&cw, &cw + 1, std::back_inserter(synapseneuronlist));
        
    };
    /** Default destructor */
    virtual ~Synapse() {};
    
};

#endif // BRAINHARMONICS_SYNAPSE_H
