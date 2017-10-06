//
//  myelinsheath.h
//  BrainHarmonics
//
//  Created by Paul Isaac's on 16/02/16.
//  Copyright © 2016 Paul Isaac's. All rights reserved.
//

#ifndef BRAINHARMONICS_MYELINSHEATH_H
#define BRAINHARMONICS_MYELINSHEATH_H

#include <iostream>
#include <vector>
#include "cognitivenetwork.h"

class MyelinSheath : public CognitiveNetwork
{
public:
    MyelinSheath() : MyelinSheath(0) {}
    
    MyelinSheath(unsigned int object_type) : MyelinSheath(object_type, std::chrono::high_resolution_clock::now()) {}
    
    MyelinSheath(unsigned int object_type, std::chrono::time_point<Clock> event_time) : CognitiveNetwork() {}
    
    MyelinSheath(unsigned int object_type, std::chrono::time_point<Clock> event_time, CognitiveNetwork& cognitivenetwork_connector) : CognitiveNetwork(cognitivenetwork_connector)
    {
        // Each myelinsheath type will have its own parameter ranges. The default is 0
    myelinsheath_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    }
    /** Default destructor */
    virtual ~MyelinSheath() {}

    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return m_Counter; }
    double GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return object_energy; }

    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { m_Counter = val; }
    void SetEnergy(std::chrono::time_point<Clock> event_time, double val) { object_energy = val; }

    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
    std::vector<CognitiveNetwork*> axonbranch_list;

private:
    int myelinsheath_type;
    unsigned int m_Counter; //!< Member variable "m_Counter"
    double object_energy; //!< Member variable "object_energy"
    double object_energy_threshold;
    double object_size;
    double object_energyFull;
    double m_Ions;
    double m_Volume;
    double m_SurfaceArea;
    double m_Length;

    std::chrono::time_point<Clock> previous_event_time;
    std::chrono::time_point<Clock> time_object_created;
    int duration_since_last_event;
    bool object_initialised;
    bool object_disabled;
};

#endif // BRAINHARMONICS_MYELINSHEATH_H
