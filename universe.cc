/*!
 * @file      universe.cc
 * @details   Base class of all operations
 * @author    Paul B. Isaac's, authored 03-FEB-2016
 * @date      08-APR-2020
 * @copyright © 2020 Linaro Limited.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Using the hierarchical linking the aim is to develop the application to
 * relate to real-world physics. This will then ease mapping between simulation,
 * emulation and real-world universes.
 */

#include "universe.h"
#include "cognitivenetwork.h"
#include "compositeforceparticle.h"
#include "dimension.h"
#include "elementaryforce.h"
#include "elementaryparticle.h"
#include "matter.h"
#include "monomer.h"
#include "polymer.h"
#include "solid.h"
#include "point.h"

double Universe::GetEnergy(std::chrono::time_point<Clock> event_time)
{
    /*!
     * The object has finite energy that can be redistributed to child objects to control information flow.
     * It can be used as an audit method for leaks.
     */
    return universe_energy;
}

void Universe::SetEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer)
{
	/*!
	 * During construction specify the amount of energy available
	 */
    universe_energy = energy_transfer;
}

double Universe::UseEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer)
{
	/*!
	 * Each time a new child object is created then it is given a share of the Universe energy.
	 * Negative energy is not enabled and so when the pool is low only the remainder is returned.
	 */
    universe_energy -= energy_transfer;
    if (universe_energy < 0)
        {
        energy_transfer = 0 - universe_energy;
        universe_energy = 0;
        }
    return energy_transfer;
}

double Universe::ReturnEnergy(std::chrono::time_point<Clock> event_time, double energy_transfer)
{
	/*!
	 * If a child object is destroyed then its remaining energy is returned to the pool.
	 */
    universe_energy += energy_transfer;
    return universe_energy;
}

void Universe::Creation(std::chrono::time_point<Clock> event_time, std::string object_title, int object_type)
{
        /*!
         * Each object has a type. When the object is created this function is called to announce
         * the creation. Primarily used as a debug point.
         */
        // std::cout << object_title << " type: " << object_type << " created @" << event_time.time_since_epoch().count() << std::endl;
}

void Universe::SetObjectType(std::chrono::time_point<Clock> event_time, int object_type)
{
	/*!
	 * ObjectType helps differentiate between the universes. Such as graphical, physical, simulated etc.
	 * U1 = Internal Time, X, Y & Z
     * U2 = Physical
	 * U3 = Spatial X,Y,Z & Time
	 * U4 = CPP
	 * U5 = Spikes
	 * U6 = Neurotransmitters
	 * U7 = Connectome
	 * U8 = Synapses
	 * U9 = Orbital example
	 */
    universe_type = object_type;
    Universe::ResetParameters(event_time);
}

