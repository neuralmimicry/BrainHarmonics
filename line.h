/*------------------------------------------------------------------------------*/
/* @file      line.h                                                            */
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

#ifndef BRAINHARMONICS_LINE_H
#define BRAINHARMONICS_LINE_H

//#include <algorithm>
#include <math.h>               /**< For Sine, Cosine, Fabs & Sqrt functions */
#include <iostream>
#include "universe.h"

class Line : public Universe
{
public:
    Line() : Line(0) {}
    
    Line(unsigned int object_type) : Line(object_type, std::chrono::high_resolution_clock::now()) {}
    
    Line(unsigned int object_type, std::chrono::time_point<Clock> event_time) : Universe() {}
    
    Line(unsigned int object_type, std::chrono::time_point<Clock> event_time, Universe& universe_connector) : Universe(universe_connector)
    {
        // Each line type will have its own parameter ranges. The default is 0
    line_type = object_type;
    time_object_created = event_time;
        // Each new object has its default parameters set here.
    ResetParameters(event_time);
    
        // Call to announce object creation
    Creation(time_object_created, "Line", line_type);
    object_disabled = true;
    }
    /** Default destructor */
    virtual ~Line() {}
    /** Access lineCounter
     * \return The current value of lineCounter
     */
    
    bool ResetParameters(std::chrono::time_point<Clock> event_time);

    int GetLineID(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return lineLineID; }
    double GetLineXYBubble(std::chrono::time_point<Clock> event_time) const { return std::max(GetLineX1Y1Bubble(event_time), GetLineX2Y2Bubble(event_time)); }
    double GetLineX1(std::chrono::time_point<Clock> event_time) const { return lineLineX1; }
    double GetLineY1(std::chrono::time_point<Clock> event_time) const { return lineLineY1; }
    double GetLineX1Y1Bubble(std::chrono::time_point<Clock> event_time) const { return ((lineLineX1 * lineLineX1) + (lineLineY1 * lineLineY1)); }
    double GetLineX2(std::chrono::time_point<Clock> event_time) const { return lineLineX2; }
    double GetLineY2(std::chrono::time_point<Clock> event_time) const { return lineLineY2; }
    double GetLineX2Y2Bubble(std::chrono::time_point<Clock> event_time) const { return ((lineLineX2 * lineLineX2) + (lineLineY2 * lineLineY2)); }
    double GetLineXMin(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return (std::min(lineLineX1, lineLineX2)); }
    double GetLineYMin(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return (std::min(lineLineY1, lineLineY2)); }
    double GetLineXMax(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return (std::max(lineLineX1, lineLineX2)); }
    double GetLineYMax(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return (std::max(lineLineY1, lineLineY2)); }
    double GetLineMinOrdinal(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return std::min(std::min(lineLineX1,lineLineX2),std::min(lineLineY1, lineLineY2)); }
    double GetLineMaxOrdinal(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return std::max(std::max(lineLineX1,lineLineX2),std::max(lineLineY1, lineLineY2)); }
    double GetSlope(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return lineSlope; }
    double GetYint(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return lineYint; }
    double GetLineTTL(std::chrono::time_point<Clock> event_time) const { return lineLineTTL; }
    int GetLineSeq(std::chrono::time_point<Clock> event_time) { std::chrono::time_point<Clock> last_event_time = event_time; return lineLineSeq; }
    int GetLineCounter(std::chrono::time_point<Clock> event_time) const { return lineLineCounter; }
    bool GetInLine(std::chrono::time_point<Clock> event_time, double X1, double Y1, double X2, double Y2, double Threshold)
    {
    if( fabs(pow((lineSlope * X1 + lineYint),2) - pow(Y1,2)) > pow(Threshold,2)) {return false;}
    if( fabs(pow((lineSlope * X2 + lineYint),2) - pow(Y2,2)) > pow(Threshold,2)) {return false;}
    if( fabs(pow((Y1 - lineYint) / lineSlope,2) - pow(X1,2)) > pow(Threshold,2)) {return false;}
    if( fabs(pow((Y2 - lineYint) / lineSlope,2) - pow(X2,2)) > pow(Threshold,2)) {return false;}
    if( fabs((pow(X1,2) + pow(Y1,2)) - (pow(X2,2) + pow(Y2,2))) > fabs((pow(lineLineX1,2) + pow(lineLineY1,2)) - (pow(lineLineX2,2) + pow(lineLineY2,2)))) {return false;}
    return true;
    }
    /** set lineCounter
     * \param val New value to set
     */
    void setLineID(std::chrono::time_point<Clock> event_time, int val) { lineLineID = val; }
    void setLineX1(std::chrono::time_point<Clock> event_time, double val) { lineLineX1 = val; }
    void setLineY1(std::chrono::time_point<Clock> event_time, double val) { lineLineY1 = val; }
    void setLineX2(std::chrono::time_point<Clock> event_time, double val) { lineLineX2 = val; }
    void setLineY2(std::chrono::time_point<Clock> event_time, double val) { lineLineY2 = val; }
    void setSlope(std::chrono::time_point<Clock> event_time, double val) { lineSlope = val; }
    void setYint(std::chrono::time_point<Clock> event_time, double val) { lineYint = val; }
    void setLineTTL(std::chrono::time_point<Clock> event_time, double val) { lineLineTTL = val; }
    void setLineSeq(std::chrono::time_point<Clock> event_time, int val) { lineLineSeq = val; }
    void setLineCounter(std::chrono::time_point<Clock> event_time, int val) { lineLineCounter = val; }

    int Update(std::chrono::time_point<Clock> event_time);
    
protected:
private:
    int lineLineID;
    int line_type;
    double lineLineX1; //!< Member variable "lineLineX1"
    double lineLineY1; //!< Member variable "lineLineY1"
    double lineLineX2; //!< Member variable "lineLineX2"
    double lineLineY2; //!< Member variable "lineLineY2"
    double lineSlope; //!< Member variable "lineSlope"
    double lineYint; //!< Member variable "lineYint"
    double lineLineTTL; //!< Member variable "lineLineTTL"
    int lineLineSeq;
    int lineLineCounter;
    std::chrono::time_point<Clock> time_object_created;
    std::chrono::time_point<Clock> previous_event_time;
    int duration_since_last_event;
    bool object_disabled;
    bool object_initialised;
};

#endif // BRAINHARMONICS_LINE_H
