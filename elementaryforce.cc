/*------------------------------------------------------------------------------*/
/* @file      elementaryforce.cc                                                */
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

#include "elementaryforce.h"
#include "elementaryparticle.h"

bool ElementaryForce::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(elementary_force_type < 1)
        {
        elementary_force_type = 1;
        }
    

    elementary_force_gravitation = 0;
    elementary_force_weak = 0;
    elementary_force_weak_electroweak = 0;
    elementary_force_electromagnetic = 0;
    elementary_force_electromagnetic_electroweak = 0;
    elementary_force_strong = 0;
    elementary_force_strong_fundamental = 0;
    elementary_force_strong_residual = 0;
    return true;
}

unsigned int ElementaryForce::GetCounter(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_counter; }
double ElementaryForce::GetEnergy(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_energy; }
double ElementaryForce::GetGravitation(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_gravitation; }
double ElementaryForce::GetWeak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_weak; }
double ElementaryForce::GetWeakElectroweak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_weak_electroweak; }
double ElementaryForce::GetElectromagnetic(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_electromagnetic; }
double ElementaryForce::GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_electromagnetic_electroweak; }
double ElementaryForce::GetStrong(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_strong; }
double ElementaryForce::GetStrongFundamental(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_strong_fundamental; }
double ElementaryForce::GetStrongResidual(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return elementary_force_strong_residual; }

double ElementaryForce::ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyWeak(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyStrong(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) { return val; }
double ElementaryForce::ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) { return val; }

void ElementaryForce::SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) { elementary_force_counter = val; }
void ElementaryForce::SetGravitation(std::chrono::time_point<Clock> event_time, double val) {elementary_force_gravitation = val; }
void ElementaryForce::SetWeak(std::chrono::time_point<Clock> event_time, double val) {elementary_force_weak = val; }
void ElementaryForce::SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) {elementary_force_weak_electroweak = val; }
void ElementaryForce::SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val) {elementary_force_electromagnetic = val; }
void ElementaryForce::SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) {elementary_force_electromagnetic_electroweak = val; }
void ElementaryForce::SetStrong(std::chrono::time_point<Clock> event_time, double val) {elementary_force_strong = val; }
void ElementaryForce::SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val) {elementary_force_strong_fundamental = val; }
void ElementaryForce::SetStrongResidual(std::chrono::time_point<Clock> event_time, double val) {elementary_force_strong_residual = val; }

void ElementaryForce::PollElementaryForce(std::chrono::time_point<Clock> event_time) {}


void ElementaryForce::Update(std::chrono::time_point<Clock> event_time)
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