bool Universe::ResetParameters(std::chrono::time_point<Clock> event_time)
{
	/*!
	 * Tidies up the construction of the Universe
	 */

        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified then set one.
    if(universe_type < 1)
        {
        universe_type = 1;
        }

    switch(universe_type)
    {
    /*!
     * Establish base parameters depending on object type.
     * This should be parameterised in a config file.
     */
        case 0:
        {
            // Blank
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 1:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 2:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 3:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 4:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 5:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 6:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 7:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 8:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        case 9:
        {
        universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
        scaled_time = 1.0;            // To speed up or slow down with relation to system time.
        time_object_created = event_time;  // According to function time, when the object was created.
        SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
        break;
        }
        default:
        {
            universe_energy = 10^12;      // Potential audit, energy cannot be created or destroyed, only redistributed
            scaled_time = 1.0;            // To speed up or slow down with relation to system time.
            time_object_created = event_time;  // According to function time, when the object was created.
            SetLifespan(event_time, std::chrono::nanoseconds(10^12));   // 10^12 nanoseconds default lifespan. Will destruct when no child objects remain after countdown.
            universe_type = 1;
        }
    }
    return true;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Universe::TheTimeNow()
{
	/*!
	 * Event-driven asynchronous solutions that are being simulated require timestamps to
	 * help identify which events across the whole system occur at the same time.
	 * Also when attempting to simulate biological speed there is a need to slow down events.
	 */
    return Universe::TheCalculatedTimeNow(time_object_created, std::chrono::high_resolution_clock::now(), scaled_time);
}

std::chrono::time_point<std::chrono::high_resolution_clock> Universe::TheCalculatedTimeNow(std::chrono::time_point<std::chrono::high_resolution_clock> time_object_created_time, std::chrono::time_point<Clock> event_time, double calculated_scaled_time)
{
	/*!
	 * Scales time
	 */
    return time_object_created_time + std::chrono::nanoseconds(int(std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - time_object_created_time).count() * calculated_scaled_time));
}

void Universe::SetLifespan(std::chrono::time_point<Clock> event_time, std::chrono::nanoseconds life_time)
{
    /*!
     * Limit object lifespan
     */
	object_lifespan = life_time;
    object_expiration = time_object_created + object_lifespan;
}

void Universe::ExtendLife(std::chrono::time_point<Clock> event_time, std::chrono::nanoseconds life_time)
{
	/*!
	 * Extend object lifespan
	 */
    if(IsDead(event_time))
        {
        object_expiration = TheTimeNow();
        }
    object_expiration += life_time;
    object_lifespan = std::chrono::nanoseconds(std::chrono::duration_cast<std::chrono::nanoseconds>(object_expiration - time_object_created).count());
}

bool Universe::IsDead(std::chrono::time_point<Clock> event_time)
{
	/*!
	 * Has lifespan expired?
	 * When a lifespan expires it is up to the main program to decide what happens.
	 * Cleanup would be required. It could spawn a new fresh object.
	 */
    if (TheTimeNow() > object_expiration or object_energy <= 0)
        {
        return true;
        }
    else
        {
        return false;
        }
}


std::vector<Universe*> Universe::AddDimensions(std::chrono::time_point<Clock> event_time, int quantity)
{
	/*!
	 * Every Universe should have at least 1 dimension.
	 */
        // Only create a rational number of initial objects
    if( quantity > 0 && quantity < 20 )
        {
        for (int nloop = 0; nloop < quantity; nloop++)
            {
                // Future development create a Struct containing a request signature for operation
            Dimension* new_object = new Dimension();
            dimension_list.push_back(new_object);
            }
        }
    return dimension_list;
}

Universe* Universe::AddDimension(std::chrono::time_point<Clock> event_time)
{
	/*!
	 * Add a single dimension.
	 */

    /*!
     * In a massively parallel environment you cannot trust that .back will give you Your object
     * just allocated if another process just carried out the same thing in the same address space.
     * Future development will add a signature to the request that can be compared on the return
     * to get the right allocation.
     */
    return AddDimensions(event_time, 1).back();
}

std::vector<Universe*> Universe::GetDimensions(std::chrono::time_point<Clock> event_time)
{
	/*!
	 * Return the list of pointers to the dimensions in this universe instance.
	 */
    return dimension_list;
}

Universe* Universe::GetDimension(std::chrono::time_point<Clock> event_time, int selector)
{
	/*!
	 * Return a specific dimension pointer from the list of pointers to the dimensions
	 * in this universe instance.
	 */

	/*!
	 * Needs test to verify selector is not out of bounds
	 */
    return GetDimensions(event_time)[selector];
}


std::vector<ElementaryParticle*> Universe::AddElementaryParticles(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        ElementaryParticle* new_object = new ElementaryParticle();
        elementary_particle_list.push_back(new_object);
        }
    return elementary_particle_list;
}

ElementaryParticle* Universe::AddElementaryParticle(std::chrono::time_point<Clock> event_time)
{
    return AddElementaryParticles(event_time, 1).back();
}

std::vector<ElementaryParticle*> Universe::GetElementaryParticles(std::chrono::time_point<Clock> event_time)
{
    return elementary_particle_list;
}

ElementaryParticle* Universe::GetElementaryParticle(std::chrono::time_point<Clock> event_time, int selector)
{
	/*!
	 * Needs test to verify selector is not out of bounds
	 */
    return elementary_particle_list[selector];
}


std::vector<Universe*> Universe::AddElementaryForces(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        ElementaryForce* new_object = new ElementaryForce();
        elementary_force_list.push_back(new_object);
        }
    return elementary_force_list;
}

