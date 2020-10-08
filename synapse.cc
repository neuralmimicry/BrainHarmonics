/*------------------------------------------------------------------------------*/
/* @file      synapse.cc                                                        */
/* @details   Assign structure for scalar values                                */
/* @author    Paul Isaac's                                                      */
/* @date      16.02.2016                                                        */
/* @Copyright © 2016 Paul Isaac's. All rights reserved.                         */
/*------------------------------------------------------------------------------*/

/* Code snippets used:                                                          */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com          */
/* The class defines a data point and the operations that can be carried out on */
/* it.                                                                          */
/* Using the hierarchical linking the aim is to develop the application to      */
/* relate to real-world physics. This will then ease mapping between simulation,*/
/* emulation and real-world universes.                                          */

#include "synapse.h"
#include "neuron.h"
#include "neurotransmitter.h"
#include "neuroreceptor.h"
    //#include "polymer.h"

bool Synapse::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(synapse_type < 1)
        {
        synapse_type = 1;
        }
    
    object_energy = 10 * ((rand() % 30 + 85) / 100);
    object_energy_threshold = 2000 * ((rand() % 30 + 85) / 100);
    object_size = 1 * ((rand() % 30 + 85) / 100);
    m_Volume = 100;
    m_SurfaceArea = 100;
    m_TauCyclesAdd = 100; // Time frame that it takes for a value to be Added (avoiding instantaneous Addition)
    m_TauCyclesDecay = 1000; // Time frame that it takes for a value to decay
    m_ChargeType = 0;
    m_DischargeType = 1;
    synapseDemand = 0;                   /** Set initial type value              */
    
    
    switch(synapse_type)
    {
        case 0:
        {
        object_size = 3 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 1:
        {
        object_size = 2 * ((rand() % 30 + 85) / 100);
        break;
        }
        case 2:
        {
        object_size = 1 * ((rand() % 30 + 85) / 100);
        break;
        }
    }
    return true;
}

CognitiveNetwork*  Synapse::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
    if(neurotransmitter_list.size() < neurotransmitter_pool)
        {
        Neurotransmitter* new_object = new Neurotransmitter();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> Synapse::CreateNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
    quantity = std::min(neurotransmitter_pool - int(neurotransmitter_list.size()), quantity);
    std::vector<CognitiveNetwork*> new_neurotransmitter_list;
    new_neurotransmitter_list.clear();
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            CognitiveNetwork* new_object = CreateNeurotransmitter(event_time);
            if(new_object != nullptr)
                {
                neurotransmitter_list.push_back(new_object);
                new_neurotransmitter_list.push_back(new_object);
                }
            else nloop = quantity;
            }
        }
    return new_neurotransmitter_list;
}


std::vector<CognitiveNetwork*> Synapse::CloneNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  Synapse::CloneNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<CognitiveNetwork*> Synapse::DestroyNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  Synapse::DestroyNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
	return nullptr;
}

CognitiveNetwork*  Synapse::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        neurotransmitter_list.push_back(add_object);
        return neurotransmitter_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> Synapse::AddNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
{
    int quantity = int(add_objects.size());
    quantity = std::min(neurotransmitter_pool - int(neurotransmitter_list.size()), quantity);
    if(quantity > 0)
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
            if(add_objects[nloop] != nullptr)
                {
                CognitiveNetwork* result = AddNeurotransmitter(event_time, add_objects[nloop]);
                if(add_objects[nloop] != result)
                    {
                    nloop = quantity;
                    }
                }
            }
        }
    return neurotransmitter_list;
}


CognitiveNetwork*  Synapse::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> Synapse::RemoveNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  Synapse::GetNeurotransmitter(std::chrono::time_point<Clock> event_time, int selector)
{
    return neurotransmitter_list[selector];
}

std::vector<CognitiveNetwork*> Synapse::GetNeurotransmitters(std::chrono::time_point<Clock> event_time)
{
    return neurotransmitter_list;
}



int Synapse::GetDemand(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return synapseDemand; }

/*
double Synapse::GetDistance(int val) { return (double)neuronList[val].distanceToNeuron; }

int Synapse::GetAllocatedNeuron() { synapseCounter = 0;
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        if((*it).synapseAllocated == false) synapseCounter++; else break;
    }
    return synapseCounter;
}

double Synapse::GetMinimumDistance() { minimumDistance = 1000;
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        if((*it).distanceToNeuron != 0 && (*it).distanceToNeuron < minimumDistance) minimumDistance = (*it).distanceToNeuron;
    }
    return minimumDistance;
}

void Synapse::GetNeuronList() {
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        std::cout << (*it).distanceToNeuron << std::endl;
    }
}
*/
void Synapse::SetDemand(std::chrono::time_point<Clock> event_time, int val) { synapseDemand = val; }

