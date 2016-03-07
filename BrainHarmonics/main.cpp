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
/* emulation and real-world universes.                                             */

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

    // Homegrown add-ins
#include <universe.h>           /**< Top of the tree, begin with Universe class    */
#include <dimension.h>          /**< Add dimensions for spatial identification     */
#include <elementaryparticle.h> /**< Follow with the creation of quarks/leptons    */
#include <compositeparticle.h>  /**< Basic interactions form protons/neutrons      */
#include <elementaryforce.h>    /**< Define force interaction between fundamentals */
#include <compositeforce.h>     /**< Define force interaction between composites   */
#include <law.h>                /**< Specify how composites interact               */
#include <matter.h>             /**< Composites form elements of periodic table    */
#include <solid.h>              /**< Materials are a combination of matter         */
#include <polyhedron.h>         /**< Materials can be formed into multidimensional shapes */
#include <polygon.h>            /**< Complex shapes are a combination of simpler forms */
#include <quad.h>               /**< Reducing high dimensions to lower             */
#include <line.h>               /**< Further reduction                             */
#include <point.h>              /**< Fundamental spatial description               */
#include <node.h>               /**< Node class for A* search                      */
#include <apptimer.h>           /**< Interim function describing time before inclusion as dimension */

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


    // Function to create a universe instance. Universes could be simulation, emulation, real or contemplative (What-if)
