    //
/*------------------------------------------------------------------------------*/
/* @file      point.h                                                         */
/* @details   Single dimension point operations. Can be combined for multidimension */
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

#ifndef BRAINHARMONICS_POINT_H
#define BRAINHARMONICS_POINT_H

#include <chrono>
#include <iostream>
#include <math.h>
#include "universe.h"

class Point : public Universe
{
    friend class ElementaryParticle;
    friend class ElementaryForce;
    friend class CompositeForceParticle;
    friend class Polyhedron;

public:
    Point() : Point(0) {}
    
    Point(unsigned int object_type) : Point(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Point(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Point(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each point type will have its own parameter ranges. The default is 0
    point_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Point", point_type);
    
        // Attach object to new dimension for time based calculations
    time_dimension_pointer = AddDimension(event_time);
    time_dimension_pointer->SetObjectType(event_time, 1); // Set non-default dimension type
    }
    /** Default destructor */
    virtual ~Point() {} // {std::cout << "Point removed." << std::endl; }
    
    /** Access member variable values     */
    int    GetPointSeq(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_seq; }
    
    std::vector<double> GetPointScale(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_scale;}
    std::vector<double> GetPointPosition(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_position; }
    std::vector<double> GetPointPosition2(std::chrono::time_point<Clock> event_time)
    {
    std::vector<double> result;
    result.clear();
    for(std::vector<double>::iterator it = point_position.begin(); it != point_position.end(); ++it)
        {
        result.push_back(double(*it * *it));
        }
    return result;
    }
    
    std::vector<double> GetPointPositionMin(std::chrono::time_point<Clock> event_time)         { return point_position_min; }
    std::vector<int>    GetPointPositionMinOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_position_min_overflow; }
    std::vector<double> GetPointPositionMax(std::chrono::time_point<Clock> event_time)         { return point_position_max; }
    std::vector<int>    GetPointPositionMaxOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_position_max_overflow; }
    
    std::vector<double> GetPointMove(std::chrono::time_point<Clock> event_time)                { return point_move; }
    std::vector<double> GetPointMoveMin(std::chrono::time_point<Clock> event_time)             { return point_move_min; }
    std::vector<int>    GetPointMoveMinOverflow(std::chrono::time_point<Clock> event_time)     { return point_move_min_overflow; }
    std::vector<double> GetPointMoveMax(std::chrono::time_point<Clock> event_time)             { return point_move_max; }
    std::vector<int>    GetPointMoveMaxOverflow(std::chrono::time_point<Clock> event_time)     { return point_move_max_overflow; }
    
