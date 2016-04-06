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

    // SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>    /**< Graphics library http://sfml-dev.org          */
#include "ResourcePath.hpp"

    // Homegrown add-ins
#include <universe.h>           /**< Top of the tree, begin with Universe class    */
#include <dimension.h>          /**< Add Dimensions for spatial identification     */
#include <elementaryparticle.h> /**< Follow with the creation of quarks/leptons    */
#include <compositeparticle.h>  /**< Basic interactions form protons/neutrons      */
#include <elementaryforce.h>    /**< Define Force interaction between fundamentals */
#include <compositeforce.h>     /**< Define Force interaction between Composites   */
#include <law.h>                /**< Specify how Composites interact               */
#include <matter.h>             /**< Composites form elements of periodic table    */
#include <solid.h>              /**< Materials are a combination of Matter         */
#include <polyhedron.h>         /**< Materials can be formed into multiDimensional shapes */
#include <polygon.h>            /**< Complex shapes are a combination of simpler forms */
#include <quad.h>               /**< Reducing high Dimensions to lower             */
#include <line.h>               /**< Further reduction                             */
#include <point.h>              /**< Fundamental spatial description               */
#include <node.h>               /**< Node class for A* search                      */
#include <apptimer.h>           /**< Interim function describing time before inclusion as Dimension */

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
    Universe myUniverse;                            /**< Create instance of Universe from Universe class */
    myUniverse.setEnergy(UniverseEnergy);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));
    
    /**< Set an energy level and attempt to maintain physics laws by keeping the total in the Universe the same. Uses the maximum value for double. Levels of abstraction used to cater for environment limitations */
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding Dimensions enables physical and spatial calculations
int add_Dimension(std::vector<Dimension> *toAddto, std::vector<Universe> *aPartof, int arrayEntry)
{
    Dimension myDimension((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myDimension, &myDimension + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Each add_ function creates an instance of the respective class and links back to the base class
    // For definition of quarks and leptons when simulating real-world environment
int add_ElementaryParticle(std::vector<ElementaryParticle> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
    ElementaryParticle myElementaryParticle((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myElementaryParticle, &myElementaryParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // For real-world definition of protons & neutrons. Other combinations in artificial environments
int add_CompositeParticle(std::vector<CompositeParticle> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    CompositeParticle myCompositeParticle((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myCompositeParticle, &myCompositeParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Methods in this class to define interaction. Which may be different between artificial, simulation and real environments
int add_ElementaryForce(std::vector<ElementaryForce> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    ElementaryForce myForce((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

int add_CompositeForce(std::vector<CompositeForce> *toAddto, std::vector<CompositeParticle> *aPartof, int arrayEntry)
{
    CompositeForce myForce((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Add methods to describe Force interactions such as gravity
int add_law(std::vector<CompositeForce> *toAddto, int arrayEntry, std::vector<CompositeParticle> *toAddto2, int arrayEntry2)
{
        //    law myLaw(aPartof[arrayEntry], toAddto2[arrayEntry2]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of periodic table of elements
int add_Matter(std::vector<Matter> *toAddto, std::vector<CompositeParticle> *aPartof, int arrayEntry)
{
    Matter myMatter((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myMatter, &myMatter + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Description of material
int add_Solid(std::vector<Solid> *toAddto, std::vector<Matter> *aPartof, int arrayEntry)
{
    Solid mySolid((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&mySolid, &mySolid + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Fundamental spatial element
int add_Point(std::vector<Point> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
        // Begin with shape singularity
    Point myPoint((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myPoint, &myPoint + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Complex shapes
int add_Polyhedron(std::vector<Polyhedron> *toAddto, std::vector<Solid> *aPartof, int arrayEntry)
{
    Polyhedron myPolyhedron((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myPolyhedron, &myPolyhedron + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Components of complex shapes
int add_Polygon(std::vector<Polygon> *toAddto, std::vector<Polyhedron> *aPartof, int arrayEntry)
{
    Polygon myPolygon((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myPolygon, &myPolygon + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Base 2D shapes
int add_Quad(std::vector<Quad> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Quad myQuad((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myQuad, &myQuad + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Component of shapes, straight, curved or complex
int add_Line(std::vector<Line> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Line myLine((*aPartof)[arrayEntry]);
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myLine, &myLine + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding application timer temporarily until integrated into Dimension class
int add_Apptimer(std::vector<Apptimer> *toAddto)
{
    Apptimer myApptimer;
        // Use copy not push_back otherwise data is destroyed on exiting function
    std::copy(&myApptimer, &myApptimer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

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
    
        //    std::cout << l_origin << " " << l_origin_Test1 << " " << l_origin_Test2 << " " << l_origin_Test3 << " " << l_origin_Test4 << " " << l_origin_Test5 << " " << l_origin_Test6 << std::endl;
    
    l_switch = false;
    
    if(l_origin_Test5 > l_origin_Test6 && l_origin != l_origin_Candidate2)
        {
        iter_swap((*origin).begin() + l_origin_Candidate1, (*origin).begin() + l_origin_Candidate2);
        l_switch = true;
        }
    
    return l_switch;
}

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
    
    return l_switch;
}

    // Clear memory to cleanly exit application
void exitCB()
{
    std::cout << "Exiting Program." << std::endl;
    /* A pause for Any key to be pressed, only needed for Windows to stop console window closing*/
    std::cin.get();
    
        // Clear vectors in reverse order to free-up memory before exiting
    
        // Remember to clear vectors / free memory before returning
}

int init(int argc, const char * argv[])
{
    atexit(exitCB);				/* Set application exit callback */
    return 0;
}

int main(int argc, const char * argv[]) {
    
    int initialiseProgram = init(argc, argv);
    if (initialiseProgram)
        {
        std::cout << "Program initialisation failed!" << std::endl;
        return 1;
        }
    
    
        // Index arrays for instances of classes described above
    std::vector <Universe> g_Universe;
    std::vector <Dimension> g_Dimension;
    std::vector <ElementaryParticle> g_ElementaryParticle;
    std::vector <CompositeParticle> g_CompositeParticle;
    std::vector <ElementaryForce> g_ElementaryForce;
    std::vector <CompositeForce> g_CompositeForce;
    std::vector <Law> g_Law;
    std::vector <Matter> g_Matter;
    std::vector <Solid> g_Solid;
    std::vector <Polyhedron> g_Polyhedron;
    std::vector <Polygon> g_Polygon;
    std::vector <Quad> g_Quad;
    std::vector <Line> g_Line;
    std::vector <Point> g_Point;
    std::vector <Apptimer> g_Apptimer;
    
        // Arrays of SFML objects to be drawn on-screen.
    std::vector <sf::Vertex> g_drawQuads;
    std::vector <sf::Text> g_drawQuadText;
    std::vector <sf::Vertex> g_drawLines;
    std::vector <sf::Vertex> g_drawPoints;
    
        // SFML objects
    sf::Font g_font;
    sf::Text g_text;
    
    std::vector <neuron> g_neuron;                      /**< Neuron container for other neuron components  */
    std::vector <dendritecleft> g_dendritecleft;        /**< Dendritic synaptic cleft, input to the neuron */
    std::vector <neuroreceptor> g_neuroreceptor;        /**< Neuroreceptor, component of dendritic cleft   */
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
    std::vector <neurotransmitter> g_neurotransmitter;  /**< Neurotransmitter, transfer component between clefts */
    
    
    const int numUniverses = 2;     // Physical material and spatial references
    const int numDimensions [numUniverses] = {1, 4};    // U1 = Physical, U2 = Spatial X,Y,Z & Time
    const int phyDimensionsStart = 0;
    const int spaDimensionsStart = phyDimensionsStart + numDimensions[phyDimensionsStart];
    const int initialElementaryParticles = 100;
    const int initialParticleAlignment = 500;
    const int infiniteLoopPrevention = 1000;
    
    double l_screenX = 900;            /**< Define graphics window size, X axis*/
    double l_screenY = 750;            /**< Define graphics window size, Y axis*/
    double l_scale = 0.05;             /**< Vertices are multiplied by this factor to enable fitting within the graphics window. Adjust to suit environment */
    std::string l_screenTitle = "Clustering";
    std::stringstream l_title;
    
    if (!g_font.loadFromFile(resourcePath() + "DroidSans.ttf"))
        {
        std::cout << "Font failed to load!" << std::endl;
            //        printf("File should be located in: %s", dir);
        return 1;
        }
    
        // Open SFML graphics window and add title
    sf::RenderWindow window(sf::VideoMode(l_screenX, l_screenY), l_screenTitle);
    g_text.setFont(g_font);
    g_text.setCharacterSize(24);
    g_text.setColor(sf::Color::Green);
    g_text.setStyle(sf::Text::Bold);
    g_text.setString("Initialising...");
    
        // Set-up the simulation environment. Currently a skeletal environment.
    std::cout << "The Big Bang..." << std::endl;
    
    g_Universe.clear();    // Ensure vector is empty
    for (int nloop = 0; nloop <= numUniverses - 1 ; nloop++) {
        int createUniverse = create_Universe(&g_Universe);    // g_Universe is a vector of pointers to each Universe instance
        if (createUniverse)
            {
            std::cout << "Universe creation failed!" << std::endl;
            return 1;
            }
        g_Universe[nloop].creation();   // Proof of creation by accessing method of instance (See console output)
    }
    
    g_Dimension.clear();    // Ensure vector is empty
    for (int ploop = 0; ploop <= numUniverses - 1; ploop++) {               // Cycle through Universes allocating n Dimensions
        for (int nloop = 0; nloop <= numDimensions[ploop] - 1; nloop++) {   // Visit create Dimensions n times
            int addDimension = add_Dimension(&g_Dimension, &g_Universe, ploop);  // Connect the Dimension to the respective Universe
            if (addDimension)                                              // If return number is not 0 then an error occurred
                {
                std::cout << "Dimension addition failed!" << std::endl;    // Console output of error
                return 1;
                }
            g_Dimension[nloop].creation();   // Proof of creation by accessing method of instance (See console output)
        }
    }
    
    int counter_Charge = -1; // Used to loop between min 0 and max 6
    int counter_Spin = 0;
    int counter_Walk = 0;
    int counter_InfiniteLoopPrevention = 0;
    int howMany_Particles = 0;
    int current_Distance = 0;
    int max_Distance = 0;
    bool l_switch = true;
    int l_origin = 0;
    int l_origin_Test1 = 0;
    int l_origin_Test3 = 0;
    int l_origin_Test5 = 0;
    double l_charge = 0;
    
    g_ElementaryParticle.clear();
    g_ElementaryForce.clear();
    for (int nloop = 0; nloop < initialElementaryParticles; nloop++)
        {
        int addElementaryParticle = add_ElementaryParticle(&g_ElementaryParticle, &g_Dimension, phyDimensionsStart);
        if (addElementaryParticle)
            {
            std::cout << "Elementary Particle addition failed!" << std::endl;
            return 1;
            }
            //        counter_Charge = int( counter_Charge + 1 ) * ( 1 - div( counter_Charge, 6 ).quot);
        counter_Charge++;
        if(counter_Charge > 6) counter_Charge = 0;
        counter_Spin = int(1 - counter_Spin);
            //        std::cout << counter_Charge << std::endl;
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().setCharge(counter_Charge);
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().setSpin(counter_Spin);
        if (!g_ElementaryParticle.empty()) g_ElementaryParticle.back().creation();
        
        
        int addElementaryForce = add_ElementaryForce(&g_ElementaryForce, &g_ElementaryParticle, nloop);
        if (addElementaryForce)
            {
            std::cout << "Elementary Force addition failed!" << std::endl;
            return 1;
            }
        if (!g_ElementaryForce.empty()) g_ElementaryForce.back().creation();
        
        howMany_Particles = int(g_ElementaryParticle.size());
        
            //        std::cout << "Size:" << howMany_Particles << std::endl;
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
                    if (l_switch) counter_Walk--; else counter_Walk++;
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
    
    
    for (int zloop = 0; zloop < int(g_ElementaryParticle.size()); zloop++ )
        {
        std::cout << g_ElementaryParticle[zloop].getCharge() << " ";
        }
    std::cout << std::endl;
    
    g_CompositeParticle.clear();
    int addCompositeParticle = add_CompositeParticle(&g_CompositeParticle, &g_ElementaryParticle, int(g_ElementaryParticle.size() - 1));
    if (addCompositeParticle)
        {
        std::cout << "Composite Particle addition failed!" << std::endl;
        return 1;
        }
    if (!g_CompositeParticle.empty()) g_CompositeParticle.back().creation();
    
    g_CompositeForce.clear();
    int addCompositeForce = add_CompositeForce(&g_CompositeForce, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addCompositeForce)
        {
        std::cout << "Composite Force addition failed!" << std::endl;
        return 1;
        }
    if (!g_CompositeForce.empty()) g_CompositeForce.back().creation();
    
    g_Matter.clear();
    int addMatter = add_Matter(&g_Matter, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addMatter)
        {
        std::cout << "Matter addition failed!" << std::endl;
        return 1;
        }
    if (!g_Matter.empty()) g_Matter.back().creation();
    
    g_Point.clear();
    for (int nloop = numDimensions[phyDimensionsStart]; nloop <= numDimensions[spaDimensionsStart]; nloop++) {
        int addPoint = add_Point(&g_Point, &g_Dimension, nloop);
        if (addPoint)
            {
            std::cout << "Point addition failed!" << std::endl;
            return 1;
            }
        if (!g_Point.empty()) g_Point.back().creation();
        if (!g_Point.empty()) g_Point.back().setPointDifferential(0);  // Set first point to location zero.
    }
    
    for (int eloop = 1; eloop < int(g_ElementaryParticle.size()) - 1; eloop++)
        {
        
        l_charge = double (3 - std::abs(int(g_ElementaryParticle[eloop].getCharge() - g_ElementaryParticle[eloop - 1].getCharge()))) / 3 ;
        
        for (int nloop = numDimensions[phyDimensionsStart]; nloop <= numDimensions[spaDimensionsStart]; nloop++) {
            int addPoint = add_Point(&g_Point, &g_Dimension, nloop);
            if (addPoint)
                {
                std::cout << "Point addition failed!" << std::endl;
                return 1;
                }
            if (!g_Point.empty()) g_Point.back().Creation();
            g_Point.back().setPointPosition(g_Point[g_Point.size() - numDimensions[spaDimensionsStart] - 1].getPointPosition() +l_charge);
        }
        }
    
    int l_pointEnd = int(g_Point.size()) - 1;
    
        // The program will loop whilst the graphics window is open
    while(window.isOpen())
        {
            // SFML event handling to define what happens if the graphics window is closed
        sf::Event event;
        while (window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
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
        
        
            // Now to put all the calculations into something visual. Drawing to the screen. Scaled and orientated.
        g_drawPoints.clear();
        for(int n = 0; n < l_pointEnd; n++)
            {
            g_drawPoints.push_back(sf::Vertex(sf::Vector2f((g_Point[n].getPointPosition() * l_scale) + (l_screenX / 2), l_screenY - ((g_Point[n].getPointPosition() * l_scale) + (l_screenY / 2))), sf::Color(255,255,0,255)));
            }
        g_drawLines.clear();
/*
        for(int n = 0; n < l_LineEnd; n++)
            {
            g_drawLines.push_back(sf::Vertex(sf::Vector2f((g_Line[n].GetLineX1() * l_scale) + (l_screenX / 2), l_screenY - ((g_Line[n].GetLineY1() * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) * g_Point[n].GetXYTTL()),0,0,255)));
            g_drawLines.push_back(sf::Vertex(sf::Vector2f((g_Line[n].GetLineX2() * l_scale) + (l_screenX / 2), l_screenY - ((g_Line[n].GetLineY2() * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) * g_Point[n].GetXYTTL()),0,0,255)));
            }
*/        
        window.clear();
        
        window.draw(&g_drawQuads[0], g_drawQuads.size(), sf::Quads);
        for (const auto& g_text : g_drawQuadText) { window.draw(g_text); }
        
        window.draw(&g_drawPoints[0], g_drawPoints.size(), sf::Points);
        
        window.draw(&g_drawLines[0], g_drawLines.size(), sf::Lines);
        
        l_title.str("");
        l_title.clear();
        l_title << "Clustering";
        g_text.setString(l_title.str());
        g_text.setCharacterSize(12);
        g_text.setPosition(sf::Vector2f((l_screenX - (l_title.str().size() * 6)) / 2,0));
        window.draw(g_text);
        l_title.str("");
        l_title.clear();
        l_title << "Localise : Discover";
        g_text.setString(l_title.str());
        g_text.setCharacterSize(9);
        g_text.setPosition(sf::Vector2f((l_screenX - (l_title.str().size() * 3)) / 2,55));
        window.draw(g_text);
        sf::RectangleShape toggleBackground(sf::Vector2f(50,25));
        toggleBackground.setFillColor(sf::Color::Green);
        toggleBackground.setPosition(sf::Vector2f((l_screenX / 2 ) - (20 / 2), 30));
        window.draw(toggleBackground);
        sf::RectangleShape toggleForground(sf::Vector2f(25,25));
        toggleForground.setFillColor(sf::Color::Red);
        toggleForground.setPosition(sf::Vector2f(((l_screenX / 2 ) - (20 / 2)) + (25 * g_toggle), 30));
        window.draw(toggleForground);
        window.display();
        }
        // Empty vectors before exiting (in reverse of creation)
        //    g_Point.clear();
        //    g_Matter.clear();
        //    g_CompositeForce.clear();
        //    g_CompositeParticle.clear();
        //    g_ElementaryForce.clear();
        //    g_ElementaryParticle.clear();
        //    g_Dimension.clear();
        //    g_Universe.clear();
    
    return EXIT_SUCCESS;
}