int create_universe(std::vector<universe> &toAddto)
{
        // First, there is nothing. Then there was something...
    double UniverseEnergy = 999999999;              /**< Defined energy level of Universe */
        // Begin with singularity
    universe myUniverse;                            /**< Create instance of Universe from Universe class */
    toAddto.push_back(myUniverse);               /**< Store pointer to this instance of the Universe in a vector */
    toAddto[toAddto.size()].SetEnergy(UniverseEnergy);
    /**< Set an energy level and attempt to maintain physics laws by keeping the total in the Universe the same. Uses the maximum value for double. Levels of abstraction used to cater for environment limitations */
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding dimensions enables physical and spatial calculations
int add_dimension(std::vector<dimension> &toAddto, std::vector<universe> &aPartof, int arrayEntry)
{
    dimension myDimension(aPartof[arrayEntry]);
    toAddto.push_back(myDimension);
    
    return 0;                       /**< Return Success = 0 */
}

    // Each add_ function creates an instance of the respective class and links back to the base class
    // For definition of quarks and leptons when simulating real-world environment
int add_elementaryparticle(std::vector<elementaryparticle> &toAddto, std::vector<dimension> &aPartof, int arrayEntry)
{
    elementaryparticle myElementaryparticle(aPartof[arrayEntry]);
    toAddto.push_back(myElementaryparticle);
    
    return 0;                       /**< Return Success = 0 */
}

    // For real-world definition of protons & neutrons. Other combinations in artificial environments
int add_compositeparticle(std::vector<compositeparticle> &toAddto, std::vector<elementaryparticle> &aPartof, int arrayEntry)
{
    compositeparticle myCompositeparticle(aPartof[arrayEntry]);
    toAddto.push_back(myCompositeparticle);
    
    return 0;                       /**< Return Success = 0 */
}

    // Methods in this class to define interaction. Which may be different between artificial, simulation and real environments
int add_elementaryforce(std::vector<elementaryforce> &toAddto, std::vector<elementaryparticle> &aPartof, int arrayEntry)
{
    elementaryforce myForce(aPartof[arrayEntry]);
    toAddto.push_back(myForce);
    
    return 0;                       /**< Return Success = 0 */
}

int add_compositeforce(std::vector<compositeforce> &toAddto, std::vector<compositeparticle> &aPartof, int arrayEntry)
{
    compositeforce myForce(aPartof[arrayEntry]);
    toAddto.push_back(myForce);
    
    return 0;                       /**< Return Success = 0 */
}

    // Add methods to describe force interactions such as gravity
int add_law(std::vector<compositeforce> &toAddto, int arrayEntry, std::vector<compositeparticle> &toAddto2, int arrayEntry2)
{
        //    law myLaw(aPartof[arrayEntry], toAddto2[arrayEntry2]);
        //    toAddto.push_back(myLaw);
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of periodic table of elements
int add_matter(std::vector<matter> &toAddto, std::vector<compositeparticle> &aPartof, int arrayEntry)
{
    matter myMatter(aPartof[arrayEntry]);
    toAddto.push_back(myMatter);
    
    return 0;                       /**< Return Success = 0 */
}

    // Description of material
int add_solid(std::vector<solid> &toAddto, std::vector<matter> &aPartof, int arrayEntry)
{
    solid mySolid(aPartof[arrayEntry]);
    toAddto.push_back(mySolid);
    
    return 0;                       /**< Return Success = 0 */
}

    // Fundamental spatial element
int add_point(std::vector<point> &toAddto, std::vector<dimension> &aPartof, int arrayEntry)
{
        // Begin with shape singularity
    point myPoint(aPartof[arrayEntry]);
    toAddto.push_back(myPoint);
    
    return 0;                       /**< Return Success = 0 */
}

    // Complex shapes
int add_polyhedron(std::vector<polyhedron> &toAddto, std::vector<solid> &aPartof, int arrayEntry)
{
    polyhedron myPolyhedron(aPartof[arrayEntry]);
    toAddto.push_back(myPolyhedron);
    
    return 0;                       /**< Return Success = 0 */
}

    // Components of complex shapes
int add_polygon(std::vector<polygon> &toAddto, std::vector<polyhedron> &aPartof, int arrayEntry)
{
    polygon myPolygon(aPartof[arrayEntry]);
    toAddto.push_back(myPolygon);
    
    return 0;                       /**< Return Success = 0 */
}

    // Base 2D shapes
int add_quad(std::vector<quad> &toAddto, std::vector<polygon> &aPartof, int arrayEntry)
{
    quad myQuad(aPartof[arrayEntry]);
    toAddto.push_back(myQuad);
    
    return 0;                       /**< Return Success = 0 */
}

    // Component of shapes, straight, curved or complex
int add_line(std::vector<line> &toAddto, std::vector<polygon> &aPartof, int arrayEntry)
{
    line myLine(aPartof[arrayEntry]);
    toAddto.push_back(myLine);
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding application timer temporarily until integrated into Dimension class
int add_apptimer(std::vector<apptimer> &toAddto)
{
    apptimer myApptimer;
    toAddto.push_back(myApptimer);
    
    return 0;                       /**< Return Success = 0 */
}

int main(int argc, const char * argv[]) {
        // Index arrays for instances of classes described above
    std::vector <universe> g_universe;
    std::vector <dimension> g_dimension;
    std::vector <elementaryparticle> g_elementaryparticle;
    std::vector <compositeparticle> g_compositeparticle;
    std::vector <elementaryforce> g_elementaryforce;
    std::vector <compositeforce> g_compositeforce;
    std::vector <law> g_law;
    std::vector <matter> g_matter;
    std::vector <solid> g_solid;
    std::vector <polyhedron> g_polyhedron;
    std::vector <polygon> g_polygon;
    std::vector <quad> g_quad;
    std::vector <line> g_line;
    std::vector <point> g_point;
    std::vector <apptimer> g_apptimer;
    
    
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
    
    std::cout << "Hello, World!\n";
    
        // Set-up the simulation environment. Currently a skeletal environment.
    std::cout << "The Big Bang..." << std::endl;
    
    g_universe.clear();    // Ensure vector is empty
    for (int nloop = 0; nloop <= numUniverses - 1 ; nloop++) {
        int createUniverse = create_universe(g_universe);    // g_universe is a vector of pointers to each Universe instance
        if (createUniverse)
            {
            std::cout << "Universe creation failed!" << std::endl;
            return 1;
            }
        g_universe[nloop].Creation();   // Proof of creation by accessing method of instance (See console output)
    }
    
    g_dimension.clear();    // Ensure vector is empty
    for (int ploop = 0; ploop <= numUniverses - 1; ploop++) {               // Cycle through universes allocating n dimensions
        for (int nloop = 0; nloop <= numDimensions[ploop] - 1; nloop++) {   // Visit create dimensions n times
            int addDimension = add_dimension(g_dimension, g_universe, ploop);  // Add the dimension to the respective universe
            if (addDimension)                                              // If return number is not 0 then an error occurred
                {
                std::cout << "Dimension addition failed!" << std::endl;    // Console output of error
                return 1;
                }
            g_dimension[nloop].Creation();   // Proof of creation by accessing method of instance (See console output)
        }
    }
    
    int counter_Charge = -1; // Used to loop between min 0 and max 6
    int counter_Spin = 0;
    int counter_Walk = 0;
    int l_origin_Test1 = 0;
    int l_origin_Test2 = 0;
    
    g_elementaryparticle.clear();
    g_elementaryforce.clear();
    for (int nloop = 0; nloop < initialElementaryParticles; nloop++)
        {
        int addElementaryparticle = add_elementaryparticle(g_elementaryparticle, g_dimension, phyDimensionsStart);
        if (addElementaryparticle)
            {
            std::cout << "Elementary particle addition failed!" << std::endl;
            return 1;
            }
            //        counter_Charge = int( counter_Charge + 1 ) * ( 1 - div( counter_Charge, 6 ).quot);
        counter_Charge++;
        if(counter_Charge > 6) counter_Charge = 0;
        counter_Spin = int(1 - counter_Spin);
        std::cout << counter_Charge << std::endl;
        g_elementaryparticle[0].SetCharge(counter_Charge);
        g_elementaryparticle[0].SetSpin(counter_Spin);
        g_elementaryparticle[0].Creation();
        
        
        int addElementaryforce = add_elementaryforce(g_elementaryforce, g_elementaryparticle, nloop);
        if (addElementaryforce)
            {
            std::cout << "Elementary force addition failed!" << std::endl;
            return 1;
            }
        g_elementaryforce[0].Creation();
        
        std::cout << "Size:" << g_elementaryparticle.size() << std::endl;
        
        while(counter_Walk <= (int(g_elementaryparticle.size()) - 4))
            {
            l_origin_Test1 = abs(int(g_elementaryparticle[counter_Walk].GetCharge()) - int(g_elementaryparticle[counter_Walk + 1].GetCharge()));
            l_origin_Test2 = abs(int(g_elementaryparticle[counter_Walk].GetCharge()) - int(g_elementaryparticle[counter_Walk + 2].GetCharge()));
            std::cout << "Test1:" << l_origin_Test1 << " Test2:" << l_origin_Test2 << std::endl;
            if(l_origin_Test1 < l_origin_Test2)
                {
                iter_swap(g_elementaryparticle.begin() + (counter_Walk + 1), g_elementaryparticle.begin() + (counter_Walk + 2));
                counter_Walk--;
                if (counter_Walk < 0) counter_Walk = 0;
                }
            else
                {
                counter_Walk++;
                }
                //            std::cout << "Walk:" << counter_Walk << std::endl;
            }
        for(int xloop = 0;xloop < nloop; xloop++)
            {
            std::cout << "xloop:" << xloop << " nloop:" << nloop << std::endl;
            std::cout << int(g_elementaryparticle[xloop].GetCharge());
            }
        std::cout << std::endl;
        }
    
    g_compositeparticle.clear();
    int addCompositeparticle = add_compositeparticle(g_compositeparticle, g_elementaryparticle, 0);
    if (addCompositeparticle)
        {
        std::cout << "Composite particle addition failed!" << std::endl;
        return 1;
        }
    g_compositeparticle[0].Creation();
    
    g_compositeforce.clear();
    int addCompositeforce = add_compositeforce(g_compositeforce, g_compositeparticle, 0);
    if (addCompositeforce)
        {
        std::cout << "Composite force addition failed!" << std::endl;
        return 1;
        }
    g_compositeforce[0].Creation();
    
    g_matter.clear();
    int addMatter = add_matter(g_matter, g_compositeparticle, 0);
    if (addMatter)
        {
        std::cout << "Matter addition failed!" << std::endl;
        return 1;
        }
    g_matter[0].Creation();
    
    g_point.clear();
    for (int nloop = numDimensions[phyDimensionsStart]; nloop <= numDimensions[spaDimensionsStart]; nloop++) {
        int addPoint = add_point(g_point, g_dimension, nloop);
        if (addPoint)
            {
            std::cout << "Point addition failed!" << std::endl;
            return 1;
            }
        g_point[0].Creation();
    }
    
    
        // Empty vectors before exiting (in reverse of creation)
    g_point.clear();
    g_matter.clear();
    g_compositeforce.clear();
    g_compositeparticle.clear();
    g_elementaryforce.clear();
    g_elementaryparticle.clear();
    g_dimension.clear();
    g_universe.clear();
    
    return 0;
}
