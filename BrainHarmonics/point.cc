/*------------------------------------------------------------------------------*/
/* @file      point.cc                                                          */
/* @details   Single Dimension point operations. Can be combined for multiDimension */
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

#include "point.h"
#include "dimension.h"

bool Point::ResetParameters(std::chrono::time_point<Clock> event_time)
{
        // If object instantiated without a time specified then add one.
    if(time_object_created == std::chrono::time_point<Clock>(std::chrono::nanoseconds::zero()))
        {
        time_object_created = event_time;
        srand((std::chrono::duration_cast<std::chrono::seconds>(TheTimeNow().time_since_epoch()).count()));
        }
    
        // If object instantiated without a type specified the set one.
    if(point_type < 1)
        {
        point_type = 1;
        }
    
    object_energy = 10 * ((rand() % 30 + 85) / 100);
    object_energy_threshold = 2000 * ((rand() % 30 + 85) / 100);
    object_size = 1 * ((rand() % 30 + 85) / 100);
    
    switch(point_type)
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

    /** Overflow options: 0 = Stay at Min/Max, 1 = Wrap, 2 = Bounce, 3 = Hidden,
     4 = DestroyDimension, 5 = DestroyAllDimensions         */
    
    /** Initialise to zero */
    point_seq = 0;                         /** Unique point sequence number       */
    
    point_scale = {1};                       /** Size can vary greatly. Scaling groups points */
    point_position = {0};                    /** Point Dimension value              */
    point_position_min = {-1} ;            /** Minimum value allowed for point    */
    point_position_min_overflow = {0};      /** What to do if overflow - see above */
    point_position_max = {1};              /** Maximum value allowed for point    */
    point_position_max_overflow = {0};       /** What to do if overflow - see above */
    
    point_move = {0};                        /** How far to move the point value    */
    point_move_min = {-1};                  /** Maximum change in movement         */
    point_move_min_overflow = {0};           /** What to do if overflow - see above */
    point_move_max = {1};                   /** Minimum change in movement         */
    point_move_max_overflow = {0};           /** What to do if overflow - see above */
    
        //        point_differential = double((int(rand() % 100) / 100)) - 0.5;   /** Rate of change of movement         */
    point_differential = {0};   /** Rate of change of movement         */
    point_differential_min = {-1};           /** Minimum rate of change             */
    point_differential_min_overflow = {0};   /** What to do if overflow - see above */
    point_differential_max = {1};            /** Maximum rate of change             */
    point_differential_max_overflow = {0};   /** What to do if overflow - see above */
    
    point_TTL = 50;                        /** Time to live for point             */
    point_TTL_min = 0;                     /** Minimum TTL for point              */
    point_TTL_min_overflow = 2;            /** What to do if overflow - see above */
    point_TTL_max = 100;                   /** Maximum TTL for point              */
    point_TTL_max_overflow = 2;            /** What to do if overflow - see above */
    return true;
}

void Point::SetObjectType(std::chrono::time_point<Clock> event_time, unsigned int val)
{
    if(point_type != val)
        {
        point_type = val;
        ResetParameters(event_time);
        }
}

void Point::PointForcePoll(std::chrono::time_point<Clock> event_time, Point* opposingPoint)
{
        // Do need to implement force affected by mass too
    combined_acceleration.clear();
    int counter_remote_object = 0;
    for(std::vector<double>::iterator it = point_differential.begin(); it != point_differential.end(); ++it)
        {
        combined_acceleration.push_back(double(*it + opposingPoint->point_differential[counter_remote_object]) / 2);
        counter_remote_object++;
        }
    
    counter_remote_object = 0;
    for(std::vector<double>::iterator it = point_position.begin(); it != point_position.end(); ++it)
        {
        distance_apart.push_back(double(*it - opposingPoint->point_position[counter_remote_object]));
        counter_remote_object++;
        }
    
    int num_dimensions = distance_apart.size();
    
    double a2 = 0;
    
        // Calculates distance beyond 3D if required
    if (distance_apart.size() > 1)
        {
        for(int outer_loop = 0; outer_loop < num_dimensions - 1; outer_loop++)
            {
            a2 = distance_apart[outer_loop] * distance_apart[outer_loop];
            for(int inner_loop = outer_loop + 1; inner_loop < num_dimensions; inner_loop++)
                {
                a2 += distance_apart[inner_loop] * distance_apart[inner_loop];
                distance_apart.push_back(sqrt(a2));
                }
            }
        }
    
        //        combined_acceleration = combined_acceleration / ( distance_apart * distance_apart );
        //    point_differential = point_differential - combined_acceleration;
        //    opposingPoint->point_differential = opposingPoint->point_differential - combined_acceleration;
    
    /*
     else
     {
     point_differential = 0 - point_differential;
     opposingPoint->point_differential = 0 - opposingPoint->point_differential;
     }
     */
}

