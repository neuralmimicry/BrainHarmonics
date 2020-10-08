/*------------------------------------------------------------------------------*/
/* @file      interneuronspace.cc                                                        */
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

#include "interneuronspace.h"
#include "neuron.h"
#include "neurotransmitter.h"
#include "neuroreceptor.h"

bool InterneuronSpace::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(interneuronspace_type < 1)
        {
        interneuronspace_type = 1;
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
    interneuronspaceDemand = 0;                   /** Set initial type value              */
    
    
    switch(interneuronspace_type)
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

CognitiveNetwork*  InterneuronSpace::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
    if(neurotransmitter_list.size() < neurotransmitter_pool)
        {
        Neurotransmitter* new_object = new Neurotransmitter();
        return new_object;
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> InterneuronSpace::CreateNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
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


std::vector<CognitiveNetwork*> InterneuronSpace::CloneNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> cloning_list, double perfection_membership)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  InterneuronSpace::CloneNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* clone_object, double perfection_membership)
{
        // Function TBD
	return nullptr;
}

std::vector<CognitiveNetwork*> InterneuronSpace::DestroyNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> destruction_list)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  InterneuronSpace::DestroyNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* destroy_object)
{
        // Function TBD
	return nullptr;
}

CognitiveNetwork*  InterneuronSpace::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, CognitiveNetwork* add_object)
{
    if(add_object != nullptr)
        {
        neurotransmitter_list.push_back(add_object);
        return neurotransmitter_list.back();
        }
    else
        return nullptr;
}

std::vector<CognitiveNetwork*> InterneuronSpace::AddNeurotransmitters(std::chrono::time_point<Clock> event_time, std::vector<CognitiveNetwork*> add_objects)
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


CognitiveNetwork*  InterneuronSpace::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        // Function TBD
    return nullptr;
}

std::vector<CognitiveNetwork*> InterneuronSpace::RemoveNeurotransmitters(std::chrono::time_point<Clock> event_time, int quantity)
{
        // Function TBD
	return std::vector<CognitiveNetwork*>();
}

CognitiveNetwork*  InterneuronSpace::GetNeurotransmitter(std::chrono::time_point<Clock> event_time, int selector)
{
    return neurotransmitter_list[selector];
}

std::vector<CognitiveNetwork*> InterneuronSpace::GetNeurotransmitters(std::chrono::time_point<Clock> event_time)
{
    return neurotransmitter_list;
}



int InterneuronSpace::GetDemand(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return interneuronspaceDemand; }

/*
double InterneuronSpace::GetDistance(std::chrono::time_point<Clock> event_time, int val) { return (double)neuronList[val].distanceToNeuron; }

int InterneuronSpace::GetAllocatedNeuron(std::chrono::time_point<Clock> event_time) { interneuronspaceCounter = 0;
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        if((*it).interneuronspaceAllocated == false) interneuronspaceCounter++; else break;
    }
    return interneuronspaceCounter;
}

double InterneuronSpace::GetMinimumDistance(std::chrono::time_point<Clock> event_time) { minimumDistance = 1000;
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        if((*it).distanceToNeuron != 0 && (*it).distanceToNeuron < minimumDistance) minimumDistance = (*it).distanceToNeuron;
    }
    return minimumDistance;
}

void InterneuronSpace::GetNeuronList(std::chrono::time_point<Clock> event_time) {
    for ( auto it = neuronList.begin(); it != neuronList.end();  ++it) {
        std::cout << (*it).distanceToNeuron << std::endl;
    }
}
*/
void InterneuronSpace::SetDemand(std::chrono::time_point<Clock> event_time, int val) { interneuronspaceDemand = val; }

void InterneuronSpace::SetNeuron(std::chrono::time_point<Clock> event_time, int val) { neuronList[val].interneuronspaceAllocated = true; }

/*
void InterneuronSpace::AddDistance(std::chrono::time_point<Clock> event_time, Neuron *neuron, double val)
{
    NearbyNeuron AddNeuron;
    AddNeuron.nearbyNeuron = neuron;
    AddNeuron.distanceToNeuron = val;
        // Add 0.001 to avoid divide by zero
    AddNeuron.interneuronspaceGravitationalAttraction = interneuronspaceDemand / ( (val + 0.001) * (val + 0.001) );
    AddNeuron.interneuronspaceAllocated = false;
    neuronList.push_back(AddNeuron);
}
*/

/*
 int InterneuronSpace::AddInterneuronSpace(std::vector<InterneuronSpace> *toAddto, std::vector<CognitiveNetwork> *aPartof, int arrayEntry)
 {
 InterneuronSpace myInterneuronSpace((*aPartof)[arrayEntry]);
 // Use move not push_back otherwise data is destroyed on exiting function
 std::copy(&myInterneuronSpace, &myInterneuronSpace + 1, std::back_inserter(*toAddto));
 
 return 0;
 }
 */


void InterneuronSpace::SendBareSpike(std::chrono::time_point<Clock> event_time)
{
    object_energy += 1000;
}

/*
int InterneuronSpace::AddNeurotransmitter(std::chrono::time_point<Clock> event_time, Neurotransmitter *val)
{
    neurotransmitter_list.push_back(*val);
    return 0;
}
*/
/*
int InterneuronSpace::CreateNeurotransmitter(std::chrono::time_point<Clock> event_time)
{
        //    Neurotransmitter myNeurotransmitter(event_time);
        //    AddNeurotransmitter(event_time, &myNeurotransmitter);
    return 0;
}
*/
/*
int InterneuronSpace::RemoveNeurotransmitter(std::chrono::time_point<Clock> event_time, Neurotransmitter *val)
{
        //neurotransmitter_list.erase(std::remove(neurotransmitter_list.begin(), neurotransmitter_list.end(), *val), neurotransmitter_list.end());
    return 0;
}
*/

void InterneuronSpace::SendTransmitterSpike(std::chrono::time_point<Clock> event_time)
{
    for (int nloop = 0; nloop < 100; nloop++)
        {
        CreateNeurotransmitter(event_time);
        }
    SendBareSpike(event_time);
}

/*
int InterneuronSpace::AddNeuroreceptor(std::chrono::time_point<Clock> event_time, Neuroreceptor *val)
{
    neuroreceptor_list.push_back(*val);
    return 0;
}
*/
/*
int InterneuronSpace::RemoveNeuroreceptor(std::chrono::time_point<Clock> event_time, Neuroreceptor *val)
{
        //neuroreceptor_list.erase(std::remove(neuroreceptor_list.begin(), neuroreceptor_list.end(), *val), neuroreceptor_list.end());
    return 0;
}
*/

int InterneuronSpace::Update(std::chrono::time_point<Clock> event_time)
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
            // Use GetPoint to enable movement across InterneuronSpace to Neuroreceptor
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
                        if (it_receptor->CompatibilityCheck(it_transmitter->GetType(std::chrono::time_point<Clock> event_time)))
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