Universe* Universe::AddElementaryForce(std::chrono::time_point<Clock> event_time)
{
    return AddElementaryForces(event_time, 1).back();
}

std::vector<Universe*> Universe::GetElementaryForces(std::chrono::time_point<Clock> event_time)
{
    return elementary_force_list;
}

Universe* Universe::GetElementaryForce(std::chrono::time_point<Clock> event_time, int selector)
{
	/*!
	 * Needs test to verify selector is not out of bounds
	 */
    return elementary_force_list[selector];
}


std::vector<Universe*> Universe::AddCompositeForceParticles(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        CompositeForceParticle* new_object = new CompositeForceParticle();
        composite_forceparticle_list.push_back(new_object);
        }
    return composite_forceparticle_list;
}

Universe* Universe::AddCompositeForceParticle(std::chrono::time_point<Clock> event_time)
{
    return AddCompositeForceParticles(event_time, 1).back();
}

std::vector<Universe*> Universe::GetCompositeForceParticles(std::chrono::time_point<Clock> event_time)
{
    return composite_forceparticle_list;
}

Universe* Universe::GetCompositeForceParticle(std::chrono::time_point<Clock> event_time, int selector)
{
	/*!
	 * Needs test to verify selector is not out of bounds
	 */
    return composite_forceparticle_list[selector];
}


std::vector<Universe*> Universe::AddMatters(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        Matter* new_object = new Matter();
        matter_list.push_back(new_object);
        }
    return matter_list;
}

Universe* Universe::AddMatter(std::chrono::time_point<Clock> event_time)
{
    return AddMatters(event_time, 1).back();
}

std::vector<Universe*> Universe::GetMatters(std::chrono::time_point<Clock> event_time)
{
    return matter_list;
}

Universe* Universe::GetMatter(std::chrono::time_point<Clock> event_time, int selector)
{
	/*!
	 * Needs test to verify selector is not out of bounds
	 */
    return matter_list[selector];
}


std::vector<Universe*> Universe::AddMonomers(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        Monomer* new_object = new Monomer();
        monomer_list.push_back(new_object);
        }
    return monomer_list;
}

Universe* Universe::AddMonomer(std::chrono::time_point<Clock> event_time)
{
    return AddMonomers(event_time, 1).back();
}

std::vector<Universe*> Universe::GetMonomers(std::chrono::time_point<Clock> event_time)
{
    return monomer_list;
}

Universe* Universe::GetMonomer(std::chrono::time_point<Clock> event_time, int selector)
{
    return monomer_list[selector];
}


std::vector<Universe*> Universe::AddPolymers(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        Polymer* new_object = new Polymer();
        polymer_list.push_back(new_object);
        }
    return polymer_list;
}

Universe* Universe::AddPolymer(std::chrono::time_point<Clock> event_time)
{
    return AddPolymers(event_time, 1).back();
}

std::vector<Universe*> Universe::GetPolymers(std::chrono::time_point<Clock> event_time)
{
    return polymer_list;
}

Universe* Universe::GetPolymer(std::chrono::time_point<Clock> event_time, int selector)
{
    return polymer_list[selector];
}


std::vector<Universe*> Universe::AddSolids(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        Solid* new_object = new Solid();
        solid_list.push_back(new_object);
        }
    return solid_list;
}

Universe* Universe::AddSolid(std::chrono::time_point<Clock> event_time)
{
    return AddSolids(event_time, 1).back();
}

std::vector<Universe*> Universe::GetSolids(std::chrono::time_point<Clock> event_time)
{
    return solid_list;
}

Universe* Universe::GetSolid(std::chrono::time_point<Clock> event_time, int selector)
{
    return solid_list[selector];
}


std::vector<Universe*> Universe::AddCognitiveNetworks(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        CognitiveNetwork* new_object = new CognitiveNetwork();
        cognitive_network_list.push_back(new_object);
        }
    return cognitive_network_list;
}

Universe* Universe::AddCognitiveNetwork(std::chrono::time_point<Clock> event_time)
{
    return AddCognitiveNetworks(event_time, 1).back();
}

std::vector<Universe*> Universe::GetCognitiveNetworks(std::chrono::time_point<Clock> event_time)
{
    return cognitive_network_list;
}

