    //
/*---------------------------------------------------------------------------------*/
/* @file      main.cpp                                                             */
/* @details   Brain Harmonics - using harmonics to store and process neural spikes */
/* @author    Paul Isaac's                                                         */
/* @date      03.02.2016                                                           */
/* @Copyright © 2016 Paul Isaac's. All rights reserved.                            */
/*---------------------------------------------------------------------------------*/

/* Code snippets used:                                                             */
/* Syntax comparison - http://stackoverflow.com & http://cplusplus.com             */
/* The program works on the principle of clustering data points received by        */
/*                                                                                 */
/* Using the hierarchical linking the aim is to develop the application to         */
/* relate to real-world physics. This will then ease mapping between simulation,   */
/* emulation and real-world Universes.                                             */

    //extern "C" {
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
    //}

    // Standard Template Libraries (STL)
#include <algorithm>            /**< For max, min, sort function                   */
#include <array>                /**< For array in CRC-32 call                      */
#include <cstring>              /**< For handling strings                          */
#include <cstdint>              /**< For byte handling in CRC-32                   */
#include <fstream>              /**< For reading files                             */
#include <iomanip>              /**< Formatting output to console                  */
#include <iostream>             /**< For output to console                         */
#include <map>                  /**< For open and closed maps in A*                */
#include <math.h>               /**< For Sine, Cosine, Power, Fabs & Sqrt functions*/
#include <numeric>              /**< For CRC-32                                    */
#include <queue>                /**< For assigning priority queue in A*            */
#include <sstream>              /**< For stringstream input from console           */
#include <string>               /**< For handling strings                          */
#include <vector>               /**< To use vectors, which automatically handle resizing, as arrays to keep track of instances */

    // SFML - Use DYLIBS not FRAMEWORKS. FRAMEWORKS had a problem with Text and missing symbols
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>    /**< Graphics library http://sfml-dev.org          */
    //#include "ResourcePath.hpp"

    // Interim calls to Python (2.7) to use existing APIs to Neuromorphic hardware
#include <Python.h>             /**< Python interpreter                            */
#include <numpy/arrayobject.h>

    // GLUT on El Capitan - poor headers
 #ifdef __APPLE__
 #include <GLUT/glut.h>
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
 #else
 #ifdef _WIN32
 #include <windows.h>
 #endif
 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <GL/glut.h>
 #endif

    // To use the std:: files
    //#define IL_STD
    //#include <ilcplex/ilocplex.h>
    //ILOSTLBEGIN

    // Homegrown add-ins
#include <universe.h>           /**< Top of the tree, begin with Universe class    */
#include <dimension.h>          /**< Add Dimensions for spatial identification     */
#include <elementaryparticle.h> /**< Follow with the creation of quarks/leptons    */
#include <compositeparticle.h>  /**< Basic interactions form protons/neutrons      */
#include <elementaryforce.h>    /**< Define Force interaction between fundamentals */
#include <compositeforce.h>     /**< Define Force interaction between Composites   */
#include <law.h>                /**< Specify how Composites interact               */
#include <matter.h>             /**< Composites form elements of periodic table    */
#include <monomer.h>            /**< Composites form molecules                     */
#include <polymer.h>            /**< Composites form molecules                     */
#include <solid.h>              /**< Materials are a combination of Matter         */
#include <polyhedron.h>         /**< Materials can be formed into multiDimensional shapes */
#include <polygon.h>            /**< Complex shapes are a combination of simpler forms */
#include <quad.h>               /**< Reducing high Dimensions to lower             */
#include <line.h>               /**< Further reduction                             */
#include <point.h>              /**< Fundamental spatial description               */
#include <node.h>               /**< Node class for A* search                      */
#include <apptimer.h>           /**< Interim function describing time before inclusion as Dimension */

    // CCP specific add-ins
#include <customer.h>         /**< Details of customer                           */
#include <warehouse.h>        /**< Details of warehouse                          */

    // Application specific add-ins
#include "neuron.hpp"           /**< Neuron container for other neuron components  */
#include "dendritecleft.hpp"    /**< Dendritic synaptic cleft, input to the neuron */
#include "neuroreceptor.hpp"    /**< Neuroreceptor, component of dendritic cleft   */
#include "synapse.hpp"          /**< Synapse, area of stimulus transmission/reception */
#include "membrane.hpp"         /**< Membrane, outer component of the neuron       */
#include "Kchannel.hpp"         /**< Potassium channel, component of the membrane  */
#include "Nachannel.hpp"        /**< Sodium channel, component of the membrane     */
#include "dendrite.hpp"         /**< Dendrite, pre-Soma component of a neuron      */
#include "dendritebranch.hpp"   /**< Dendrite branch, division/join of dendrites   */
#include "soma.hpp"             /**< Soma, component of a neuron                   */
#include "axonhillock.hpp"      /**< Axon Hillock, component of Soma               */
#include "axon.hpp"             /**< Axon, connected to Axon Hillock               */
#include "axonbranch.hpp"       /**< Axon branch, division/join of Axon            */
#include "myelinsheath.hpp"     /**< Myelin sheath, wraps around Axon              */
#include "schwanncell.hpp"      /**< Schwann Cell, component of a Myelin sheath    */
#include "axoncleft.hpp"        /**< Axon synaptic cleft, output area of neuron    */
#include "synapticvesicle.hpp"  /**< Synaptic vesicle, container of neurotransmitters */
#include "Cagate.hpp"           /**< Calcium gate, component of Axon cleft         */
#include "neurotransmitter.hpp" /**< Neurotransmitter, transfer component between clefts */
#include "spike.hpp"            /**< Spikes                                        */
#include "multiscreen.h"        /**< Screen layouts                                */

#ifndef DEBUG_PROGRAM
#define DEBUG_PROGRAM true
#endif // DEBUG_PROGRAM

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif // INVALID_SOCKET

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

#ifndef SOCKET_PORT
#define SOCKET_PORT 9876
#endif // SOCKET_PORT

#ifndef SOCKET_ADDRESS
#define SOCKET_ADDRESS "192.168.42.56"    // Change to the IP address of the computer running the middleware portion of the project
#endif // SOCKET_ADDRESS

    // Handy conversions
#ifndef DEG2RAD
#define DEG2RAD 0.01745329252f  /**< Avoids having to recalculate a constant PI/180 */
#endif // DEG2RAD

#ifndef RAD2DEG
#define RAD2DEG 57.29577951f    /**< Avoids having to recalculate a constant 180/PI */
#endif // RAD2DEG

#ifndef ONERAD
#define ONERAD 3.14159265f    /**< Avoids having to recalculate */
#endif // ONERAD

#ifndef GRAVITY
#define GRAVITY 6.67384e-11;
#endif // GRAVITY

float g_speed;                      /**< Speed of robot */
float g_deltaheading;               /**< Change current angle of robot by this amount */
float g_toggle = 0;                 /**< Discover or localise */
bool g_buttonPressed = false;

bool msg_handling(std::vector <std::string> *m_messages, bool m_response, int m_ok, int m_fail)
{
    if(DEBUG_PROGRAM)
        {
        if(m_response)
            {
            std::cout << (*m_messages)[m_ok] << std::endl;
            }
        else
            {
            std::cout << (*m_messages)[m_fail] << std::endl;
            sleep(1);
            }
        }
    return true;
}

    // Function to create a Universe instance. Universes could be simulation, emulation, real or contemplative (What-if)
