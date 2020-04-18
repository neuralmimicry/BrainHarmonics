/*------------------------------------------------------------------------------*/
/* @file      monomer.h                                                         */
/* @details   of the biological type                                            */
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

#ifndef BRAINHARMONICS_MONOMER_H
#define BRAINHARMONICS_MONOMER_H

#include <iostream>
#include <vector>
#include "universe.h"

class Monomer : public Universe
{
    
public:
    Monomer() : Monomer(0) {}
    
    Monomer(unsigned int object_type) : Monomer(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Monomer(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Monomer(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each monomer type will have its own parameter ranges. The default is 0
    monomer_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Monomer", monomer_type);
    object_disabled = true;
    }
    
    /** Default destructor */
    virtual ~Monomer() {}
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time);
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val);

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    int AddSolid(std::chrono::time_point<Clock> event_time);

    int Update(std::chrono::time_point<Clock> event_time);
 
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
    
        //    void SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val) final {}
    
        //    std::vector<double> GetPointPosition(std::chrono::time_point<Clock> event_time) final {}
    
        //    int GetCharge(std::chrono::time_point<Clock> event_time) final {}

protected:
    std::vector<Monomer*> solid_list;
private:
    
    unsigned int monomer_counter; //!< Member variable "monomer_counter"
    int monomer_type;
    bool object_initialised;
    bool object_disabled;
    int duration_since_last_event;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
};


#endif // BRAINHARMONICS_MONOMER_H