Universe* Universe::GetCognitiveNetwork(std::chrono::time_point<Clock> event_time, int selector)
{
    return cognitive_network_list[selector];
}


std::vector<Universe*> Universe::AddPoints(std::chrono::time_point<Clock> event_time, int quantity)
{
    for (int nloop = 0; nloop < quantity; nloop++)
        {
        Point* new_object = new Point();
        point_list.push_back(new_object);
        }
    return point_list;
}

Universe* Universe::AddPoint(std::chrono::time_point<Clock> event_time)
{
    return AddPoints(event_time, 1).back();
}

std::vector<Universe*> Universe::GetPoints(std::chrono::time_point<Clock> event_time)
{
    return point_list;
}

Universe* Universe::GetPoint(std::chrono::time_point<Clock> event_time, int selector)
{
    return point_list[selector];
}

void Universe::UpdateCycle(std::chrono::time_point<Clock> event_time, std::vector<Universe*> set_of_update_pointers, unsigned int pointer_type)
{
    std::vector<Universe*>::iterator update_iter;
    Universe* update_pointer;
    for(update_iter = set_of_update_pointers.begin(); update_iter != set_of_update_pointers.end(); ++update_iter)
        {
        switch(pointer_type)
            {
                case 1:
                {
                auto update_pointer = dynamic_cast<CognitiveNetwork*>(*update_iter);
                break;
                }
                case 2:
                {
                auto update_pointer = dynamic_cast<CompositeForceParticle*>(*update_iter);
                break;
                }
                case 3:
                {
                auto update_pointer = dynamic_cast<Dimension*>(*update_iter);
                break;
                }
                case 4:
                {
                auto update_pointer = dynamic_cast<ElementaryForce*>(*update_iter);
                break;
                }
                case 5:
                {
                auto update_pointer = dynamic_cast<ElementaryParticle*>(*update_iter);
                break;
                }
                case 6:
                {
                auto update_pointer = dynamic_cast<Matter*>(*update_iter);
                break;
                }
                case 7:
                {
                auto update_pointer = dynamic_cast<Monomer*>(*update_iter);
                break;
                }
                case 8:
                {
                auto update_pointer = dynamic_cast<Polymer*>(*update_iter);
                break;
                }
                case 9:
                {
                auto update_pointer = dynamic_cast<Solid*>(*update_iter);
                break;
                }
                case 10:
                {
                auto update_pointer = dynamic_cast<Point*>(*update_iter);
                break;
                }
            }
        update_pointer->Update(event_time);
        }
}