int create_Universe(std::vector<Universe> *toAddto)
{
        // First, there is nothing. Then there was something...
    double UniverseEnergy = 999999999;              /**< Defined energy level of Universe */
        // Begin with singularity
    Universe myUniverse(0.9);                            /**< Create instance of Universe from Universe class */
    /**< Set an energy level and attempt to maintain physics laws by keeping the total in the Universe the same. Uses the maximum value for double. Levels of abstraction used to cater for environment limitations */
    myUniverse.setEnergy(UniverseEnergy);
        // Use move not push_back otherwise data is destroyed on exiting function
        //    std::copy(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));
    std::copy(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding Dimensions enables physical and spatial calculations
    // Possible to use this as a basis for higher dimensionality if it becomes relevant
int add_Dimension(std::vector<Dimension> *toAddto, std::vector<Universe> *aPartof, int arrayEntry)
{
    Dimension myDimension((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myDimension, &myDimension + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Each add_ function creates an instance of the respective class and links back to the base class
    // For definition of quarks and leptons when simulating real-world environment
int add_ElementaryParticle(std::vector<ElementaryParticle> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
    ElementaryParticle myElementaryParticle((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myElementaryParticle, &myElementaryParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // For real-world definition of protons & neutrons. Other combinations in artificial environments
int add_CompositeParticle(std::vector<CompositeParticle> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    CompositeParticle myCompositeParticle((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myCompositeParticle, &myCompositeParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Methods in this class to define interaction. Which may be different between artificial, simulation and real environments
int add_ElementaryForce(std::vector<ElementaryForce> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    ElementaryForce myForce((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

int add_CompositeForce(std::vector<CompositeForce> *toAddto, std::vector<CompositeParticle> *aPartof, int arrayEntry)
{
    CompositeForce myForce((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Add methods to describe Force interactions such as gravity
int add_Law(std::vector<CompositeForce> *toAddto, int arrayEntry, std::vector<CompositeParticle> *toAddto2, int arrayEntry2)
{
        //    law myLaw(aPartof[arrayEntry], toAddto2[arrayEntry2]);
        // Use move not push_back otherwise data is destroyed on exiting function
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of periodic table of elements
int add_Matter(std::vector<Matter> *toAddto, std::vector<CompositeParticle> *aPartof, int arrayEntry)
{
    Matter myMatter((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myMatter, &myMatter + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of simple molecules
int add_Monomer(std::vector<Monomer> *toAddto, std::vector<Matter> *aPartof, int arrayEntry)
{
    Monomer myMonomer((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myMonomer, &myMonomer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of complex molecules
int add_Polymer(std::vector<Polymer> *toAddto, std::vector<Monomer> *aPartof, int arrayEntry)
{
    Polymer myPolymer((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myPolymer, &myPolymer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Description of material
int add_Solid(std::vector<Solid> *toAddto, std::vector<Matter> *aPartof, int arrayEntry)
{
    Solid mySolid((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&mySolid, &mySolid + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Fundamental spatial element
int add_Point(std::vector<Point> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
        // Begin with shape singularity
    Point myPoint((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myPoint, &myPoint + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Complex shapes
int add_Polyhedron(std::vector<Polyhedron> *toAddto, std::vector<Solid> *aPartof, int arrayEntry)
{
    Polyhedron myPolyhedron((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myPolyhedron, &myPolyhedron + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Components of complex shapes
int add_Polygon(std::vector<Polygon> *toAddto, std::vector<Polyhedron> *aPartof, int arrayEntry)
{
    Polygon myPolygon((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myPolygon, &myPolygon + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Base 2D shapes
int add_Quad(std::vector<Quad> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Quad myQuad((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myQuad, &myQuad + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Component of shapes, straight, curved or complex
int add_Line(std::vector<Line> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Line myLine((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myLine, &myLine + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Component of the brain
    //int add_Neuron(std::vector<neuron> *toAddto, std::vector<Polymer> *aPartof, int arrayEntry)
int add_Neuron(std::vector<neuron> *toAddto)
{
    neuron myNeuron;
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myNeuron, &myNeuron + 1, std::back_inserter(*toAddto));
    
        //    std::cout << "Neuron added." << std::endl;
    return 0;                       /**< Return Success = 0 */
}

int add_Spike(std::vector<Spike> *toAddto)
{
    Spike mySpike;
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&mySpike, &mySpike + 1, std::back_inserter(*toAddto));
    
        //    std::cout << "Spike added." << std::endl;
    return 0;                       /**< Return Success = 0 */
}

    // Each add_ function creates an instance of the respective class and links back to the base class
    // For definition of Warehouses and Customers when simulating CPP environment
int add_Warehouse(std::vector<Warehouse> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
    Warehouse myWarehouse((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myWarehouse, &myWarehouse + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // For CPP definition of Customers. Other combinations in artificial environments
int add_Customer(std::vector<Customer> *toAddto, std::vector<Warehouse> *aPartof, int arrayEntry)
{
    Customer myCustomer((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myCustomer, &myCustomer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding application timer temporarily until integrated into Dimension class
int add_Apptimer(std::vector<Apptimer> *toAddto)
{
    Apptimer myApptimer;
        // Use move not push_back otherwise data is destroyed on exiting function
    std::copy(&myApptimer, &myApptimer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

int add_SFMLRectangle(std::vector<sf::RectangleShape> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
    sf::RectangleShape mySFMLRectangle;
    mySFMLRectangle.setSize(sf::Vector2f(1,1));
    mySFMLRectangle.setOutlineColor(sf::Color::Green);
    mySFMLRectangle.setOutlineThickness(1);
    mySFMLRectangle.setFillColor(sf::Color::Green);
    mySFMLRectangle.setPosition(sf::Vector2f(0,0));
    
    std::copy(&mySFMLRectangle, &mySFMLRectangle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

int add_SFMLText(std::vector<sf::Text> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry, sf::Font *font)
{
    sf::Text mySFMLText;
    std::stringstream l_displayString;
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << " ";
    mySFMLText.setFont(*font);
    mySFMLText.setString(l_displayString.str());
    mySFMLText.setCharacterSize(10);
        // Fill & Outline replaces deprecated setColor. Also means DYLIBS is used now not FRAMEWORKS for linking
    mySFMLText.setFillColor(sf::Color::Green);
    mySFMLText.setOutlineColor(sf::Color::Green);
    mySFMLText.setStyle(sf::Text::Bold);
    
    std::copy(&mySFMLText, &mySFMLText + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Test which Candidate is closest to being 3 away in the charge values and move that Candidate next to the Origin.
bool compare_swapElementaryParticle(std::vector<ElementaryParticle> *origin, int l_origin_Swap, int l_origin_Candidate1, int l_origin_Candidate2)
{
    bool l_switch = true;
    int l_origin = (*origin)[l_origin_Swap].getCharge();
    int l_origin_Test1 = (*origin)[l_origin_Candidate1].getCharge();
    int l_origin_Test2 = (*origin)[l_origin_Candidate2].getCharge();
    int l_origin_Test3 = std::abs(l_origin - l_origin_Test1);
    int l_origin_Test4 = std::abs(l_origin - l_origin_Test2);
    int l_origin_Test5 = (3 - l_origin_Test3);
    int l_origin_Test6 = (3 - l_origin_Test4);
    
    l_switch = false;
    
    if(l_origin_Test5 > l_origin_Test6 && l_origin != l_origin_Candidate2)
        {
            //        std::cout << "Before: " << l_origin << " " << l_origin_Test1 << " " << l_origin_Test2 << std::endl;
        iter_swap((*origin).begin() + l_origin_Candidate1, (*origin).begin() + l_origin_Candidate2);
            //        std::cout << "After : " << (*origin)[l_origin_Swap].getCharge() << " " << (*origin)[l_origin_Candidate1].getCharge() << " " << (*origin)[l_origin_Candidate2].getCharge() << std::endl;
        l_switch = true;
        }
    
    return l_switch; // Return answering whether or not an exchange occurred
}

int distanceBetweenNodes(std::vector<Point> *nodesQuery, std::vector<int> *nodesList, int nodesDimensions, double desiredDistance )
{
    double firstX;
    double firstY;
    double firstZ;
    double secondX;
    double secondY;
    double secondZ;
    double direction;
    double diffX;
    double diffY;
    double diffZ;
    double diffX2;
    double diffY2;
    double diffZ2;
    double slope;
    double actualDistance;
    double angleRAD;
    double angleDEG;

        //    std::cout << "Received nodes: " << (*nodesList)[0] << ", " << (*nodesList)[1] << ", " << (*nodesList)[2] << ", " << (*nodesList)[3] << std::endl;

    firstX = (*nodesQuery)[(*nodesList)[0]].getPointPosition();
    firstY = (*nodesQuery)[(*nodesList)[1]].getPointPosition();
    secondX = (*nodesQuery)[(*nodesList)[2]].getPointPosition();
    secondY = (*nodesQuery)[(*nodesList)[3]].getPointPosition();
    diffX = firstX - secondX;
    diffX2 = diffX * diffX;
    diffY = firstY - secondY;
    diffY2 = diffY * diffY;
    slope = diffY / diffX;
    actualDistance = fabs(sqrt(diffX2 + diffY2));
    angleRAD = atan2(diffY,diffX);
    angleDEG = angleRAD * RAD2DEG;
    
    if(firstX < secondX && firstY > secondY)
        {
        angleDEG = angleDEG + 90;
        }
    
    if(firstX > secondX && firstY > secondY)
        {
        angleDEG = angleDEG + 180;
        }
    
    if(firstX > secondX && firstY < secondY)
        {
        angleDEG = angleDEG + 270;
        }
    
    angleRAD = angleDEG * DEG2RAD;
    
    direction = actualDistance - desiredDistance;
    
    if(direction > -1000 and direction < 1000)
        {
            //        diffX = 0;
            //        diffY = 0;
        
/*
        if(desiredDistance < actualDistance)
            {
            diffX = sin(angleRAD);
            diffY = cos(angleRAD);
            }

        if(desiredDistance > actualDistance)
            {
            diffX = sin(angleRAD + ONERAD);
            diffY = cos(angleRAD + ONERAD);
            }
*/
        diffX = actualDistance * cos(diffX / actualDistance);
        diffY = actualDistance * sin(diffY / actualDistance);
        
        
            //                  std::cout << "(" << firstX << "," << firstY << ") (" << secondX << "," << secondY << ") " << desiredDistance << ":" << direction << " <" << angleDEG << " = (" << diffX << "," << diffY << ")" << std::endl;
/*
        if(desiredDistance != 0)
            {
            if((actualDistance / desiredDistance) > 0.95 && (actualDistance / desiredDistance) < 1.05)
                {
                (*nodesQuery)[(*nodesList)[0]].setPointDifferential(0);
                (*nodesQuery)[(*nodesList)[0]].setPointMove(0);
                (*nodesQuery)[(*nodesList)[1]].setPointDifferential(0);
                (*nodesQuery)[(*nodesList)[1]].setPointMove(0);
 */
                /*
                 (*nodesQuery)[(*nodesList)[2]].setPointDifferential(0);
                 (*nodesQuery)[(*nodesList)[2]].setPointMove(0);
                 (*nodesQuery)[(*nodesList)[3]].setPointDifferential(0);
                 (*nodesQuery)[(*nodesList)[3]].setPointMove(0);
                 */
        /*
                }
            else
                {
         */
                (*nodesQuery)[(*nodesList)[0]].setPointDifferential((((*nodesQuery)[(*nodesList)[0]].getPointDifferential() + diffX)/2));
                (*nodesQuery)[(*nodesList)[1]].setPointDifferential((((*nodesQuery)[(*nodesList)[1]].getPointDifferential() + diffY)/2));
                    //                (*nodesQuery)[(*nodesList)[2]].setPointDifferential((((*nodesQuery)[(*nodesList)[2]].getPointDifferential() - diffX)/2));
                    //                (*nodesQuery)[(*nodesList)[3]].setPointDifferential((((*nodesQuery)[(*nodesList)[3]].getPointDifferential() - diffY)/2));
                
                    //                std::cout << "Amended : " << (*nodesQuery)[(*nodesList)[0]].getPointDifferential() << ", " << (*nodesQuery)[(*nodesList)[1]].getPointDifferential() << ", " << (*nodesQuery)[(*nodesList)[2]].getPointDifferential() << ", " << (*nodesQuery)[(*nodesList)[3]].getPointDifferential() << std::endl;
                    //                }
                    //            }
        }
    return EXIT_SUCCESS;
}

    // Test which Candidate is closest in the charge values and move that Candidate next to the Origin.
bool compare_swapCompositeParticle(std::vector<CompositeParticle> *origin, int l_origin_Swap, int l_origin_Candidate1, int l_origin_Candidate2)
{
    bool l_switch = true;
    int l_origin = (*origin)[l_origin_Swap].getCharge();
    int l_origin_Test1 = (*origin)[l_origin_Candidate1].getCharge();
    int l_origin_Test2 = (*origin)[l_origin_Candidate2].getCharge();
    int l_origin_Test3 = l_origin_Test1 - l_origin;
    int l_origin_Test4 = l_origin_Test2 - l_origin;
    int l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
    int l_origin_Test6 = l_origin_Test4 * l_origin_Test4;
    
    l_switch = false;
    
    if(l_origin_Test5 < l_origin_Test6)
        {
        iter_swap((*origin).begin() + l_origin_Candidate1, (*origin).begin() + l_origin_Candidate2);
        l_switch = true;
        }
    
    return l_switch; // Return answering whether or not an exchange occurred
}

    // Test which Candidate is closest to being 3 away in the charge values and move that Candidate next to the Origin.
bool compare_swapCustomer(std::vector<Customer> *origin, int l_origin_Swap, int l_origin_Candidate1, int l_origin_Candidate2)
{
    bool l_switch = true;
    int l_origin = (*origin)[l_origin_Swap].getDemand();
    int l_origin_Test1 = (*origin)[l_origin_Candidate1].getDemand();
    int l_origin_Test2 = (*origin)[l_origin_Candidate2].getDemand();
    int l_origin_Test3 = std::abs(l_origin - l_origin_Test1);
    int l_origin_Test4 = std::abs(l_origin - l_origin_Test2);
    int l_origin_Test5 = (l_origin_Test3);
    int l_origin_Test6 = (l_origin_Test4);
    
    l_switch = false;
    
    if(l_origin_Test5 > l_origin_Test6 && l_origin != l_origin_Candidate2)
        {
            //                    std::cout << "Before: " << l_origin << " " << l_origin_Test1 << " " << l_origin_Test2 << std::endl;
        iter_swap((*origin).begin() + l_origin_Candidate1, (*origin).begin() + l_origin_Candidate2);
            //                    std::cout << "After : " << (*origin)[l_origin_Swap].getDemand() << " " << (*origin)[l_origin_Candidate1].getDemand() << " " << (*origin)[l_origin_Candidate2].getDemand() << std::endl;
        l_switch = true;
        }
    
    return l_switch; // Return answering whether or not an exchange occurred
}


bool analyseStream(std::vector<neuron> *neuronList, std::vector<Point> *aPoint, int startPoint, int endPoint, int stepPoint, int neuralSequence)
{
    double feed;
    int addStatus;
    int neuronListSize = 0;
    bool neuronStimulated = false;
    
    for(int analyseLoop = startPoint; analyseLoop < endPoint; analyseLoop = analyseLoop + stepPoint)
        {
        neuronListSize = int((*neuronList).size());
        feed = (*aPoint)[analyseLoop].getPointPosition();
        neuronStimulated = false;
            //        std::cout << "List Size: " << neuronListSize << " Feed: " << feed << std::endl;
        for(int gateLoop = 0; gateLoop < neuronListSize; gateLoop++)
            {
            if(neuronListSize > 0)
                {
                if((*neuronList)[gateLoop].getCounter() == neuralSequence)
                    {
                    if((*neuronList)[gateLoop].openGate(feed) == true)
                        {
                        neuronStimulated = true;
                        for(int stimulateLoop = gateLoop + 1; stimulateLoop < gateLoop + 5; stimulateLoop++)
                            {
                            if(stimulateLoop < neuronListSize)
                                {
                                if((*neuronList)[stimulateLoop].getCounter() == neuralSequence)
                                    {
                                    (*neuronList)[stimulateLoop].openGate(feed);
                                    }
                                }
                            }
                        }
                    }
                }
            else
                {
                addStatus = add_Neuron(&(*neuronList));
                neuronListSize++;
                (*neuronList).back().setGateKeeper(feed);
                (*neuronList).back().setChannelMin(feed - 1);
                (*neuronList).back().setChannelMax(feed + 1);
                (*neuronList).back().setCounter(neuralSequence);
                neuronStimulated = true;
                    //                std::cout << "First Neuron: " << (*neuronList).back().getGateKeeper() << " Feed: " << feed << std::endl;
                }
            }
        if(neuronStimulated == false)
            {
            addStatus = add_Neuron(&(*neuronList));
            neuronListSize++;
            (*neuronList).back().setGateKeeper(feed);
            (*neuronList).back().setChannelMin(feed - 1);
            (*neuronList).back().setChannelMax(feed + 1);
            (*neuronList).back().setCounter(neuralSequence);
                //            std::cout << "Extra Neuron: " << (*neuronList).back().getGateKeeper() << " Feed: " << feed << std::endl;
            }
        }
    for(int readoutLoop = 0; readoutLoop < neuronListSize; readoutLoop++)
        {
        if((*neuronList)[readoutLoop].getCounter() == neuralSequence)
            {
                //            std::cout << "Sequence: " << neuralSequence << " " << readoutLoop << ": Value: " << (*neuronList)[readoutLoop].getGateKeeper() << " Energy: " << (*neuronList)[readoutLoop].getEnergy() << std::endl;
            }
        }
    return false;
}

class Screen_0 : public MultiScreen
{
public:
    /** Default constructor */
    Screen_0();
    /** Default destructor */
    virtual ~Screen_0() {};
    void creation();
    virtual int runScreen(sf::RenderWindow &app);
    
protected:
private:
    bool m_onScreen; //!< Member variable "m_onScreen"
};

Screen_0::Screen_0()
{
    m_onScreen = false;
}
void Screen_0::creation() {std::cout << "Screen 0 created." << std::endl; }

int Screen_0::runScreen(sf::RenderWindow &app)
{
    sf::Event Event;
    bool Running = true;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    sf::Text Menu4;
    int menu = 0;
    
        //    if (!Font.loadFromFile(resourcePath() + "DroidSans.ttf"))
    if (!Font.loadFromFile("/Users/pbisaacs/Developer/BrainHarmonics/DerivedData/Build/Products/Debug/DroidSans.ttf"))
        {
        std::cerr << "Error loading font." << std::endl;
        return (-1);
        }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Add item");
    Menu1.setPosition( 280.f, 160.f );
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Remove item");
    Menu2.setPosition( 280.f, 220.f );
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Up level");
    Menu3.setPosition( 280.f, 280.f );
    
    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Down level");
    Menu4.setPosition( 280.f, 320.f );
    
    while (Running)
        {
        while(app.pollEvent(Event))
            {
                // Window closed
            if (Event.type == sf::Event::Closed)
                {
                return (-1);
                }
            }
        if (menu == 0)
            {
            Menu1.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu1.setFillColor(sf::Color(255, 0, 0, 255));
            Menu2.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu2.setFillColor(sf::Color(255, 255, 255, 255));
            Menu3.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu3.setFillColor(sf::Color(255, 0, 0, 255));
            Menu4.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu4.setFillColor(sf::Color(255, 0, 0, 255));
            }
        else
            {
            Menu1.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu1.setFillColor(sf::Color(255, 255, 255, 255));
            Menu2.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu2.setFillColor(sf::Color(255, 0, 0, 255));
            Menu3.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu3.setFillColor(sf::Color(255, 255, 255, 255));
            Menu4.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu4.setFillColor(sf::Color(255, 255, 255, 255));
            }
        
        app.clear();
        app.display();
        }
    return (-1);
}

class Screen_1 : public MultiScreen
{
public:
    /** Default constructor */
    Screen_1();
    /** Default destructor */
    virtual ~Screen_1() {};
    void creation();
    virtual int runScreen(sf::RenderWindow &app);
    
protected:
private:
    bool m_onScreen; //!< Member variable "m_onScreen"
};

Screen_1::Screen_1()
{
    m_onScreen = false;
}
void Screen_1::creation() {std::cout << "Screen 0 created." << std::endl; }

int Screen_1::runScreen(sf::RenderWindow &app)
{
    sf::Event Event;
    bool Running = true;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    sf::Text Menu4;
    int menu = 0;
    
        //    if (!Font.loadFromFile(resourcePath() + "DroidSans.ttf"))
    if (!Font.loadFromFile("/Users/pbisaacs/Developer/BrainHarmonics/DerivedData/Build/Products/Debug/DroidSans.ttf"))
        {
        std::cerr << "Error loading font." << std::endl;
        return (-1);
        }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Add item");
    Menu1.setPosition( 280.f, 160.f );
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Remove item");
    Menu2.setPosition( 280.f, 220.f );
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Up level");
    Menu3.setPosition( 280.f, 280.f );
    
    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Down level");
    Menu4.setPosition( 280.f, 320.f );
    
    while (Running)
        {
        while(app.pollEvent(Event))
            {
                // Window closed
            if (Event.type == sf::Event::Closed)
                {
                return (-1);
                }
            }
        if (menu == 0)
            {
            Menu1.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu1.setFillColor(sf::Color(255, 0, 0, 255));
            Menu2.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu2.setFillColor(sf::Color(255, 255, 255, 255));
            Menu3.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu3.setFillColor(sf::Color(255, 0, 0, 255));
            Menu4.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu4.setFillColor(sf::Color(255, 0, 0, 255));
            }
        else
            {
            Menu1.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu1.setFillColor(sf::Color(255, 255, 255, 255));
            Menu2.setOutlineColor(sf::Color(255, 0, 0, 255));
            Menu2.setFillColor(sf::Color(255, 0, 0, 255));
            Menu3.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu3.setFillColor(sf::Color(255, 255, 255, 255));
            Menu4.setOutlineColor(sf::Color(255, 255, 255, 255));
            Menu4.setFillColor(sf::Color(255, 255, 255, 255));
            }
        
        app.clear();
        app.display();
        }
    return (-1);
}


    // Clear memory to cleanly exit application
void exitCB()
{
    std::cout << "Exiting Program. Press Any key to complete." << std::endl;
    /* A pause for Any key to be pressed, only needed for Windows to stop console window closing*/
    std::cin.get();
    
        // Clear vectors in reverse order to free-up memory before exiting
    
        // Remember to clear vectors / free memory before returning
}

int init(int argc, const char * argv[])
{
    /* Initialise random seed */
    srand (time(NULL));

    atexit(exitCB);				/* Set application exit callback */
    return 0;
}

int main(int argc, const char * argv[]) {
    
    int initialiseProgram = init(argc, argv);
    if (initialiseProgram)
        {
        std::cout << "Program initialisation failed!" << std::endl;
        return EXIT_FAILURE;
        }
    
    
        // Index arrays for instances of classes described above
    std::vector <Universe>           g_Universe;           /**< Top of the tree, begin with Universe class    */
    std::vector <Dimension>          g_Dimension;          /**< Add Dimensions for spatial identification     */
    std::vector <ElementaryParticle> g_ElementaryParticle; /**< Follow with the creation of quarks/leptons    */
    std::vector <CompositeParticle>  g_CompositeParticle;  /**< Basic interactions form protons/neutrons      */
    std::vector <ElementaryForce>    g_ElementaryForce;    /**< Define Force interaction between fundamentals */
    std::vector <CompositeForce>     g_CompositeForce;     /**< Define Force interaction between Composites   */
    std::vector <Law>                g_Law;                /**< Specify how Composites interact               */
    std::vector <Matter>             g_Matter;             /**< Composites form elements of periodic table    */
    std::vector <Monomer>            g_Monomer;            /**< Composites form molecules                     */
    std::vector <Polymer>            g_Polymer;            /**< Composites form complex molecules             */
    std::vector <Solid>              g_Solid;              /**< Materials are a combination of Matter         */
    std::vector <Polyhedron>         g_Polyhedron;         /**< Materials can be formed into multiDimensional shapes */
    std::vector <Polygon>            g_Polygon;            /**< Complex shapes are a combination of simpler forms */
    std::vector <Quad>               g_Quad;               /**< Reducing high Dimensions to lower             */
    std::vector <Line>               g_Line;               /**< Further reduction                             */
    std::vector <Point>              g_Point;              /**< Fundamental spatial description               */
        //    std::vector <Node>               g_Node;               /**< Node class for A* search                      */
    std::vector <Apptimer>           g_Apptimer;           /**< Interim function describing time before inclusion as Dimension */
    
        // Arrays of SFML objects to be drawn on-screen.
    std::vector<MultiScreen*>             g_screens;
    int g_screen = 0;
    std::vector <sf::RectangleShape>      g_drawRectangles;
    std::vector <sf::Vertex>              g_drawQuads;
    std::vector <sf::Text>                g_drawText;
    std::vector <sf::Vertex>              g_drawLines;
    std::vector <sf::Vertex>              g_drawPoints;
    
        // SFML objects
    sf::Font g_font;
    
    sf::Vector2u screenSize;
    
        // Higher level of abstraction. Initial naming.
    std::vector <neuron> g_neuron;                      /**< Neuron container for other neuron components  */
    std::vector <dendritecleft> g_dendritecleft;        /**< Dendritic synaptic cleft, input to the neuron */
    std::vector <Neuroreceptor> g_neuroreceptor;        /**< Neuroreceptor, component of dendritic cleft   */
    std::vector <synapse> g_synapse;                    /**< Synapse, area of stimulus transmission/reception */
    std::vector <membrane> g_membrane;                  /**< Membrane, outer component of the neuron       */
    std::vector <Kchannel> g_Kchannel;                  /**< Potassium channel, component of the membrane  */
    std::vector <Nachannel> g_Nachannel;                /**< Sodium channel, component of the membrane     */
    std::vector <dendrite>  g_dendrite;                 /**< Dendrite, pre-Soma component of a neuron      */
    std::vector <dendritebranch> g_dendritebranch;      /**< Dendrite branch, division/join of dendrites   */
    std::vector <soma> g_soma;                          /**< Soma, component of a neuron                   */
    std::vector <axonhillock> g_axonhillock;            /**< Axon Hillock, component of Soma               */
    std::vector <axon> g_axon;                          /**< Axon, connected to Axon Hillock               */
    std::vector <axonbranch> g_axonbranch;              /**< Axon branch, division/join of Axon            */
    std::vector <myelinsheath> g_myelinsheath;          /**< Myelin sheath, wraps around Axon              */
    std::vector <schwanncell> g_schwanncell;            /**< Schwann Cell, component of a Myelin sheath    */
    std::vector <axoncleft> g_axoncleft;                /**< Axon synaptic cleft, output area of neuron    */
    std::vector <synapticvesicle> g_synapticvesicle;    /**< Synaptic vesicle, container of neurotransmitters */
    std::vector <Cagate> g_Cagate;                      /**< Calcium gate, component of Axon cleft         */
    std::vector <Neurotransmitter> g_neurotransmitter;  /**< Neurotransmitter, transfer component between clefts */
    std::vector <Spike> g_Spike;                        /**< Spike */
    
        //CCP Abstraction
    std::vector <Warehouse> g_warehouse;                /**< Warehouse container                           */
    std::vector <Customer> g_customer;                  /**< Customer container                            */
    std::vector <int> nodeList;

    const int numUniverses = 5;     // Internal display, Physical material and spatial references
    const int numDimensions [numUniverses] = {2, 1, 4, 2, 2};    // U1 = Internal X & Y, U2 = Physical, U3 = Spatial X,Y,Z & Time, U4 = CPP, U5 = Spikes
    const int intDimensionsStart = 0;
    const int phyDimensionsStart = intDimensionsStart + numDimensions[0];
    const int spaDimensionsStart = phyDimensionsStart + numDimensions[1];
    const int ccpDimensionsStart = spaDimensionsStart + numDimensions[2];
    const int spkDimensionsStart = ccpDimensionsStart + numDimensions[2];
    const int initialElementaryParticles = 100;
    const int initialParticleAlignment = 200;
    const int infiniteLoopPrevention = 800;
    const int initialCustomers = 50;
    const int initialCustomerAlignment = 200;
    
    int addStatus;
    bool patternFound = false;
    
    double l_screenX = 925;            /**< Define graphics window size, X axis*/
    double l_screenY = 800;            /**< Define graphics window size, Y axis*/
    double l_scale = 300;               /**< Vertices are multiplied by this factor to enable fitting within the graphics window. Adjust to suit environment */
    std::string l_screenTitle = "Clustering";
    std::stringstream l_displayString;
    
    int counter_Charge = -1; // Used to loop between min 0 and max 6
    int counter_Spin = 0;
    int counter_Walk = 0;
    int counter_InfiniteLoopPrevention = 0;
    int l_spaPointBase = 0; // Base of data points (Moves because of use by internal graphics for points control too
    int howMany_Particles = 0;
    int howMany_Customers = 0;
    int howMany_Warehouses = 0;
    int current_Distance = 0;
    int max_Distance = 0;
    int l_pointStart = 0;
    int l_ccpPointStart = 0;
    bool l_switch = true;
    int l_origin = 0;
    int l_origin_Test1 = 0;
    int l_origin_Test3 = 0;
    int l_origin_Test5 = 0;
    double l_charge = 0;
    double l_lastCharge = 0;
    int pauseLoop = 0;
    
    double distanceToMove;
    double radialDistance;
    double s;
    double t;
    double pOrigin;
    double xd;
    double yd;
    double zd;
    double pointDistance;
    double pointDistance2;
    double effect;
    
    std::vector<std::string> l_inputData;
    
    char * l_dir = getcwd(NULL, 0);
    l_inputData.clear();
    int numCustomers;
    int initialWarehouses;
    int paramCounter;
    std::string entry;
    std::string buf;
    std::istringstream iss("");
    std::string::size_type sz;   // alias of size_t
    
    double l_customerX = 0;
    double l_customerY = 0;
    double l_warehouseX = 0;
    double l_warehouseY = 0;
    double l_desiredDistance = 0;
    double l_demandCounter = 0;
    double l_direction = 1;
    double l_diffX = 0;
    double l_diffX2 = 0;
    double l_diffY = 0;
    double l_diffY2 = 0;
    double l_slope = 0;
    double l_angleRAD = 0;
    double l_angleDEG = 0;
    double l_actualDistance = 0;
    double l_minimumDistance = 1000;
    std::vector <double> l_transferArray;
    int NumRows = 0;
    int NumInputs = 0;
    
    
        // CPLEX Environment
        //IloEnv cplexEnv;
    
        // Setup the Python environment for integrating K-means clustering solution
    
    setenv("PYTHONPATH", ".", 0);
    
    int pyArgc = 4;
        //    const char pyArgv[] = { ' ','p','y','c','o','m','p','u','t','e',' ','m','u','l','t','i','p','l','y',' ','3',' ','4','\0'};
    
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    PyObject *pArrayArgs;
    int *pTransferArray;
    
    int i;
    
    int result = EXIT_FAILURE;
    
    Py_Initialize();
    if(!Py_IsInitialized())
        {
        fprintf(stderr, "Python failed to initialise.\n");
        return EXIT_FAILURE;
        }
    import_array(); // Numpy array initialisation
    
    pName = PyUnicode_FromString("pycompute");    // File to be called. Must be in the same folder as the C++ executable and Not have a .py extension
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    
    if (pModule != NULL)
        {
        pFunc = PyObject_GetAttrString(pModule, "mlkmeans");
        if (!pFunc or !PyCallable_Check(pFunc))
            {
            PyErr_Occurred();
            PyErr_Print();
            fprintf(stderr, "Cannot find Python function.\n");
            return EXIT_FAILURE;
            }
        }
    else
        {
        PyErr_Print();
        fprintf(stderr, "Failed to load Python module.\n");
        return EXIT_FAILURE;
        }
    
        //    if (!g_font.loadFromFile(resourcePath() + "DroidSans.ttf"))
    if (!g_font.loadFromFile("/Users/pbisaacs/Developer/BrainHarmonics/DerivedData/Build/Products/Debug/DroidSans.ttf"))
        {
        std::cout << "Font failed to load!" << std::endl;
        return EXIT_FAILURE;
        }
    
        // Open SFML graphics windows and add title
    screenSize.x = l_screenX;
    screenSize.y = l_screenY;
    sf::RenderWindow window(sf::VideoMode(l_screenX, l_screenY), l_screenTitle, sf::Style::Resize);
    window.setSize(screenSize);
    screenSize = window.getSize();
    l_screenX = double(screenSize.x);
    l_screenY = double(screenSize.y);
    
        // Prepare screens
    
        // Group quads
        // Bind a Rectangle object
    g_drawRectangles.clear();
    for(int nloop = 0; nloop < 10; nloop++)
        {
        addStatus = add_SFMLRectangle(&g_drawRectangles, &g_Dimension, 0);
        if (addStatus)
            {
            std::cout << "Rectangle addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        }
    std::cout << g_drawRectangles.size() << " rectangle addresses created." << std::endl;
    
    for(int nloop = 0; nloop < 9; nloop++)
        {
        g_drawRectangles[nloop].setSize(sf::Vector2f(100,25));
        g_drawRectangles[nloop].setOutlineColor(sf::Color::Red);
        g_drawRectangles[nloop].setOutlineThickness(1);
        g_drawRectangles[nloop].setFillColor(sf::Color::Transparent);
        g_drawRectangles[nloop].setPosition(sf::Vector2f(800, 25 * (nloop + 2)));
        }
    
    g_drawRectangles[9].setSize(sf::Vector2f(100,225));
    g_drawRectangles[9].setOutlineColor(sf::Color::Green);
    g_drawRectangles[9].setOutlineThickness(2);
    g_drawRectangles[9].setFillColor(sf::Color::Transparent);
    g_drawRectangles[9].setPosition(sf::Vector2f(800, 225));
    
        // Bind a Text object
    for(int nloop = 0; nloop < 10; nloop++)
        {
        addStatus = add_SFMLText(&g_drawText, &g_Dimension, 0, &g_font);
        if (addStatus)
            {
            std::cout << "Text addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        }
    
    std::cout << g_drawText.size() << " text addresses created." << std::endl;
    
        // Build display text
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Initialising...";
    g_drawText[0].setFont(g_font);
    g_drawText[0].setCharacterSize(24);
    g_drawText[0].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Read Only";
    g_drawText[1].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Level";
    g_drawText[2].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "TOP";
    g_drawText[3].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "< ^ v >";
    g_drawText[4].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Quantity";
    g_drawText[5].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "0000";
    g_drawText[6].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Patterns";
    g_drawText[7].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "0000";
    g_drawText[8].setString(l_displayString.str());
    
    l_displayString.str("");
    l_displayString.clear();
    l_displayString << "Zoom";
    g_drawText[9].setString(l_displayString.str());
    
        // No GLUT on El Capitan - port headers
        //    glMatrixMode(GL_PROJECTION); // Setup OpenGL calls (for 3D use)
    
    Screen_0 screen0;
    g_screens.push_back(&screen0);
    Screen_1 screen1;
    g_screens.push_back(&screen1);
    
    window.clear();
        //    window.pushGLStates();
    window.draw(g_drawText[0]);
        //    window.popGLStates();
    window.display();
    
        // Set-up the simulation environment. Currently a skeletal environment.
    std::cout << "Brain Harmonics - Using neuron concepts to solve problems" << std::endl << std::endl;
    std::cout << "First we need to create the environment:" << std::endl << std::endl;
    std::cout << "The Big Bang..." << std::endl;
    
        // g_Universe is a vector of pointers to the Universe objects.
    g_Universe.clear();    // Ensure vector is empty
    for (int nloop = 0; nloop <= numUniverses - 1 ; nloop++) {
            // Pass the g_Universe address to the create function to keep all Universes within the same vector
        addStatus = create_Universe(&g_Universe);
        if (addStatus)
            {
            std::cout << "Universe creation failed!" << std::endl;
            return EXIT_FAILURE;
            }
        g_Universe[nloop].creation();   // Proof of creation by accessing method of instance (See console output)
    }
    
    std::cout << g_Universe.size() << " universe addresses created." << std::endl;
    
    g_Dimension.clear();    // Ensure vector is empty
    for (int ploop = 0; ploop <= numUniverses - 1; ploop++) {               // Cycle through Universes allocating n Dimensions
        for (int nloop = 0; nloop <= numDimensions[ploop] - 1; nloop++) {   // Visit create Dimensions n times
            addStatus = add_Dimension(&g_Dimension, &g_Universe, ploop);  // Connect the Dimension to the respective Universe
            if (addStatus)                                              // If return number is not 0 then an error occurred
                {
                std::cout << "Dimension addition failed!" << std::endl;    // Console output of error
                return EXIT_FAILURE;
                }
            g_Dimension[nloop].creation();   // Proof of creation by accessing method of instance (See console output)
        }
    }
    
    std::cout << g_Dimension.size() << " dimension addresses created." << std::endl;
    
        // Create new Elementary Particles - Quarks etc
    g_ElementaryParticle.clear();
    g_ElementaryForce.clear();
    for (int nloop = 0; nloop < initialElementaryParticles; nloop++)
        {
        addStatus = add_ElementaryParticle(&g_ElementaryParticle, &g_Dimension, phyDimensionsStart);
        if (addStatus)
            {
            std::cout << "Elementary Particle addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
            //        counter_Charge = int( counter_Charge + 1 ) * ( 1 - div( counter_Charge, 6 ).quot);
        counter_Charge++;
        if(counter_Charge > 6) counter_Charge = 0;
        counter_Spin = int(1 - counter_Spin);
            //        std::cout << counter_Charge << std::endl;
            // Try to ensure we get variations of particles. Not all one type by changing Charge and Spin.
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().resetElementaryParticle();
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().setCharge(counter_Charge);
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().setSpin(counter_Spin);
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().creation();
        
            // Bind a Force object to each Particle
        int addStatus = add_ElementaryForce(&g_ElementaryForce, &g_ElementaryParticle, nloop);
        if (addStatus)
            {
            std::cout << "Elementary Force addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        if (!g_ElementaryForce.empty()) g_ElementaryForce.back().creation();
        
        howMany_Particles = int(g_ElementaryParticle.size());
        
            //        std::cout << "Size:" << howMany_Particles << std::endl;
            // Rearrange new Particles in an order closer to how they're likely to interact.
        for (int qloop = 0; qloop <= initialParticleAlignment * howMany_Particles; qloop++)
            {
            
            counter_Walk = 0;
            current_Distance = 0;
            counter_InfiniteLoopPrevention = 0;
            
            do {
                counter_InfiniteLoopPrevention++;
                max_Distance = current_Distance;
                current_Distance = 0;
                while(counter_Walk <= (howMany_Particles - 3))
                    {
                    l_switch = compare_swapElementaryParticle(&g_ElementaryParticle, counter_Walk, counter_Walk + 1, counter_Walk + 2);
                    if (l_switch) counter_Walk--; else counter_Walk++;// If Switch occurred retest previous Origin
                    if (counter_Walk < 0) counter_Walk = 0;
                    
                    l_origin = g_ElementaryParticle[counter_Walk].getCharge();
                    l_origin_Test1 = g_ElementaryParticle[counter_Walk + 1].getCharge();
                    l_origin_Test3 = l_origin_Test1 - l_origin;
                    l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
                    current_Distance = current_Distance + l_origin_Test5;
                    }
            } while ( current_Distance < max_Distance && counter_InfiniteLoopPrevention < infiniteLoopPrevention);
            
            
            counter_Walk = (howMany_Particles - 1);
            current_Distance = 0;
            counter_InfiniteLoopPrevention = 0;
            
            do {
                counter_InfiniteLoopPrevention++;
                max_Distance = current_Distance;
                current_Distance = 0;
                while(counter_Walk >= 2)
                    {
                    l_switch = compare_swapElementaryParticle(&g_ElementaryParticle, counter_Walk, counter_Walk - 1, counter_Walk - 2);
                    if (l_switch) counter_Walk++; else counter_Walk--;
                    if (counter_Walk > (howMany_Particles - 1)) counter_Walk = (howMany_Particles - 1);
                    
                    l_origin = g_ElementaryParticle[counter_Walk].getCharge();
                    l_origin_Test1 = g_ElementaryParticle[counter_Walk - 1].getCharge();
                    l_origin_Test3 = l_origin_Test1 - l_origin;
                    l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
                    current_Distance = current_Distance + l_origin_Test5;
                    }
            } while ( current_Distance < max_Distance && counter_InfiniteLoopPrevention < infiniteLoopPrevention);
            }
        
        }
    
    std::cout << g_ElementaryParticle.size() << " elementary particle addresses created." << std::endl;
    std::cout << g_ElementaryForce.size() << " elementary force addresses created." << std::endl;
    
    for (int zloop = 0; zloop < int(g_ElementaryParticle.size()); zloop++ )
        {
            //        std::cout << g_ElementaryParticle[zloop].getCharge() << " ";
        }
        //    std::cout << std::endl;
    
        // Make Composite Particles - Protons, Neutrons
    g_CompositeParticle.clear();
    addStatus = add_CompositeParticle(&g_CompositeParticle, &g_ElementaryParticle, int(g_ElementaryParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Composite Particle addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_CompositeParticle.empty()) g_CompositeParticle.back().creation();
    
    std::cout << g_CompositeParticle.size() << " composite particle addresses created." << std::endl;
    
    g_CompositeForce.clear();
    addStatus = add_CompositeForce(&g_CompositeForce, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Composite Force addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_CompositeForce.empty()) g_CompositeForce.back().creation();
    
    std::cout << g_CompositeForce.size() << " composite force addresses created." << std::endl;
    
        // Make Elements - Hydrogen, Helium, Lithium etc
    g_Matter.clear();
    addStatus = add_Matter(&g_Matter, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Matter addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_Matter.empty()) g_Matter.back().creation();
    
    std::cout << g_Matter.size() << " matter addresses created." << std::endl;
    
        // Make Monomers - Carbohydrates/Sugars etc
    g_Monomer.clear();
    addStatus = add_Monomer(&g_Monomer, &g_Matter,  int(g_Matter.size() - 1));
    if (addStatus)
        {
        std::cout << "Monomer addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_Monomer.empty()) g_Monomer.back().creation();
    
    std::cout << g_Monomer.size() << " monomer addresses created." << std::endl;
    
    g_Polymer.clear();
    addStatus = add_Polymer(&g_Polymer, &g_Monomer,  int(g_Monomer.size() - 1));
    if (addStatus)
        {
        std::cout << "Polymer addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_Polymer.empty()) g_Polymer.back().creation();
    
    std::cout << g_Polymer.size() << " polymer addresses created." << std::endl;
    
    g_Spike.clear();
    addStatus = add_Spike(&g_Spike);
    if (addStatus)
        {
        std::cout << "Spike addition failed!" << std::endl;
        return EXIT_FAILURE;
        }
    if (!g_Spike.empty()) g_Spike.back().creation();
    
    std::cout << g_Spike.size() << " spike addresses created." << std::endl;
    
    g_Point.clear();
    
        // Add points to control application screen positions. Screen is two dimensions so two point values.
        // Points are grouped. First set is for internal use such as screen labels.
    l_spaPointBase = 0;
    for (int zloop = 0; zloop < int(g_drawRectangles.size()) + int(g_drawText.size()); zloop++)
        {
        for (int nloop = intDimensionsStart; nloop < phyDimensionsStart; nloop++)
            {
            addStatus = add_Point(&g_Point, &g_Dimension, nloop);
            if (addStatus)
                {
                std::cout << "Point addition failed!" << std::endl;
                return EXIT_FAILURE;
                }
            if (!g_Point.empty()) g_Point.back().creation();
            if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
            l_spaPointBase++;
            }
        }
    
        // Draw a few bounding box rectangles and text points for screen labelling
    for (int nloop = 0; nloop < 39; nloop = nloop + 2)
        {
        g_Point[nloop].setPointPosition(800);
        }
    for (int nloop = 1; nloop < 18; nloop = nloop + 2)
        {
        g_Point[nloop].setPointPosition((((nloop - 1)/2)+1) * 25);
        g_Point[nloop + 22].setPointPosition((((nloop - 1)/2)+1) * 25);
        }
    g_Point[18].setPointPosition(800);   g_Point[19].setPointPosition(25);  // Rectangle 10
    g_Point[20].setPointPosition(400);   g_Point[21].setPointPosition(0);   // Text 1
    
        // After screen layout the second set of points is for the quantum environment
    for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + numDimensions[2]; nloop++)
        {
        addStatus = add_Point(&g_Point, &g_Dimension, nloop);
        if (addStatus)
            {
            std::cout << "Point addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        if (!g_Point.empty()) g_Point.back().creation();
        if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
        }
    
    for (int eloop = 1; eloop < int(g_ElementaryParticle.size()); eloop++)
        {
            // Work out the charge difference between neighbouring particles to indicate how far apart they should be.
        l_lastCharge = l_charge;
        l_charge = double (3 - std::abs(int(g_ElementaryParticle[eloop].getCharge() - g_ElementaryParticle[eloop - 1].getCharge())));
            //        std::cout << "Charge: " << l_charge << std::endl;
            // This angle to later be dynamic to adjust for different particle types and considering placement of existing particles
        s = (s + (180 - ((l_charge * l_lastCharge) * 10)) * DEG2RAD) / 2; // in Radians
        t = (t + (180 - ((l_charge * l_lastCharge) * 10)) * DEG2RAD) / 2; // in Radians
        radialDistance = l_charge;
        for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + numDimensions[2]; nloop++) {
            addStatus = add_Point(&g_Point, &g_Dimension, nloop);
            if (addStatus)
                {
                std::cout << "Point addition failed!" << std::endl;
                return EXIT_FAILURE;
                }
            if (!g_Point.empty()) g_Point.back().creation();
            if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise point to location zero.
            
                // To calculate the position on the surface of a sphere is:
                // ( where radialDistance is radius and s & t are angles in Radians. The Origin is 0,0,0 )
                // x = radialDistance * cos(s) * sin(t)
                // y = radialDistance * sin(s) * sin(t)
                // z = radialDistance * cos(t)
            
                // radians = angleInDegrees * Math.PI / 180
            
            distanceToMove = 0;
            pOrigin = g_Point[(g_Point.size() - numDimensions[2]) - 1].getPointPosition();
            
                // Loop through each dimension to calculate position on the surface of a sphere
                // The sphere takes the previous particle as it's Origin and the radius is related to the charge.
                // The position on the surface will be affected by proximity to other particles.
            switch(nloop - spaDimensionsStart)
            {
                case 0:
                {
                distanceToMove = radialDistance * cos(s) * sin(t);
                break;
                }
                case 1:
                {
                distanceToMove = radialDistance * sin(s) * sin(t);
                break;
                }
                case 2:
                {
                distanceToMove = radialDistance * cos(t);
                break;
                }
                case 3:
                {
                distanceToMove = 0;
                break;
                }
            }
            
            distanceToMove = distanceToMove + pOrigin;
                //            std::cout << "d:" << distanceToMove << " r:" << radialDistance << " s:" << s << " t:" << t << std::endl;
            g_Point.back().setPointPosition(distanceToMove);
            g_Point.back().setPointPositionMaxOverflow(2);
            g_Point.back().setPointPositionMinOverflow(2);
            g_Point.back().setPointMove(1);
            g_Point.back().setPointMoveMaxOverflow(2);
            g_Point.back().setPointMoveMinOverflow(2);
            g_Point.back().setPointDifferential(0);
                //            std::cout << g_Point.back().getPointPosition() << ", ";
        }
            //        std::cout << std::endl;
        }
    
    std::cout << g_Point.size() << " point addresses created." << std::endl;
    
    /*
     // Add lines to points
     for (int eloop = 1; eloop < int(g_ElementaryParticle.size()); eloop++)
     {
     for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + numDimensions[2]; nloop++)
     {
     addStatus = add_Line(&g_Line, &g_Polygon, nloop);
     if (addStatus)
     {
     std::cout << "Line addition failed!" << std::endl;
     return EXIT_FAILURE;
     }
     if (!g_Line.empty()) g_Line.back().creation();
     if (!g_Line.empty()) g_Line.back().resetLine();
     }
     }
     */
    
    std::cout << "Capacitated Clustering Problem" << std::endl;
    
    std::ifstream dataFile("/Users/pbisaacs/Developer/BrainHarmonics/ccpx1.in");
    if(!dataFile)
        {
        std::cout << "Error opening data file!" << std::endl;
        printf("File should be located in: %s", l_dir);
        return false;
        }
    
        // Read number of customers and initial number of warehouses
    entry = "";
    std::getline(dataFile, entry);
    iss.clear();
    iss.str(entry);
    buf = "";
        // Walks through 1 row of 2 numbers
    paramCounter = 0;
    while (iss >> buf)
        {
        if(buf != "" && buf != " " && paramCounter < 10)
            {
            paramCounter++;
                //            std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
            l_inputData.push_back(buf);
            }
        }
    
    numCustomers = std::stoi(l_inputData[0],&sz);
    initialWarehouses = std::stoi(l_inputData[1],&sz);
    
        //    std::cout << numCustomers << " " << initialWarehouses << std::endl;
    
    g_warehouse.clear();
        // Add initial 50 warehouses
    for(int nloop = 0; nloop < 50; nloop++)
        {
        addStatus = add_Warehouse(&g_warehouse, &g_Dimension,  int(g_Dimension.size() - 1));
        if (addStatus)
            {
            std::cout << "Warehouse addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        if (!g_warehouse.empty()) g_warehouse[0].creation();
        }
    
        // Read in customer demand data from file
    l_inputData.clear();
    
    for(int nloop = 0; nloop < 5; nloop++)
        {
        entry = "";
        std::getline(dataFile, entry);
        if(entry != "" and entry.length() > 10)
            {
            iss.clear();
            iss.str(entry);
            buf="";
                // Walks through 5 rows of 10 numbers
            paramCounter = 0;
            while (iss >> buf)
                {
                if(buf != "" && buf != " " && paramCounter < 10)
                    {
                    paramCounter++;
                        //                    std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
                    l_inputData.push_back(buf);
                    }
                }
            }
        else
            {
            nloop--;
            }
        }
    
    g_customer.clear();
    for(int nloop = 0; nloop < 50; nloop++)
        {
            // Add customer demands
        addStatus = add_Customer(&g_customer, &g_warehouse,  int(g_warehouse.size() - 1));
        if (addStatus)
            {
            std::cout << "Customer addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        if (!g_customer.empty() && !l_inputData[nloop].empty())
            {
            g_customer.back().setDemand(std::stoi(l_inputData[nloop],&sz));
            std::cout << "Customer: " << nloop << " Demand: " << g_customer.back().getDemand() << std::endl;
            }
        }
        //    std::cout << std::endl;
    
        // Load capacity data to each warehouse
    l_inputData.clear();
    
    for(int nloop = 0; nloop < 5; nloop++)
        {
        entry = "";
        std::getline(dataFile, entry);
        if(entry != "" and entry.length() > 10)
            {
            iss.clear();
            iss.str(entry);
            buf="";
                // Walks through 5 rows of 10 numbers
            paramCounter = 0;
            while (iss >> buf)
                {
                if(buf != "" && buf != " " && paramCounter < 10)
                    {
                    paramCounter++;
                        //                        std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
                    l_inputData.push_back(buf);
                    }
                }
            }
        else
            {
            nloop--;
            }
        }
    
    for(int nloop = 0; nloop < 50; nloop++)
        {
            //        std::cout << l_inputData[nloop] << " ";
        if (!g_warehouse.empty() && !l_inputData[nloop].empty()) g_warehouse[nloop].setCapacity(std::stoi(l_inputData[nloop],&sz));
        }
    
        // Load distance data from 50 customers to each warehouse
    l_inputData.clear();
    
    for(int xloop = 0; xloop < 50; xloop++)
        {
        for(int nloop = 0; nloop < 5; nloop++)
            {
            entry = "";
            std::getline(dataFile, entry);
            if(entry != "" and entry.length() > 10)
                {
                iss.clear();
                iss.str(entry);
                buf="";
                    // Walks through 5 rows of 10 numbers
                paramCounter = 0;
                while (iss >> buf)
                    {
                    if(buf != "" && buf != " " && paramCounter < 10)
                        {
                            //                        std::cout << buf << " ";
                        paramCounter++;
                            //                        std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
                        l_inputData.push_back(buf);
                        }
                    }
                    //                std::cout << std::endl;
                }
            else
                {
                nloop--;
                }
            }
        }
    
        // Close data file - all data read in.
    iss.clear();
    dataFile.close();
    
        // Transfer distance data to customer instances
    for(int xloop = 0; xloop < 50; xloop++)
        {
        for(int nloop = 0; nloop < 50; nloop++)
            {
                //            std::cout << l_inputData[(xloop * 50) + nloop] << " ";
            if (!g_customer.empty() && !l_inputData[(xloop * 50) + nloop].empty())
                {
                g_customer[xloop].addDistance(&g_warehouse[nloop], std::stod(l_inputData[(xloop * 50) + nloop],&sz));
                }
            }
        }
        //    std::cout << std::endl;
    
    
    /*
     for(int nloop = 0; nloop < 50; nloop++)
     {
     g_customer[nloop].getWarehouseList();
     }
     */
    
    
    howMany_Customers = int(g_customer.size());
    
    std::cout << howMany_Customers << " customers to consider." << std::endl;
    
        // Rearrange new Customers in an order closer to how they're likely to group with warehouses.
    /*
     for (int qloop = 0; qloop <= initialCustomerAlignment * howMany_Customers; qloop++)
     {
     
     counter_Walk = 0;
     current_Distance = 0;
     counter_InfiniteLoopPrevention = 0;
     
     do {
     counter_InfiniteLoopPrevention++;
     max_Distance = current_Distance;
     current_Distance = 0;
     while(counter_Walk <= (howMany_Customers - 3))
     {
     l_switch = compare_swapCustomer(&g_customer, counter_Walk, counter_Walk + 1, counter_Walk + 2);
     if (l_switch) counter_Walk--; else counter_Walk++;// If Switch occurred retest previous Origin
     if (counter_Walk < 0) counter_Walk = 0;
     
     l_origin = g_customer[counter_Walk].getDemand();
     l_origin_Test1 = g_customer[counter_Walk + 1].getDemand();
     l_origin_Test3 = l_origin_Test1 - l_origin;
     l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
     current_Distance = current_Distance + l_origin_Test5;
     }
     } while ( current_Distance < max_Distance && counter_InfiniteLoopPrevention < infiniteLoopPrevention);
     
     
     counter_Walk = (howMany_Customers - 1);
     current_Distance = 0;
     counter_InfiniteLoopPrevention = 0;
     
     do {
     counter_InfiniteLoopPrevention++;
     max_Distance = current_Distance;
     current_Distance = 0;
     while(counter_Walk >= 2)
     {
     l_switch = compare_swapCustomer(&g_customer, counter_Walk, counter_Walk - 1, counter_Walk - 2);
     if (l_switch) counter_Walk++; else counter_Walk--;
     if (counter_Walk > (howMany_Customers - 1)) counter_Walk = (howMany_Customers - 1);
     
     l_origin = g_customer[counter_Walk].getDemand();
     l_origin_Test1 = g_customer[counter_Walk - 1].getDemand();
     l_origin_Test3 = l_origin_Test1 - l_origin;
     l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
     current_Distance = current_Distance + l_origin_Test5;
     }
     } while ( current_Distance < max_Distance && counter_InfiniteLoopPrevention < infiniteLoopPrevention);
     }
     */
    int maxCapacity = 120;
    int currentCapacity = 0;
    
    for(int nloop = 0; nloop < 50 ; nloop++)
        {
        if(currentCapacity + g_customer[nloop].getDemand() <= maxCapacity)
            {
            currentCapacity += g_customer[nloop].getDemand();
            }
        }
    
    
    
    l_pointStart = int(l_spaPointBase);
    l_ccpPointStart = int(g_Point.size());
    
        // 50 customers and 50 possible warehouses
    for(int xloop = 0; xloop < 100; xloop++)
        {
        for (int nloop = ccpDimensionsStart; nloop < ccpDimensionsStart + numDimensions[3]; nloop++)
            {
                //        std::cout << "Dimension Loop: " << nloop << " ";
            addStatus = add_Point(&g_Point, &g_Dimension, nloop);
            if (addStatus)
                {
                std::cout << "Point addition failed!" << std::endl;
                return EXIT_FAILURE;
                }
            if (!g_Point.empty()) g_Point.back().creation();
            if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
                                                                // Customer points first
            if(xloop < 50)
                {
                if (!g_Point.empty()) g_Point.back().setPointPosition(rand() % 500 + 100);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMin(100);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMinOverflow(2);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMax(600);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMaxOverflow(2);  // Initialise to ne coordinate.
                }
            else
                {
                    // Warehouse points second
                if (!g_Point.empty()) g_Point.back().setPointPosition(rand() % 500 + 100);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMin(100);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMinOverflow(2);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMax(600);  // Initialise to ne coordinate.
                if (!g_Point.empty()) g_Point.back().setPointPositionMaxOverflow(2);  // Initialise to ne coordinate.
                }
            }
        }
    
    
    int l_ccpPointEnd = int(g_Point.size());
    int l_spkPointStart = int(g_Point.size());
    
    for(int zloop = 0; zloop < 300; zloop++)
        {
        for (int nloop = spkDimensionsStart; nloop < spkDimensionsStart + numDimensions[4]; nloop++)
            {

        addStatus = add_Point(&g_Point, &g_Dimension, nloop);
        if (addStatus)
            {
            std::cout << "Point addition failed!" << std::endl;
            return EXIT_FAILURE;
            }
        if (!g_Point.empty()) g_Point.back().creation();
        if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
            if (!g_Point.empty()) g_Point.back().setPointPosition(zloop);
        }
        g_Point.back().setPointPosition(g_Spike[0].pollSpike());
            //        std::cout << g_Point.back().getPointPosition() << ", ";
        }
        //    std::cout << std::endl;
    
    int l_spkPointEnd = int(g_Point.size());
    int l_pointEnd = int(g_Point.size());
    
        // The program will loop whilst the graphics window is open
    while(g_screen >= 0)
        {
            // Prepared for multiscreen
            //        g_screen = g_screens[g_screen]->runScreen(window);
            // SFML event handling to define what happens if the graphics window is closed
        sf::Event event;
        while (window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                {
                window.close();
                g_screen = -1;
                break;
                }
            if (event.type == sf::Event::Resized)
                {
                screenSize = window.getSize();
                l_screenX = double(screenSize.x);
                l_screenY = double(screenSize.y);
                if(l_screenX < 400)
                    {
                    l_screenX = 400;
                    screenSize.x = l_screenX;
                    }
                if(l_screenY < 400)
                    {
                    l_screenY = 400;
                    screenSize.y = l_screenY;
                    }
                window.setSize(screenSize);
                screenSize = window.getSize();
                l_screenX = double(screenSize.x);
                l_screenY = double(screenSize.y);
                }
            if (event.type == sf::Event::KeyPressed)
                {
                switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                        window.close();
                        g_screen = -1;
                        break;
                        case sf::Keyboard::Up:
                            //                        posy -= movement_step;
                        break;
                        case sf::Keyboard::Down:
                            //                        posy += movement_step;
                        break;
                        case sf::Keyboard::Left:
                            //                        posx -= movement_step;
                        break;
                        case sf::Keyboard::Right:
                            //                        posx += movement_step;
                        break;
                        default:
                        break;
                    }
                }
            }
        
            // Toggle between discover map and explore discovered map when mouse clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            if(!g_buttonPressed)
                {
                g_toggle = 1 - g_toggle;
                g_buttonPressed = true;
                }
            }
        
            // Prevents flapping of toggle when mouse button held down
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
            g_buttonPressed = false;
            }

        pauseLoop++;
            if(pauseLoop > 1000)
                {
                pauseLoop = 0;
                sleep(3);
                    //                std::cout << "Actual: " << time(0) << " Virtual: " << g_Universe[0].theTimeNow() << std::endl;
                }
        /*
        for(int ploop = 0; ploop < 10000; ploop++)
            {
            
            }
         */
        /*
         // Early calculation for colliding elementary particles and the effect on direction and acceleration
         for(int n = 0; n < l_pointEnd; n = n + 4)
         {
         for(int p = 0; p < l_pointEnd; p = p + 4)
         {
         if(n != p)
         {
         xd = g_Point[p].getPointPosition() - g_Point[n].getPointPosition();
         yd = g_Point[p + 1].getPointPosition() - g_Point[n + 1].getPointPosition();
         zd = g_Point[p + 2].getPointPosition() - g_Point[n + 2].getPointPosition();
         pointDistance2 = (xd * xd + yd * yd + zd * zd);
         effect = 1 + (1 / pointDistance2);
         g_Point[n].setPointDifferential(g_Point[n].getPointDifferential() * effect);
         g_Point[p].setPointDifferential(g_Point[p].getPointDifferential() * effect);
         g_Point[n + 1].setPointDifferential(g_Point[n + 1].getPointDifferential() * effect);
         g_Point[p + 1].setPointDifferential(g_Point[p + 1].getPointDifferential() * effect);
         g_Point[n + 2].setPointDifferential(g_Point[n + 2].getPointDifferential() * effect);
         g_Point[p + 2].setPointDifferential(g_Point[p + 2].getPointDifferential() * effect);
         }
         }
         }
         */
        
        
        
        for(int x = l_ccpPointStart; x < l_ccpPointStart + 100; x = x + 2)
            {
            for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
                {
                l_desiredDistance = g_customer[int((x - l_ccpPointStart)/2)].getDistance(int((n - (l_ccpPointStart + 100))/2));
                nodeList.clear();
                nodeList.push_back(x);
                nodeList.push_back(x + 1);
                nodeList.push_back(n);
                nodeList.push_back(n + 1);
                
                    //                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desiredDistance << std::endl;
                
                addStatus = distanceBetweenNodes(&g_Point, &nodeList, 2, l_desiredDistance);
                
                    //                std::cout << "Retrieved : " << g_Point[nodeList[0]].getPointDifferential() << ", " << g_Point[nodeList[1]].getPointDifferential() << ", " << g_Point[nodeList[2]].getPointDifferential() << ", " << g_Point[nodeList[3]].getPointDifferential() << std::endl;

                }
            }

        for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
            {
            l_demandCounter = 0;
            for(int x = l_ccpPointStart; x < l_ccpPointStart + 100; x = x + 2)
                {
                l_desiredDistance = g_customer[int((x - l_ccpPointStart)/2)].getDistance(int((n - (l_ccpPointStart + 100))/2));
                nodeList.clear();
                nodeList.push_back(n);
                nodeList.push_back(n + 1);
                nodeList.push_back(x);
                nodeList.push_back(x + 1);
                
                    //                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desiredDistance << std::endl;
                
                addStatus = distanceBetweenNodes(&g_Point, &nodeList, 2, l_desiredDistance);
                
                if(g_customer[int((x - l_ccpPointStart)/2)].getAllocatedWarehouse() == int( n - (l_ccpPointStart + 100 ))/2)
                    {
                    l_demandCounter = l_demandCounter + g_customer[int((x - l_ccpPointStart)/2)].getDemand();
                    }
                    //                std::cout << ((n - (l_ccpPointStart + 100)) / 2) << " - " << g_customer[int((x - l_ccpPointStart)/2)].getAllocatedWarehouse() << " - " << int( n - (l_ccpPointStart + 100 ))/2 << " - " << l_demandCounter << std::endl;
                }
            }

        for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
            {
            for(int x = l_ccpPointStart + 100; x < l_ccpPointStart + 200; x = x + 2)
                {
                if (n != x)
                    {
                l_desiredDistance = 100;
                nodeList.clear();
                nodeList.push_back(n);
                nodeList.push_back(n + 1);
                nodeList.push_back(x);
                nodeList.push_back(x + 1);
                
                    //                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desiredDistance << std::endl;
                
                addStatus = distanceBetweenNodes(&g_Point, &nodeList, 2, l_desiredDistance);
                    }
                }
            }

        pArgs = NULL;
        pArrayArgs = NULL;
        pTransferArray = NULL;
        pValue = NULL;
        pArgs = PyTuple_New(2);
            //        pValue = PyInt_FromLong(3);
        npy_intp dims[2] = {2,15};
        pArrayArgs = PyArray_SimpleNew(2, dims, NPY_INT);
            // The pointer to the array data is accessed using PyArray_DATA()
        pTransferArray = (int *) PyArray_DATA(pArrayArgs);
            // Copy the data from the "array of arrays" to the contiguous numpy array.
        l_transferArray.clear();
        for (int tloop = l_ccpPointStart; tloop < l_ccpPointStart + 30; tloop++)
            {
            l_transferArray.push_back((int)round(g_Point[tloop].getPointPosition()));
                //            std::cout << l_transferArray.back() << ", ";
            }
            //        std::cout << std::endl;
        std::memcpy(pTransferArray, &l_transferArray, sizeof(int) * 30);
        PyTuple_SetItem(pArgs,0,pArrayArgs);
        pValue = PyInt_FromLong(2);
        PyTuple_SetItem(pArgs,1,pValue);
        
            //        pValue = PyObject_CallObject(pFunc, pArgs);
        pValue = PyObject_CallObject(pFunc, pArgs);
            //        Py_DECREF(pArgs);
            //        Py_DECREF(pArrayArgs);
        if (pValue != NULL) {
                //            printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                //            Py_DECREF(pValue);
                //            Py_DECREF(pTransferArray);
                //            pValue = NULL;
        }
        else {
            Py_DECREF(pTransferArray);
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            PyErr_Print();
            fprintf(stderr,"Call failed\n");
            return EXIT_FAILURE;
        }
        
        for(int n = l_pointStart; n < l_pointEnd; n++)
            {
                //            std::cout << n << " ";
            g_Point[n].pointPoll(1);
            g_Point[n].overflowPoll();
            }
            //        std::cout << std::endl;
        
        patternFound = analyseStream(&g_neuron, &g_Point, l_pointStart, (l_ccpPointStart + 0) - numDimensions[2], numDimensions[2],1);
        patternFound = analyseStream(&g_neuron, &g_Point, l_pointStart + 1, (l_ccpPointStart + 1) - numDimensions[2], numDimensions[2],2);
        patternFound = analyseStream(&g_neuron, &g_Point, l_pointStart + 2, (l_ccpPointStart + 2) - numDimensions[2], numDimensions[2],3);
        
        patternFound = analyseStream(&g_neuron, &g_Point, l_ccpPointStart, (l_pointEnd + 0) - numDimensions[3], numDimensions[3],1);
        patternFound = analyseStream(&g_neuron, &g_Point, l_ccpPointStart + 1, (l_pointEnd + 1) - numDimensions[3], numDimensions[3],2);
        
            // Now to put all the calculations into something visual. Drawing to the screen. Scaled and orientated.
        g_drawPoints.clear();
        for(int n = l_pointStart; n < l_ccpPointStart; n = n + numDimensions[2])
            {
            g_drawPoints.push_back(sf::Vertex(sf::Vector2f(((g_Point[n].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenX / 2), l_screenY - (((g_Point[n + 1].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenY / 2))), sf::Color(255,255,0,255)));
                //            std::cout << n << " = " << ((g_Point[n].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenX / 2) << " : " << l_screenY - (((g_Point[n + 1].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenY / 2)) << std::endl;
            }
        for(int n = l_ccpPointStart; n < l_ccpPointEnd; n = n + numDimensions[3])
            {
            g_drawPoints.push_back(sf::Vertex(sf::Vector2f(((g_Point[n].getPointPosition()))+100, l_screenY - (((g_Point[n + 1].getPointPosition()))+100)), sf::Color(128,255,128,255)));
                //            std::cout << n << " = " << ((g_Point[n].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenX / 2) << " : " << l_screenY - (((g_Point[n + 1].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenY / 2)) << std::endl;
            }
        for(int n = l_spkPointStart; n < l_spkPointEnd; n = n + numDimensions[4])
            {
            g_drawPoints.push_back(sf::Vertex(sf::Vector2f(((g_Point[n].getPointPosition()))+100, l_screenY - (((g_Point[n + 1].getPointPosition()))+100)), sf::Color(255,0,0,255)));
                //            std::cout << g_Point[n].getPointPosition() << ":" << g_Point[n+1].getPointPosition() << ", ";
            }
            //        std::cout << std::endl;
        g_drawLines.clear();
        /*
         for(int n = 0; n < l_LineEnd; n++)
         {
         g_drawLines.push_back(sf::Vertex(sf::Vector2f((g_Line[n].GetLineX1() * l_scale) + (l_screenX / 2), l_screenY - ((g_Line[n].GetLineY1() * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) * g_Point[n].GetXYTTL()),0,0,255)));
         g_drawLines.push_back(sf::Vertex(sf::Vector2f((g_Line[n].GetLineX2() * l_scale) + (l_screenX / 2), l_screenY - ((g_Line[n].GetLineY2() * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) * g_Point[n].GetXYTTL()),0,0,255)));
         }
         */
        window.clear();
        
            //        window.pushGLStates();
        window.draw(&g_drawQuads[0], g_drawQuads.size(), sf::Quads);
            //        window.popGLStates();
        
            //        window.pushGLStates();
        window.draw(&g_drawPoints[0], g_drawPoints.size(), sf::Points);
            //        window.popGLStates();
        
            //        window.pushGLStates();
        window.draw(&g_drawLines[0], g_drawLines.size(), sf::Lines);
            //        window.popGLStates();
        
            // Group quads
            //        g_drawRectangles[1].setPosition(sf::Vector2f(((l_screenX / 2 ) - (20 / 2)) + (25 * g_toggle), 30));
        
        for(int loopRectangles = 0; loopRectangles < int(g_drawRectangles.size()); loopRectangles++)
            {
            g_drawRectangles[loopRectangles].setPosition(g_Point[loopRectangles * 2].getPointPosition(), g_Point[(loopRectangles * 2) + 1].getPointPosition());
                //            window.pushGLStates();
            window.draw(g_drawRectangles[loopRectangles]);
                //            window.popGLStates();
            }
        
        for(int loopText = 1; loopText < int(g_drawText.size()); loopText++)
            {
            g_drawText[loopText].setPosition(g_Point[(loopText * 2) + (int(g_drawRectangles.size())*2)].getPointPosition(), g_Point[(loopText * 2) + 1 + (int(g_drawRectangles.size())*2)].getPointPosition());
                //            window.pushGLStates();
            window.draw(g_drawText[loopText]);
                //            window.popGLStates();
                //            std::cout << "X:" << g_Point[(loopText * 2) + (int(g_drawRectangles.size())*2)].getPointPosition() << " Y:" << g_Point[(loopText * 2) + 1 + (int(g_drawRectangles.size())*2)].getPointPosition() << std::endl;
            }
        
        window.display();
        }
        // Empty vectors before exiting (in reverse of creation)
        //    for(int dloop = int(g_Point.size()); dloop > 0; --dloop) delete (&g_Point[dloop - 1]);
    std::cout << "Clearing memory..." << std::endl;
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    Py_Finalize();
    g_Point.clear();
    g_Matter.clear();
    g_CompositeForce.clear();
    g_CompositeParticle.clear();
    g_ElementaryForce.clear();
    g_ElementaryParticle.clear();
    g_Dimension.clear();
    g_Universe.clear();
    
    return EXIT_SUCCESS;
}
