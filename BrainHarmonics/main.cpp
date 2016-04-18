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

    // SFML - Use DYLIBS not FRAMEWORKS. FRAMEWORKS had a problem with Text and missing symbols
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>    /**< Graphics library http://sfml-dev.org          */
#include "ResourcePath.hpp"

/* Can't use GLUT on El Capitan - poor headers
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
*/

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
#include "multiscreen.h"        /**< Screen layouts                                */
    //#include "screen_0.hpp"         /**< Screen layouts                                */
    //#include "screen_1.hpp"         /**< Screen layouts                                */

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
    /**< Set an energy level and attempt to maintain physics laws by keeping the total in the Universe the same. Uses the maximum value for double. Levels of abstraction used to cater for environment limitations */
    myUniverse.setEnergy(UniverseEnergy);
        // Use move not push_back otherwise data is destroyed on exiting function
        //    std::copy(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));
    std::move(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding Dimensions enables physical and spatial calculations
    // Possible to use this as a basis for higher dimensionality if it becomes relevant
int add_Dimension(std::vector<Dimension> *toAddto, std::vector<Universe> *aPartof, int arrayEntry)
{
    Dimension myDimension((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myDimension, &myDimension + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Each add_ function creates an instance of the respective class and links back to the base class
    // For definition of quarks and leptons when simulating real-world environment
int add_ElementaryParticle(std::vector<ElementaryParticle> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
    ElementaryParticle myElementaryParticle((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myElementaryParticle, &myElementaryParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // For real-world definition of protons & neutrons. Other combinations in artificial environments
int add_CompositeParticle(std::vector<CompositeParticle> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    CompositeParticle myCompositeParticle((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myCompositeParticle, &myCompositeParticle + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Methods in this class to define interaction. Which may be different between artificial, simulation and real environments
int add_ElementaryForce(std::vector<ElementaryForce> *toAddto, std::vector<ElementaryParticle> *aPartof, int arrayEntry)
{
    ElementaryForce myForce((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

int add_CompositeForce(std::vector<CompositeForce> *toAddto, std::vector<CompositeParticle> *aPartof, int arrayEntry)
{
    CompositeForce myForce((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myForce, &myForce + 1, std::back_inserter(*toAddto));
    
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
    std::move(&myMatter, &myMatter + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of simple molecules
int add_Monomer(std::vector<Monomer> *toAddto, std::vector<Matter> *aPartof, int arrayEntry)
{
    Monomer myMonomer((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myMonomer, &myMonomer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Class for definition of complex molecules
int add_Polymer(std::vector<Polymer> *toAddto, std::vector<Monomer> *aPartof, int arrayEntry)
{
    Polymer myPolymer((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myPolymer, &myPolymer + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Description of material
int add_Solid(std::vector<Solid> *toAddto, std::vector<Matter> *aPartof, int arrayEntry)
{
    Solid mySolid((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&mySolid, &mySolid + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Fundamental spatial element
int add_Point(std::vector<Point> *toAddto, std::vector<Dimension> *aPartof, int arrayEntry)
{
        // Begin with shape singularity
    Point myPoint((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myPoint, &myPoint + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Complex shapes
int add_Polyhedron(std::vector<Polyhedron> *toAddto, std::vector<Solid> *aPartof, int arrayEntry)
{
    Polyhedron myPolyhedron((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myPolyhedron, &myPolyhedron + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Components of complex shapes
int add_Polygon(std::vector<Polygon> *toAddto, std::vector<Polyhedron> *aPartof, int arrayEntry)
{
    Polygon myPolygon((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myPolygon, &myPolygon + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Base 2D shapes
int add_Quad(std::vector<Quad> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Quad myQuad((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myQuad, &myQuad + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Component of shapes, straight, curved or complex
int add_Line(std::vector<Line> *toAddto, std::vector<Polygon> *aPartof, int arrayEntry)
{
    Line myLine((*aPartof)[arrayEntry]);
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myLine, &myLine + 1, std::back_inserter(*toAddto));
    
    return 0;                       /**< Return Success = 0 */
}

    // Adding application timer temporarily until integrated into Dimension class
int add_Apptimer(std::vector<Apptimer> *toAddto)
{
    Apptimer myApptimer;
        // Use move not push_back otherwise data is destroyed on exiting function
    std::move(&myApptimer, &myApptimer + 1, std::back_inserter(*toAddto));
    
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
    
    std::move(&mySFMLRectangle, &mySFMLRectangle + 1, std::back_inserter(*toAddto));
    
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
    
    std::move(&mySFMLText, &mySFMLText + 1, std::back_inserter(*toAddto));
    
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
    
    if (!Font.loadFromFile(resourcePath() + "DroidSans.ttf"))
        {
        std::cerr << "Error loading font." << std::endl;
        return (-1);
        }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Add item");
    Menu1.setPosition({ 280.f, 160.f });
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Remove item");
    Menu2.setPosition({ 280.f, 220.f });
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Up level");
    Menu3.setPosition({ 280.f, 280.f });
    
    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Down level");
    Menu4.setPosition({ 280.f, 320.f });
    
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
    
    if (!Font.loadFromFile(resourcePath() + "DroidSans.ttf"))
        {
        std::cerr << "Error loading font." << std::endl;
        return (-1);
        }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Add item");
    Menu1.setPosition({ 280.f, 160.f });
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Remove item");
    Menu2.setPosition({ 280.f, 220.f });
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Up level");
    Menu3.setPosition({ 280.f, 280.f });
    
    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Down level");
    Menu4.setPosition({ 280.f, 320.f });
    
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
    
    
    const int numUniverses = 3;     // Internal display, Physical material and spatial references
    const int numDimensions [numUniverses] = {2, 1, 4};    // U1 = Internal X & Y, U2 = Physical, U3 = Spatial X,Y,Z & Time
    const int intDimensionsStart = 0;
    const int phyDimensionsStart = intDimensionsStart + numDimensions[0];
    const int spaDimensionsStart = phyDimensionsStart + numDimensions[1];
    const int initialElementaryParticles = 100;
    const int initialParticleAlignment = 200;
    const int infiniteLoopPrevention = 800;
    
    int addStatus;
    
    double l_screenX = 925;            /**< Define graphics window size, X axis*/
    double l_screenY = 800;            /**< Define graphics window size, Y axis*/
    double l_scale = 200;               /**< Vertices are multiplied by this factor to enable fitting within the graphics window. Adjust to suit environment */
    std::string l_screenTitle = "Clustering";
    std::stringstream l_displayString;
    
    if (!g_font.loadFromFile(resourcePath() + "DroidSans.ttf"))
        {
        std::cout << "Font failed to load!" << std::endl;
            //        printf("File should be located in: %s", dir);
        return 1;
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
    for(int nloop = 0; nloop < 10; nloop++)
        {
        addStatus = add_SFMLRectangle(&g_drawRectangles, &g_Dimension, 0);
        if (addStatus)
            {
            std::cout << "Rectangle addition failed!" << std::endl;
            return 1;
            }
        }
    
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
            return 1;
            }
        }
    
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
    
        // No GLUT on El Capitan - poort headers
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
    std::cout << "The Big Bang..." << g_drawText.size() << std::endl;
    
        // g_Universe is a vector of pointers to the Universe objects.
    g_Universe.clear();    // Ensure vector is empty
    for (int nloop = 0; nloop <= numUniverses - 1 ; nloop++) {
            // Pass the g_Universe address to the create function to keep all Universes within the same vector
        addStatus = create_Universe(&g_Universe);
        if (addStatus)
            {
            std::cout << "Universe creation failed!" << std::endl;
            return 1;
            }
        g_Universe[nloop].creation();   // Proof of creation by accessing method of instance (See console output)
    }
    
    g_Dimension.clear();    // Ensure vector is empty
    for (int ploop = 0; ploop <= numUniverses - 1; ploop++) {               // Cycle through Universes allocating n Dimensions
        for (int nloop = 0; nloop <= numDimensions[ploop] - 1; nloop++) {   // Visit create Dimensions n times
            addStatus = add_Dimension(&g_Dimension, &g_Universe, ploop);  // Connect the Dimension to the respective Universe
            if (addStatus)                                              // If return number is not 0 then an error occurred
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
    int l_spaPointBase = 0; // Base of data points (Moves because of use by internal graphics for points control too
    int howMany_Particles = 0;
    int current_Distance = 0;
    int max_Distance = 0;
    bool l_switch = true;
    int l_origin = 0;
    int l_origin_Test1 = 0;
    int l_origin_Test3 = 0;
    int l_origin_Test5 = 0;
    double l_charge = 0;
    
        // Create new Elementary Particles - Quarks etc
    g_ElementaryParticle.clear();
    g_ElementaryForce.clear();
    for (int nloop = 0; nloop < initialElementaryParticles; nloop++)
        {
        addStatus = add_ElementaryParticle(&g_ElementaryParticle, &g_Dimension, phyDimensionsStart);
        if (addStatus)
            {
            std::cout << "Elementary Particle addition failed!" << std::endl;
            return 1;
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
            return 1;
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
    
    
    for (int zloop = 0; zloop < int(g_ElementaryParticle.size()); zloop++ )
        {
        std::cout << g_ElementaryParticle[zloop].getCharge() << " ";
        }
    std::cout << std::endl;
    
        // Make Composite Particles - Protons, Neutrons
    g_CompositeParticle.clear();
    addStatus = add_CompositeParticle(&g_CompositeParticle, &g_ElementaryParticle, int(g_ElementaryParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Composite Particle addition failed!" << std::endl;
        return 1;
        }
    if (!g_CompositeParticle.empty()) g_CompositeParticle.back().creation();
    
    g_CompositeForce.clear();
    addStatus = add_CompositeForce(&g_CompositeForce, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Composite Force addition failed!" << std::endl;
        return 1;
        }
    if (!g_CompositeForce.empty()) g_CompositeForce.back().creation();
    
        // Make Elements - Hydrogen, Helium, Lithium etc
    g_Matter.clear();
    addStatus = add_Matter(&g_Matter, &g_CompositeParticle,  int(g_CompositeParticle.size() - 1));
    if (addStatus)
        {
        std::cout << "Matter addition failed!" << std::endl;
        return 1;
        }
    if (!g_Matter.empty()) g_Matter.back().creation();
    
        // Make Monomers - Carbohydrates/Sugars etc
    g_Monomer.clear();
    addStatus = add_Monomer(&g_Monomer, &g_Matter,  int(g_Matter.size() - 1));
    if (addStatus)
        {
        std::cout << "Monomer addition failed!" << std::endl;
        return 1;
        }
    if (!g_Monomer.empty()) g_Monomer.back().creation();
    
    g_Polymer.clear();
    addStatus = add_Polymer(&g_Polymer, &g_Monomer,  int(g_Monomer.size() - 1));
    if (addStatus)
        {
        std::cout << "Polymer addition failed!" << std::endl;
        return 1;
        }
    if (!g_Polymer.empty()) g_Polymer.back().creation();
    
    g_Point.clear();
    
        // Add points to control application screen positions
    l_spaPointBase = 0;
    for (int zloop = 0; zloop < int(g_drawRectangles.size()) + int(g_drawText.size()); zloop++)
        {
        for (int nloop = intDimensionsStart; nloop < phyDimensionsStart; nloop++)
            {
            addStatus = add_Point(&g_Point, &g_Dimension, nloop);
            if (addStatus)
                {
                std::cout << "Point addition failed!" << std::endl;
                return 1;
                }
            if (!g_Point.empty()) g_Point.back().creation();
            if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
            l_spaPointBase++;
        }
        }
    std::cout << "spaPointBase: " << l_spaPointBase << std::endl;
    
    g_Point[0].setPointPosition(800);    g_Point[1].setPointPosition(25);   // Rectangle 1
    g_Point[2].setPointPosition(800);    g_Point[3].setPointPosition(50);   // Rectangle 2
    g_Point[4].setPointPosition(800);    g_Point[5].setPointPosition(75);   // Rectangle 3
    g_Point[6].setPointPosition(800);    g_Point[7].setPointPosition(100);  // Rectangle 4
    g_Point[8].setPointPosition(800);    g_Point[9].setPointPosition(125);  // Rectangle 5
    g_Point[10].setPointPosition(800);   g_Point[11].setPointPosition(150); // Rectangle 6
    g_Point[12].setPointPosition(800);   g_Point[13].setPointPosition(175); // Rectangle 7
    g_Point[14].setPointPosition(800);   g_Point[15].setPointPosition(200); // Rectangle 8
    g_Point[16].setPointPosition(800);   g_Point[17].setPointPosition(225); // Rectangle 9
    g_Point[18].setPointPosition(800);   g_Point[19].setPointPosition(25);  // Rectangle 10
    g_Point[20].setPointPosition(400);   g_Point[21].setPointPosition(0);   // Text 1
    g_Point[22].setPointPosition(800);   g_Point[23].setPointPosition(25);  // Text 2
    g_Point[24].setPointPosition(800);   g_Point[25].setPointPosition(50);  // Text 3
    g_Point[26].setPointPosition(800);   g_Point[27].setPointPosition(75);  // Text 4
    g_Point[28].setPointPosition(800);   g_Point[29].setPointPosition(100); // Text 5
    g_Point[30].setPointPosition(800);   g_Point[31].setPointPosition(125); // Text 6
    g_Point[32].setPointPosition(800);   g_Point[33].setPointPosition(150); // Text 7
    g_Point[34].setPointPosition(800);   g_Point[35].setPointPosition(175); // Text 8
    g_Point[36].setPointPosition(800);   g_Point[37].setPointPosition(200); // Text 9
    g_Point[38].setPointPosition(800);   g_Point[39].setPointPosition(225); // Text 10
    
    for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + numDimensions[2]; nloop++)
        {
        std::cout << "Dimension Loop: " << nloop << " ";
        addStatus = add_Point(&g_Point, &g_Dimension, nloop);
        if (addStatus)
            {
            std::cout << "Point addition failed!" << std::endl;
            return 1;
            }
        if (!g_Point.empty()) g_Point.back().creation();
        if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise first point to location zero.
    }
        std::cout << std::endl;
    double d;
    double r;
    double s;
    double t;
    double pOrigin;
    double xd;
    double yd;
    double zd;
    double pointDistance;
    double pointDistance2;
    double effect;
    
    for (int eloop = 1; eloop < int(g_ElementaryParticle.size()); eloop++)
        {
        
        l_charge = double (3 - std::abs(int(g_ElementaryParticle[eloop].getCharge() - g_ElementaryParticle[eloop - 1].getCharge())));
        
        for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + numDimensions[2]; nloop++) {
            addStatus = add_Point(&g_Point, &g_Dimension, nloop);
            if (addStatus)
                {
                std::cout << "Point addition failed!" << std::endl;
                return 1;
                }
            if (!g_Point.empty()) g_Point.back().creation();
            if (!g_Point.empty()) g_Point.back().resetPoint();  // Initialise point to location zero.
            
                // To calculate the position on the surface of a sphere is:
                // ( where r is radius and s & t are angles in Radians. The Origin is 0,0,0 )
                // x = r * cos(s) * sin(t)
                // y = r * sin(s) * sin(t)
                // z = r * cos(t)
            
                // radians = angleInDegrees * Math.PI / 180
            
            d = 0;
            r = l_charge;
                // This angle to later be dynamic to adjust for different particle types
            s = 30 * DEG2RAD; // in Radians
            t = 90 * DEG2RAD; // in Radians
            pOrigin = g_Point[(g_Point.size() - numDimensions[2]) - 1].getPointPosition();
                // std::cout << "nloop:" << nloop << std::endl;
            
                // Loop through each dimension to calculate position on the surface of a sphere
                // The sphere takes the previous particle as it's Origin and the radius is related to the charge.
                // The position on the surface will be affected by proximity to other particles.
            switch(nloop - spaDimensionsStart)
            {
                case 0:
                {
                d = r * cos(s) * sin(t);
                break;
                }
                case 1:
                {
                d = r * sin(s) * sin(t);
                break;
                }
                case 2:
                {
                d = r * cos(t);
                break;
                }
                case 3:
                {
                d = 0;
                break;
                }
            }
            
            d = d + pOrigin;
                // std::cout << "d:" << d << " r:" << r << " s:" << s << " t:" << t << std::endl;
            g_Point.back().setPointPosition(d);
        }
        }
    
    int l_pointStart = int(l_spaPointBase);
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
                        return (0);
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
        for(int n = l_pointStart; n < l_pointEnd; n++)
            {
                //            std::cout << n << " ";
            g_Point[n].pointPoll(1);
            g_Point[n].overflowPoll();
            }
            //        std::cout << std::endl;
        
            // Now to put all the calculations into something visual. Drawing to the screen. Scaled and orientated.
        g_drawPoints.clear();
        for(int n = l_pointStart; n < l_pointEnd; n = n + numDimensions[2])
            {
            g_drawPoints.push_back(sf::Vertex(sf::Vector2f(((g_Point[n].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenX / 2), l_screenY - (((g_Point[n + 1].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenY / 2))), sf::Color(255,255,0,255)));
                //            std::cout << n << " = " << ((g_Point[n].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenX / 2) << " : " << l_screenY - (((g_Point[n + 1].getPointPosition() / g_Point[n + 2].getPointPosition()) * l_scale) + (l_screenY / 2)) << std::endl;
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
