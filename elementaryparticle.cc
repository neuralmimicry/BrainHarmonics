/*------------------------------------------------------------------------------*/
/* @file      elementaryparticle.cc                                             */
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

#include "elementaryparticle.h"

bool ElementaryParticle::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(elementary_particle_type < 1)
        {
        elementary_particle_type = 1;
        }
    
    elementary_particle_mass_index = 0;
    elementary_particle_mass = 0;
    elementary_particle_spin = 0;
    elementary_particle_charge = 0;
    elementary_particle_counter = 0;
    return true;
}

void ElementaryParticle::SetMassIndex(std::chrono::time_point<Clock> event_time, int val)
{
    elementary_particle_mass_index = val;
    switch(elementary_particle_mass_index)
    {
        case 0:
        {
            // Blank
        elementary_particle_mass = 0 * kUnitKgeV;
        break;
        }
        case 1:
        {
            // Gluon (Gauge Boson)
        elementary_particle_mass = 0 * kUnitKgeV;
        elementary_particle_charge = 3;
        elementary_particle_spin = 2;
        break;
        }
        case 2:
        {
            // Photon (Gauge Boson)
        elementary_particle_mass = 0 * kUnitKgeV;
        break;
        }
        case 3:
        {
            // Electron Neutrino (Lepton)
        elementary_particle_mass = 2.2 * kUnitKgeV;
        break;
        }
        case 4:
        {
            // Muon Neutrino (Lepton)
        elementary_particle_mass = 0.17 * kUnitKgMeV;
        break;
        }
        case 5:
        {
            // Electron (Lepton)
        elementary_particle_mass = 0.511 * kUnitKgMeV;
        break;
        }
        case 6:
        {
            // Up (Quark)
        elementary_particle_mass = 2.3 * kUnitKgMeV;
        elementary_particle_charge = 5;
        elementary_particle_spin = 1;
        break;
        }
        case 7:
        {
            // Down (Quark)
        elementary_particle_mass = 4.8 * kUnitKgMeV;
        break;
        }
        case 8:
        {
            // Tau Neutrino (Lepton)
        elementary_particle_mass = 15.5 * kUnitKgMeV;
        break;
        }
        case 9:
        {
            // Strange (Quark)
        elementary_particle_mass = 95 * kUnitKgMeV;
        break;
        }
        case 10:
        {
            // Muon (Lepton)
        elementary_particle_mass = 105.7 * kUnitKgMeV;
        break;
        }
        case 11:
        {
            // Charm (Quark)
        elementary_particle_mass = 1.275 * kUnitKgGeV;
        elementary_particle_charge = 5;
        elementary_particle_spin = 1;
        break;
        }
        case 12:
        {
            // Tau (Lepton)
        elementary_particle_mass = 1.777 * kUnitKgGeV;
        break;
        }
        case 13:
        {
            // Bottom (Quark)
        elementary_particle_mass = 4.18 * kUnitKgGeV;
        break;
        }
        case 14:
        {
            // W Boson (Gauge Boson)
        elementary_particle_mass = 80.4 * kUnitKgGeV;
        break;
        }
        case 15:
        {
            // Z Boson (Gauge Boson)
        elementary_particle_mass = 91.2 * kUnitKgGeV;
        break;
        }
        case 16:
        {
            // Higgs Boson (Boson)
        elementary_particle_mass = 126 * kUnitKgGeV;
        break;
        }
        case 17:
        {
            // Top (Quark)
        elementary_particle_mass = 173.07 * kUnitKgGeV;
        elementary_particle_charge = 5;
        elementary_particle_spin = 1;
        break;
        }
    }
}

void ElementaryParticle::SetMass(std::chrono::time_point<Clock> event_time, double val)          { elementary_particle_mass = val; }

int ElementaryParticle::Update(std::chrono::time_point<Clock> event_time)
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
        }
        previous_event_time = event_time;
        }
}