void Synapse::SetNeuron(std::chrono::time_point<Clock> event_time, int val) { neuronList[val].synapseAllocated = true; }

/*
void Synapse::AddDistance(Neuron *neuron, double val)
{
    NearbyNeuron AddNeuron;
    AddNeuron.nearbyNeuron = neuron;
    AddNeuron.distanceToNeuron = val;
        // Add 0.001 to avoid divide by zero
    AddNeuron.synapseGravitationalAttraction = synapseDemand / ( (val + 0.001) * (val + 0.001) );
    AddNeuron.synapseAllocated = false;
    neuronList.push_back(AddNeuron);
}
*/

/*
 int Synapse::AddSynapse(std::vector<Synapse> *toAddto, std::vector<CognitiveNetwork> *aPartof, int arrayEntry)
 {
 Synapse mySynapse((*aPartof)[arrayEntry]);
 // Use move not push_back otherwise data is destroyed on exiting function
 std::copy(&mySynapse, &mySynapse + 1, std::back_inserter(*toAddto));
 
 return 0;
 }
 */


void Synapse::SendBareSpike(std::chrono::time_point<Clock> event_time)
{
    object_energy += 1000;
}

/*
int Synapse::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, Neurotransmitter *val)
{
    neurotransmitter_list.push_back(*val);
    return 0;
}
*/
/*
int Synapse::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        //    Neurotransmitter myNeurotransmitter(event_time);
        //    AddNeurotransmitter(event_time, &myNeurotransmitter);
    return 0;
}
*/
/*
int Synapse::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time, Neurotransmitter *val)
{
        //neurotransmitter_list.erase(std::remove(neurotransmitter_list.begin(), neurotransmitter_list.end(), *val), neurotransmitter_list.end());
    return 0;
}
*/

void Synapse::SendTransmitterSpike(std::chrono::time_point<Clock> event_time)
{
    for (int nloop = 0; nloop < 100; nloop++)
        {
        CreateNeurotransmitter(event_time);
        }
    SendBareSpike(event_time);
}

/*
int Synapse::AddNeuroreceptor(std::chrono::time_point<Clock> event_time, Neuroreceptor *val)
{
    neuroreceptor_list.push_back(*val);
    return 0;
}
*/
/*
int Synapse::RemoveNeuroreceptor(std::chrono::time_point<Clock> event_time, Neuroreceptor *val)
{
        //neuroreceptor_list.erase(std::remove(neuroreceptor_list.begin(), neuroreceptor_list.end(), *val), neuroreceptor_list.end());
    return 0;
}
*/



int Synapse::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
        object_initialised = ResetParameters(event_time);
        }
    
    if(event_time != previous_event_time)
        {
    // time_dimension_pointer->AdjustCounters(event_time);
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    
    if (object_energy < 0)
        {
        object_energy = 0;
        }
    
    if (duration_since_last_event > 0 && object_energy > 0)
        {
            // Extra programming: Change 0 to correct point address
            // Use GetPoint to enable movement across Synapse to Neuroreceptor
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &GetPoint(event_time, 0)->object_energy, object_energy * 0.1, 10000, 1);
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - (object_energy * 0.1), 10000, 1);
        }
    

    bool bindingFound;

    /*
    for(std::vector<Neurotransmitter*>::iterator it = neurotransmitter_list.begin(); it != neurotransmitter_list.end(); ++it)
        {
        (*it)->Update(event_time);
        }
    
    if (object_energy > 0)
        {
        for(std::vector<Neurotransmitter>::iterator it = neurotransmitter_list.begin(); it != neurotransmitter_list.end(); ++it)
            {
            // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, (0-object_energy)/neurotransmitter_list.size(), 100, 1);   // redistribute energy
            it->AddTemporalAdjustment(event_time, object_energy/neurotransmitter_list.size());
            }
        }
    
    duration_since_last_event = std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - previous_event_time).count();
    if (duration_since_last_event < 0)
        {
        duration_since_last_event = 0;
        }
    if (duration_since_last_event > 1000)
        {
        for(std::vector<Neuroreceptor>::iterator it_receptor = neuroreceptor_list.begin(); it_receptor != neuroreceptor_list.end(); ++it_receptor)
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
                for(std::vector<Neurotransmitter>::iterator it_transmitter = neurotransmitter_list.begin(); it_transmitter != neurotransmitter_list.end(); ++it_transmitter)
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
     */
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}