void Point::PointPoll(std::chrono::time_point<Clock> event_time, double val)
{
    int counter_local_object = 0;
    for(std::vector<double>::iterator it = point_differential.begin(); it != point_differential.end(); ++it)
        {
        point_move[counter_local_object] += (double(*it * val));
        point_position[counter_local_object] += point_move[counter_local_object];
        counter_local_object++;
        }
}


void Point::OverflowPoll(std::chrono::time_point<Clock> event_time)
{
    for(int dimension_loop = 0; dimension_loop < int(point_position.size()); dimension_loop++)
        {
    if ( point_position[dimension_loop] < point_position_min[dimension_loop] )
        {
            //        std::cout << "PositionMin called: " << point_position_min_overflow << std::endl;
        switch (point_position_min_overflow[dimension_loop])
            {
                case 0:   // Stay at Min/Max value
                {
                point_position[dimension_loop] = point_position_min[dimension_loop];
                break;
                }
                case 1:   // Wrap value
                {
                point_position[dimension_loop] = point_position_min[dimension_loop] + ( point_position[dimension_loop] - point_position_max[dimension_loop] );
                break;
                }
                case 2:   // Bounce value
                {
                    //            std::cout << "Position Bounce called: " << point_position << " Max: " << point_position_max << " Move: " << point_move << std::endl;
                point_position[dimension_loop] = point_position_min[dimension_loop] + ( point_position_min[dimension_loop] - point_position[dimension_loop] );
                point_move[dimension_loop] = 0 - point_move[dimension_loop];
                point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
                break;
                }
                case 3:   // Make hidden
                {
                
                break;
                }
                case 4:   // Destroy Dimension data
                {
                
                break;
                }
                case 5:   // Destroy connected Dimension data
                {
                
                break;
                }
                break;
                
                default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
            }
        }
    
    if ( point_position[dimension_loop] > point_position_max[dimension_loop] )
        {
            //        std::cout << "PositionMax called." << std::endl;
        switch (point_position_max_overflow[dimension_loop])
            {
                case 0:   // Stay at Min/Max value
                {
                point_position[dimension_loop] = point_position_max[dimension_loop];
                break;
                }
                case 1:   // Wrap value
                {
                point_position[dimension_loop] = point_position_min[dimension_loop] + ( point_position[dimension_loop] - point_position_max[dimension_loop] );
                break;
                }
                case 2:   // Bounce value
                {
                point_position[dimension_loop] = point_position_max[dimension_loop] - ( point_position[dimension_loop] - point_position_max[dimension_loop] );
                point_move[dimension_loop] = 0 - point_move[dimension_loop];
                point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
                break;
                }
                case 3:   // Make hidden
                {
                
                break;
                }
                case 4:   // Destroy Dimension data
                {
                
                break;
                }
                case 5:   // Destroy connected Dimension data
                {
                
                break;
                }
                break;
                
                default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
            }
        }
    
    if ( point_move[dimension_loop] < point_move_min[dimension_loop] )
        {
            //        std::cout << "MoveMin called." << std::endl;
        switch (point_move_min_overflow[dimension_loop])
            {
                case 0:   // Stay at Min/Max value
                {
                point_move[dimension_loop] = point_move_min[dimension_loop];
                point_differential[dimension_loop] = 0;
                break;
                }
                case 1:   // Wrap value
                {
                point_move[dimension_loop] = point_move_min[dimension_loop] + ( point_move[dimension_loop] - point_move_max[dimension_loop] );
                break;
                }
                case 2:   // Bounce value
                {
                point_move[dimension_loop] = point_move_min[dimension_loop] + ( point_move_min[dimension_loop] - point_move[dimension_loop] );
                point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
                break;
                }
                case 3:   // Make hidden
                {
                
                break;
                }
                case 4:   // Destroy Dimension data
                {
                
                break;
                }
                case 5:   // Destroy connected Dimension data
                {
                
                break;
                }
                break;
                
                default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
            }
        }
    
    if ( point_move[dimension_loop] > point_move_max[dimension_loop] )
        {
            //        std::cout << "MoveMax called." << std::endl;
        switch (point_move_max_overflow[dimension_loop])
            {
                case 0:   // Stay at Min/Max value
                {
                point_move[dimension_loop] = point_move_max[dimension_loop];
                point_differential[dimension_loop] = 0;
                break;
                }
                case 1:   // Wrap value
                {
                point_move[dimension_loop] = point_move_max[dimension_loop] + ( point_move[dimension_loop] - point_move_min[dimension_loop] );
                break;
                }
                case 2:   // Bounce value
                {
                point_move[dimension_loop] = point_move_max[dimension_loop] - ( point_move[dimension_loop] - point_move_max[dimension_loop] );
                point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
                break;
                }
                case 3:   // Make hidden
                {
                
                break;
                }
                case 4:   // Destroy Dimension data
                {
                
                break;
                }
                case 5:   // Destroy connected Dimension data
                {
                
                break;
                }
                break;
                
                default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
            }
        }
    
    if ( point_differential[dimension_loop] < point_differential_min[dimension_loop] )
        {
            //        std::cout << "DifferentialMin called." << std::endl;
        switch (point_differential_min_overflow[dimension_loop])
            {
                case 0:   // Stay at Min/Max value
                {
                point_differential[dimension_loop] = point_differential_min[dimension_loop];
                break;
                }
                case 1:   // Wrap value
                {
                point_differential[dimension_loop] = point_differential_min[dimension_loop] + ( point_differential[dimension_loop] - point_differential_max[dimension_loop] );
                break;
                }
                case 2:   // Bounce value
                {
                point_differential[dimension_loop] = point_differential_min[dimension_loop] + ( point_differential_min[dimension_loop] - point_differential[dimension_loop] );
                    //point_move[dimension_loop] = 0 - point_move[dimension_loop];
                    //            point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
                break;
                }
                case 3:   // Make hidden
                {
                
                break;
                }
                case 4:   // Destroy Dimension data
                {
                
                break;
                }
                case 5:   // Destroy connected Dimension data
                {
                
                break;
                }
                break;
                
                default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
            }
        }
    
    if ( point_differential[dimension_loop] > point_differential_max[dimension_loop] )
        {
            //        std::cout << "DifferentialMax called." << std::endl;
        switch (point_differential_max_overflow[dimension_loop]) {
            case 0:   // Stay at Min/Max value
            {
            point_differential[dimension_loop] = point_differential_max[dimension_loop];
            break;
            }
            case 1:   // Wrap value
            {
            point_differential[dimension_loop] = point_differential_min[dimension_loop] + ( point_differential[dimension_loop] - point_differential_max[dimension_loop] );
            break;
            }
            case 2:   // Bounce value
            {
            point_differential[dimension_loop] = point_differential_max[dimension_loop] - ( point_differential[dimension_loop] - point_differential_max[dimension_loop] );
                //            point_move[dimension_loop] = 0 - point_move[dimension_loop];
                //point_differential[dimension_loop] = 0 - point_differential[dimension_loop];
            break;
            }
            case 3:   // Make hidden
            {
            
            break;
            }
            case 4:   // Destroy Dimension data
            {
            
            break;
            }
            case 5:   // Destroy connected Dimension data
            {
            
            break;
            }
                break;
                
            default:
            {std::cout << "Overflow not catered for." << std::endl; }
                
                break;
        }
        }
    
        }
}

int Point::Update(std::chrono::time_point<Clock> event_time)
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
        Universe* myUniverse;
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &myUniverse->object_energy, object_energy * 0.1, 10000, 1);
        // time_dimension_pointer->AddTemporalAdjustment(event_time, &object_energy, 0 - (object_energy * 0.1), 10000, 1);
        PointPoll(event_time, 1);
        }
    
        // Clock duration does not consider parallel or serial operation
    previous_event_time = event_time;
        }
    return 0;
}

