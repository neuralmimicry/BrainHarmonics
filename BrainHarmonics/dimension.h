/*------------------------------------------------------------------------------*/
/* @file      dimension.h                                                       */
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

#ifndef BRAINHARMONICS_DIMENSION_H
#define BRAINHARMONICS_DIMENSION_H

#include <iostream>
#include <vector>
#include "universe.h"

class Dimension : public Universe
{
    friend class CognitiveNetwork; // Allow a sibling access to Dimension functions
    friend class CompositeForce;
    friend class CompositeParticle;
    friend class ElementaryForce;
    friend class ElementaryParticle;
    friend class Matter;
    friend class Membrane;
    friend class Monomer;
    friend class Neuron;
    friend class Polymer;
    friend class Point;
    friend class Solid;
    friend class Soma;
    

public:
    Dimension() : Dimension(0) {}

    Dimension(unsigned int object_type) : Dimension(object_type, std::chrono::high_resolution_clock::now()) {}

    Dimension(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}

    Dimension(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
    dimension_type = object_type;
    time_object_created = event_time;
        //    Creation(time_object_created, "Dimension", dimension_type);
    ResetParameters(event_time);
    }
    
    virtual ~Dimension() {}
    
        // Vector of counter pointers are used to enable gradual increase/decrease of values over time to represent
        // biological functions rather than near-instantaneous electronic transmission.
    struct CounterAdjustment
    {
    CounterAdjustment() : counter_begin(std::chrono::high_resolution_clock::now()), point_to_counter(0), pool(0), interval(0), shape(0) {}
    std::chrono::time_point<Clock> counter_begin;
    std::chrono::time_point<Clock> counter_last_update;
    std::chrono::time_point<Clock> counter_end;
    double* point_to_counter;
    double pool;
    int interval;
    int shape;
    };
    
    std::vector<CounterAdjustment*> temporal_adjustment_list;
    
    
    unsigned int GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return dimensionCounter; }
    
    double GetScale(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return (dimension_scale/100); }

    double GetOffset(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return dimension_offset; }
    int duration_since_last_event;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> TheTimeNow();
    
    
    void SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val);
    
    void SetScale(std::chrono::time_point<Clock> event_time, double val);
    
    void SetTime(std::chrono::time_point<Clock> event_time, double val);
    
    void SetOffset(std::chrono::time_point<Clock> event_time, double val);
    
    void IncScale(std::chrono::time_point<Clock> event_time, double val);
    
    void DecScale(std::chrono::time_point<Clock> event_time, double val);
    
    void IncTime(std::chrono::time_point<Clock> event_time, double val);
    
    void DecTime(std::chrono::time_point<Clock> event_time, double val);

    void IncOffset(std::chrono::time_point<Clock> event_time, double val);

    void DecOffset(std::chrono::time_point<Clock> event_time, double val);
    
    void SetObjectType(std::chrono::time_point<Clock> event_time, int val);
    
    int GetObjectType(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return dimension_type; }

    bool ResetParameters(std::chrono::time_point<Clock> event_time);
        
    void AdjustCounters(std::chrono::time_point<std::chrono::high_resolution_clock> currentTime);
    
    int Update(std::chrono::time_point<Clock> event_time);

    void SetCharge(std::chrono::time_point<Clock> event_time, int val) final {}
    void SetSpin(std::chrono::time_point<Clock> event_time, int val) final {}
    double GetGravitation(std::chrono::time_point<Clock> event_time) final {}
    double GetWeak(std::chrono::time_point<Clock> event_time) final {}
    double GetWeakElectroweak(std::chrono::time_point<Clock> event_time) final {}
    double GetElectromagnetic(std::chrono::time_point<Clock> event_time) final {}
    double GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) final {}
    double GetStrong(std::chrono::time_point<Clock> event_time) final {}
    double GetStrongFundamental(std::chrono::time_point<Clock> event_time) final {}
    double GetStrongResidual(std::chrono::time_point<Clock> event_time) final {}
    
    double ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyWeak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrong(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) final {}
    double ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) final {}
    
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
    double scale_time;
    std::chrono::time_point<Clock> time_object_created;              //!< Member variable "time_object_created"
    std::chrono::time_point<Clock> objectExpiration;            //!< Member variable "objectExpiration"
    std::chrono::time_point<Clock> objectLifespan;              //!< Member variable "objectLifespan"

private:
    void AddTemporalAdjustment(std::chrono::time_point<Clock> event_time, double *point_to_counter, double pool, int interval, int shape);

    double object_energy;
    int dimension_type;
    unsigned int dimensionCounter;          //!< Member variable "dimensionCounter"
    double dimension_scale;
    double dimension_time_counter;
    double dimension_offset;
    
    
    unsigned int m_Counter; //!< Member variable "m_Counter"
    int m_OrbitalType;
    int m_Tau;
    double m_Position;
    double m_Phase;
    int m_Duration;
    int m_InternalClock;
    std::chrono::time_point<Clock> previous_event_time;
    bool object_initialised;
    bool object_disabled;

};


#endif // BRAINHARMONICS_DIMENSION_H