    std::vector<double> GetPointDifferential(std::chrono::time_point<Clock> event_time)            { return point_differential; }
    std::vector<double> GetPointDifferentialMin(std::chrono::time_point<Clock> event_time)         { return point_differential_min; }
    std::vector<int>    GetPointDifferentialMinOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_differential_min_overflow; }
    std::vector<double> GetPointDifferentialMax(std::chrono::time_point<Clock> event_time)         { return point_differential_max; }
    std::vector<int>    GetPointDifferentialMaxOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_differential_max_overflow; }
    
    double GetPointTTL(std::chrono::time_point<Clock> event_time)            { return point_TTL; }
    double GetPointTTLMin(std::chrono::time_point<Clock> event_time)         { return point_TTL_min; }
    int    GetPointTTLMinOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_TTL_min_overflow; }
    double GetPointTTLMax(std::chrono::time_point<Clock> event_time)         { return point_TTL_max; }
    int    GetPointTTLMaxOverflow(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return point_TTL_max_overflow; }
    
    /** Set member variable values */
    std::vector<double> RespectLimits(std::chrono::time_point<Clock> event_time, std::vector<double> val)
    {
    if(point_position.size() < 1 || point_position.size() > 2)
        {
        if(val.size() > 2)
        {
        for(int reduction_loop = 0; reduction_loop < val.size(); reduction_loop++)
            {
            if(val[reduction_loop] < -1)
                {
                val[reduction_loop] = (2 / val[reduction_loop]) + 1;
                }
            if(val[reduction_loop] > 1)
                {
                val[reduction_loop] = (2 / val[reduction_loop]) - 1;
                }
            }
        }
        }
    return val;
    }
    
    void SetObjectType(std::chrono::time_point<Clock> event_time, unsigned int val);

    void SetPointSeq(std::chrono::time_point<Clock> event_time, int val) { point_seq = val; }
    
    void SetPointScale(std::chrono::time_point<Clock> event_time, std::vector<double> val) {point_scale = val; }
    void SetPointPosition(std::chrono::time_point<Clock> event_time, std::vector<double> val)
    {
        point_position = RespectLimits(event_time, val);
    }
    void SetPointPositionMin(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_position_min = RespectLimits(event_time, val); }
    void SetPointPositionMinOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_position_min_overflow = val; }
    void SetPointPositionMax(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_position_max = RespectLimits(event_time, val); }
    void SetPointPositionMaxOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_position_max_overflow = val; }
    
    void SetPointMove(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_move = RespectLimits(event_time, val); }
    void SetPointMoveMin(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_move_min = RespectLimits(event_time, val); }
    void SetPointMoveMinOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_move_min_overflow = val; }
    void SetPointMoveMax(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_move_max = RespectLimits(event_time, val); }
    void SetPointMoveMaxOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_move_max_overflow = val; }
    
    void SetPointDifferential(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_differential = RespectLimits(event_time, val); }
    void SetPointDifferentialMin(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_differential_min = RespectLimits(event_time, val); }
    void SetPointDifferentialMinOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_differential_min_overflow = val; }
    void SetPointDifferentialMax(std::chrono::time_point<Clock> event_time, std::vector<double> val) { point_differential_max = RespectLimits(event_time, val); }
    void SetPointDifferentialMaxOverflow(std::chrono::time_point<Clock> event_time, std::vector<int> val) { point_differential_max_overflow = val; }
    
    void SetPointTTL(std::chrono::time_point<Clock> event_time, double val) { point_TTL = val; }
    void SetPointTTLMin(std::chrono::time_point<Clock> event_time, double val) { point_TTL_min = val; }
    void SetPointTTLMinOverflow(std::chrono::time_point<Clock> event_time, int val) { point_TTL_min_overflow = val; }
    void SetPointTTLMax(std::chrono::time_point<Clock> event_time, double val) { point_TTL_max = val; }
    void SetPointTTLMaxOverflow(std::chrono::time_point<Clock> event_time, int val) { point_TTL_max_overflow = val; }
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);
    
    void PointForcePoll(std::chrono::time_point<Clock> event_time, Point* opposingPoint);

    int Update(std::chrono::time_point<Clock> event_time);

    void PointPoll(std::chrono::time_point<Clock> event_time, double val);
    
    void OverflowPoll(std::chrono::time_point<Clock> event_time);
    
protected:
    
private:
    int    point_seq;                      //!< Member variable "point_seq"
    int    point_type;                     //!< Member variable "point_type"
    bool   object_disabled = true;                //!< Member variable "object_disabled"
    bool   object_initialised = false;
    std::vector<double> point_scale;                    //!< Member variable "point_scale"
    std::vector<double> point_position;                 //!< Member variable "point_position"
    std::vector<double> point_position_min;             //!< Member variable "point_position_min"
    std::vector<int>    point_position_min_overflow;    //!< Member variable "point_position_min_overflow"
    std::vector<double> point_position_max;             //!< Member variable "point_position_max"
    std::vector<int>    point_position_max_overflow;    //!< Member variable "point_position_max_overflow"
    
    std::vector<double> point_move;                     //!< Member variable "point_move"
    std::vector<double> point_move_min;                 //!< Member variable "point_move_min"
    std::vector<int>    point_move_min_overflow;        //!< Member variable "point_move_min_overflow"
    std::vector<double> point_move_max;                 //!< Member variable "point_move_max"
    std::vector<int>    point_move_max_overflow;        //!< Member variable "point_move_max_overflow"
    
    std::vector<double> point_differential;             //!< Member variable "point_differential"
    std::vector<double> point_differential_min;         //!< Member variable "point_differential_min"
    std::vector<int>    point_differential_min_overflow;//!< Member variable "point_differential_min_overflow"
    std::vector<double> point_differential_max;         //!< Member variable "point_differential_max"
    std::vector<int>    point_differential_max_overflow;//!< Member variable "point_differential_max_overflow"
    
    double point_TTL;                      //!< Member variable "point_TTL"
    double point_TTL_min;                  //!< Member variable "point_TTL_min"
    int    point_TTL_min_overflow;         //!< Member variable "point_TTL_min_overflow"
    double point_TTL_max;                  //!< Member variable "point_TTL_max"
    int    point_TTL_max_overflow;         //!< Member variable "point_TTL_max_overflow"
    
    std::vector<double> combined_acceleration;          //!< Member variable "combined_acceleration"
    std::vector<double> distance_apart;                 //!< Member variable "distance_apart"
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;

};

#endif // BRAINHARMONICS_POINT_H