int Universe::Update(std::chrono::time_point<Clock> event_time)
{
        // If this is the first time that Update is called after object instantiation use the setup parameters.
        // object_initialised should then report true and then not be re-run.
    if(!object_initialised)
        {
            // Attach a Dimension pointer to object for time based calculations
        time_dimension_pointer = AddDimension(event_time);
        time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
        object_initialised = ResetParameters(event_time);
        std::cout << "U";
        }
    if(event_time != previous_event_time)
        {
    
    //if (!cognitive_network_list.empty()) {UpdateCycle(event_time, cognitive_network_list, 1);}
    //UpdateCycle(event_time, composite_forceparticle_list, 2);
        //UpdateCycle(event_time, dimension_list, 3);
    //UpdateCycle(event_time, elementary_force_list, 4);
    //UpdateCycle(event_time, elementary_particle_list, 5);
    //UpdateCycle(event_time, matter_list, 6);
    //UpdateCycle(event_time, monomer_list, 7);
    //UpdateCycle(event_time, polymer_list, 8);
    //UpdateCycle(event_time, solid_list, 9);
    //UpdateCycle(event_time, point_list, 10);

    // time_dimension_pointer->AdjustCounters(event_time);
    
    unsigned int list_size = 0;
    
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
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - (object_energy * 0.001), 10000, 1);
        
        list_size = elementary_force_list.size();
        if(list_size > 0)
            {
        test_subject_one = rand() % list_size;
        test_subject_two = (rand() % (list_size - test_subject_one)) + test_subject_one;
        
        if(elementary_force_list[test_subject_one]->GetEnergy(event_time) < elementary_force_list[test_subject_two]->GetEnergy(event_time))
            {
            iter_swap(elementary_force_list.begin() + test_subject_one, elementary_force_list.begin() + test_subject_two);
            }
            }
        
        list_size = elementary_particle_list.size();
        if(list_size > 0)
            {
            test_subject_one = rand() % list_size;
            test_subject_two = (rand() % (list_size - test_subject_one)) + test_subject_one;
            
        if(elementary_particle_list[test_subject_one]->GetEnergy(event_time) < elementary_particle_list[test_subject_two]->GetEnergy(event_time))
            {
            iter_swap(elementary_particle_list.begin() + test_subject_one, elementary_particle_list.begin() + test_subject_two);
            }
            }
        
        list_size = cognitive_network_list.size();
        if(list_size > 0)
            {
            test_subject_one = rand() % list_size;
            test_subject_two = (rand() % (list_size - test_subject_one)) + test_subject_one;
            
        test_subject_one = rand() % cognitive_network_list.size();
        test_subject_two = (rand() % (cognitive_network_list.size() - test_subject_one)) + test_subject_one;
        
        if(cognitive_network_list[test_subject_one]->GetEnergy(event_time) < cognitive_network_list[test_subject_two]->GetEnergy(event_time))
            {
            iter_swap(cognitive_network_list.begin() + test_subject_one, cognitive_network_list.begin() + test_subject_two);
            }
            }

        list_size = composite_forceparticle_list.size();
        if(list_size > 0)
            {
            test_subject_one = rand() % list_size;
            test_subject_two = (rand() % (list_size - test_subject_one)) + test_subject_one;
            
        if(composite_forceparticle_list[test_subject_one]->GetEnergy(event_time) < composite_forceparticle_list[test_subject_two]->GetEnergy(event_time))
            {
            iter_swap(composite_forceparticle_list.begin() + test_subject_one, composite_forceparticle_list.begin() + test_subject_two);
            }
            }
        
            // Do not re-sort Points until implementing a separate ObjectID to keep track. Currently index only.
        /*
        test_subject_one = rand() % point_list.size();
        test_subject_two = (rand() % (point_list.size() - test_subject_one)) + test_subject_one;
        
        if(point_list[test_subject_one]->GetEnergy(event_time) < point_list[test_subject_two]->GetEnergy(event_time))
            {
            iter_swap(point_list.begin() + test_subject_one, point_list.begin() + test_subject_two);
            }
        */
        }
         
    
    if(IsDead(event_time))
        {
        return 1;
        }
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

void Universe::AddTemporalAdjustment(std::chrono::time_point<Clock> event_time, double *point_to_counter, double pool, int interval, int shape) {}

void Universe::AdjustCounters(std::chrono::time_point<std::chrono::high_resolution_clock> currentTime) {}

void Universe::SetCharge(std::chrono::time_point<Clock> event_time, int val) {}
void Universe::SetSpin(std::chrono::time_point<Clock> event_time, int val) {}
double Universe::GetGravitation(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetWeak(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetWeakElectroweak(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetElectromagnetic(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetStrong(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetStrongFundamental(std::chrono::time_point<Clock> event_time) {}
 double Universe::GetStrongResidual(std::chrono::time_point<Clock> event_time) {}

 double Universe::ApplyGravitation(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyWeak(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyElectromagnetic(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyStrong(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyStrongFundamental(std::chrono::time_point<Clock> event_time, double val) {}
 double Universe::ApplyStrongResidual(std::chrono::time_point<Clock> event_time, double val) {}

 void Universe::SetCounter(std::chrono::time_point<Clock> event_time, unsigned int val) {}
 void Universe::SetGravitation(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetWeak(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetWeakElectroweak(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetElectromagnetic(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetElectromagneticElectroweak(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetStrong(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetStrongFundamental(std::chrono::time_point<Clock> event_time, double val) {}
 void Universe::SetStrongResidual(std::chrono::time_point<Clock> event_time, double val) {}

 void Universe::PollElementaryForce(std::chrono::time_point<Clock> event_time) {}

    //void Universe::SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val) {}

    // std::vector<double> Universe::GetPointPosition(std::chrono::time_point<Clock> event_time) {}

    // int Universe::GetCharge(std::chrono::time_point<Clock> event_time) {}


