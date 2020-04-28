/*!
 * @file      BrainHarmonics.cc
 * @details   BrainHarmonics - using harmonics to store and process neural spikes
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
 */

/*!
 * BrainHarmonics is the first code designed to implement Autonomic Asynchronous
 * Recursive Neuromorphic Network. It is an infrastructure designed to enable
 * the creation of emergent properties.
 * A - Self maintaining
 * A - Event/Stimulus driven
 * R - Massive replication of interdependent small objects
 * N - Dynamic self-learning
 * N - Interconnected for scale
 *
 * Based on: https://www.researchgate.net/publication/325069661_An_Outline_of_Artificial_Intelligence_and_Neuromorphic_technology_to_introduce_Auto-Asynchronous_Recursive_Neural_Networks_AARNN
 */

/*!
 * Code snippets used:
 * Syntax comparison - http://stackoverflow.com & http://cplusplus.com
 * Using hierarchical linking the aim is to develop the application to
 * relate to real-world physics. This will then ease mapping between simulation,
 * emulation and real-world Universes.
 */

/*!
 * The Code is primarily C++ however, where optimisations are available C-calls
 * will be used. For connectivity to other datascience resources Python-calls
 * are also supported.
 */

extern "C" {
#include <sys/time.h>           //! header defines the timeval structure
#include <sys/types.h>          //! header defines a minimum set of type definitions
#include <sys/socket.h>         //! makes available a type, socklen_t, which is an unsigned opaque integral
#include <netinet/in.h>         //! defines at least in_port_t and in_addr_t
#include <arpa/inet.h>          //! header makes available the type in_port_t and the type in_addr_t
#include <stdio.h>              //! header defines three variable types, several macros, and various functions for performing input and output
#include <stdlib.h>             //! This header defines several general purpose functions, including dynamic memory management, random number generation, communication with the environment, integer arithmetics, searching, sorting and converting.
#include <fcntl.h>              //! header in the C POSIX library for the C programming language that contains constructs that refer to file control.
#include <unistd.h>             //! header file that provides access to the POSIX operating system API.
#include <assert.h>             //! header file in the standard library of the C programming language that defines the C preprocessor macro assert()
#include <time.h>               //! header defines four variable types, two macro and various functions for manipulating date and time.
}

//! Standard Template Libraries (STL)
#include <array>                //! For array in CRC-32 call
#include <cstring>              //! For handling strings
#include <cstdint>              //! For byte handling in CRC-32
#include <fstream>              //! For reading files
#include <iomanip>              //! Formatting output to console
#include <iostream>             //! For output to console
#include <map>                  //! For open and closed maps in A*
#include <math.h>               //! For Sine, Cosine, Power, Fabs & Sqrt functions
#include <mpi.h>                //! For Open MPI
#include <numeric>              //! For CRC-32
#include <queue>                //! For assigning priority queue in A*
#include <sstream>              //! For stringstream input from console
#include <string>               //! For handling strings
#include <thread>               //! For thread handling
#include <vector>               //! To use vectors, which automatically handle resizing, as arrays to keep track of instances

/*!
 * The Addressable Event Representation is for asynchronous activation transmission.
 * Initially, BrainHarmonics was written to make use of academic test hardware from
 * the Institute of Neuroinformatics at the Univerisity of Zurich / ETH.
 */
#include <libcaercpp/devices/dynapse.hpp>          //! The Dynap-se is a neuromorphic device from UZH/ETH INI.
#include <libcaercpp/libcaer.hpp>                  //! Addressable Event Representation (AER)
#include <libcaercpp/events/packetContainer.hpp>   //! Package/Unpack events within packets
#include <csignal>                                 //! C-library to handle signals
#include <atomic>                                  //! Clarifies access method in multithreading

#define DEFAULTBIASES "data/defaultbiases_values.txt"     //! Initial bias settings for Dynap-se
#define LOWPOWERBIASES "data/lowpowerbiases_values.txt"   //! Low-power bias settings for Dynap-se

/*!
 * Planned feature to use network traffic as an input stimulus to the neural network
 */
#include "sniffex.h"            //! Used along with pcap to capture streaming packets

/*!
 * The VTK_MODULE_INIT is definitely required. Without it NULL is returned to ::New() type calls
 */
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); //! VTK was built with vtkRenderingOpenGL2 //! @suppress("Type cannot be resolved")
VTK_MODULE_INIT(vtkRenderingFreeType); //! @suppress("Type cannot be resolved")
VTK_MODULE_INIT(vtkInteractionStyle); //! @suppress("Type cannot be resolved")
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkColorTransferFunction.h>
#include <vtkContourFilter.h>
#include <vtkCoordinate.h>
#include <vtkFloatArray.h>
#include <vtkMath.h>
#include <vtkParametricFunctionSource.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkAppendPolyData.h>
#include <vtkProgrammableSource.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkReverseSense.h>
#include <vtkSmartPointer.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkTextActor.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkUnsignedCharArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <cmath>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

vtkSmartPointer<vtkRenderWindow> render_window;
vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor;

vtkSmartPointer<vtkPoints> define_points = vtkSmartPointer<vtkPoints>::New();
std::vector<vtkSmartPointer<vtkCellArray>> define_cellarrays;
std::vector<vtkSmartPointer<vtkPolyData>> define_polydata;

std::vector<vtkSmartPointer<vtkSurfaceReconstructionFilter>> define_surfaces;
std::vector<vtkSmartPointer<vtkContourFilter>> define_contourfilters;
std::vector<vtkSmartPointer<vtkReverseSense>> define_reversals;
std::vector<vtkSmartPointer<vtkPolyDataMapper>> define_datamappers;
std::vector<vtkSmartPointer<vtkPolyDataMapper2D>> define_datamappers2D;
std::vector<vtkSmartPointer<vtkActor>> define_actors;
std::vector<vtkSmartPointer<vtkActor2D>> define_actors2D;
std::vector<vtkSmartPointer<vtkTextActor>> define_textactors;

std::vector<vtkSmartPointer<vtkRenderer>> define_renderers;

int static_points_counter = 0;
int static_polygons_counter = 0;
int static_polydata_counter = 0;
int static_cellarrays_counter = 0;
int static_surfaces_counter = 0;
int static_contourfilter_counter = 0;
int static_reversals_counter = 0;
int static_datamappers_counter = 0;
int static_datamappers2D_counter = 0;
int static_actors_counter = 0;
int static_actors2D_counter = 0;
int static_renderers_counter = 0;

int dynamic_points_counter = 0;
int dynamic_polygons_counter = 0;
int dynamic_polydata_counter = 0;
int dynamic_cellarrays_counter = 0;
int dynamic_surfaces_counter = 0;
int dynamic_contourfilter_counter = 0;
int dynamic_reversals_counter = 0;
int dynamic_datamappers_counter = 0;
int dynamic_datamappers2D_counter = 0;
int dynamic_actors_counter = 0;
int dynamic_actors2D_counter = 0;
int dynamic_renderers_counter = 0;

static vtkSmartPointer<vtkPolyData> TransformBack(vtkSmartPointer<vtkPoints> pt, vtkSmartPointer<vtkPolyData> pd);

/*!
 * Interim calls to Python (3.8) to use existing APIs to Neuromorphic hardware and/or Brain simulators
 */
#include <Python.h>             //! Python interpreter
#include <numpy/arrayobject.h>

/*!
 * GLUT on OS X El Capitan - poor headers
 */
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

/*!
 * Homegrown add-ins
 * Real-time emulation at the sub-atomic level across 86 billion neurons of the human brain
 * is not currently practical. BrainHarmonics abstracts and calculates small-scale reference
 * models to guide the sub-set emulation rather than being the whole emulation.
 * Further software enhancement will be to utilise GROMACS for supplemental modelling.
 */
#include "universe.h"                  //! Top of the tree, begin with Universe class
#include "dimension.h"                 //! Add Dimensions for spatial identification
#include "elementaryparticle.h"        //! Follow with the creation of quarks/leptons
#include "elementaryforce.h"           //! Define Force interaction between fundamentals
#include "compositeforceparticle.h"    //! Define ForceParticle interaction between Composites
#include "law.h"                       //! Specify how Composites interact
#include "matter.h"                    //! Composites form elements of periodic table
#include "monomer.h"                   //! Composites form molecules
#include "polymer.h"                   //! Composites form molecules
#include "solid.h"                     //! Materials are a combination of Matter
#include "polyhedron.h"                //! Materials can be formed into multiDimensional shapes
#include "polygon.h"                   //! Complex shapes are a combination of simpler forms
#include "quad.h"                      //! Reducing high Dimensions to lower
#include "line.h"                      //! Further reduction
#include "point.h"                     //! Fundamental spatial description
#include "node.h"                      //! Node class for A* search
#include "apptimer.h"                  //! Interim function describing time before inclusion as Dimension

std::vector <Universe*> universe_list; //! Top of the tree, begin with Universe class

/*!
 * Application specific add-ins
 * Focusing on the biology to be mimicked. Which is how the original project  of NeuralMimicry
 * got its name.
 */
#include "cognitivenetwork.h"          //! This is where emergent properties can develop
#include "cognitiveinput.h"            //! Input to a cognitive network, either from outside or another cognitive network
#include "cognitiveoutput.h"           //! Output from a cognitive network, either to outside or another cognitive network
#include "orbital.h"                   //! Example of harmonic motion of particles
#include "neuron.h"                    //! Neuron container for other neuron components
#include "dendritecleft.h"             //! Dendritic synaptic cleft, input to the neuron
#include "neuroreceptor.h"             //! Neuroreceptor, component of dendritic cleft
#include "synapse.h"                   //! Synapse, area of stimulus transmission/reception
#include "interneuronspace.h"          //! The space between neurons is an energy pool
#include "membrane.h"                  //! Membrane, outer component of the neuron
#include "membranechannel.h"           //! Potassium or Sodium channel, component of the membrane
#include "dendrite.h"                  //! Dendrite, pre-Soma component of a neuron
#include "dendritebranch.h"            //! Dendrite branch, division/join of dendrites
#include "soma.h"                      //! Soma, component of a neuron
#include "axonhillock.h"               //! Axon Hillock, component of Soma
#include "axon.h"                      //! Axon, connected to Axon Hillock
#include "axonbranch.h"                //! Axon branch, division/join of Axon
#include "myelinsheath.h"              //! Myelin sheath, wraps around Axon
#include "schwanncell.h"               //! Schwann Cell, component of a Myelin sheath
#include "axonbouton.h"                //! Axon synaptic cleft, output area of neuron
#include "synapticvesicle.h"           //! Synaptic vesicle, container of neurotransmitters
#include "neurotransmitter.h"          //! Neurotransmitter, transfer component between clefts
#include "spike.h"                     //! Spikes

#ifndef DEBUG_PROGRAM
#define DEBUG_PROGRAM true
#endif //! DEBUG_PROGRAM

/*!
 * Socket definition was firstly to establish a communication path between independent cognitive networks.
 * The current steps are to scale first with Open MP for single node computation, then Open MPI for
 * same cluster communication. Then to expand to federated cognitive networks.
 * Sockets can also be used as a way to get input and output stimulus through the networks.
 */
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif //! INVALID_SOCKET

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif //! SOCKET_ERROR

#ifndef SOCKET_PORT
#define SOCKET_PORT 9876
#endif //! SOCKET_PORT

#ifndef SOCKET_ADDRESS
#define SOCKET_ADDRESS "192.168.42.56"    //! Change to the IP address of the computer running the middleware portion of the project. Potential to add auto-discovery here.
#endif //! SOCKET_ADDRESS

//! Handy conversions
#ifndef DEG2RAD
#define DEG2RAD 0.01745329252f  //! Avoids having to recalculate a constant PI/180 */
#endif //! DEG2RAD

#ifndef RAD2DEG
#define RAD2DEG 57.29577951f    //! Avoids having to recalculate a constant 180/PI */
#endif //! RAD2DEG

#ifndef ONERAD
#define ONERAD 3.14159265f    //! Avoids having to recalculate */
#endif //! ONERAD

#ifndef GRAVITY
#define GRAVITY 6.67384e-11;
#endif //! GRAVITY

struct caer_dynapse_info dynapse_info;

//! Dynap-se shutdown
static std::atomic_bool globalShutdown(false);

static void globalShutdownSignalHandler(int signal)
{
	//! Simply set the running flag to false on SIGTERM and SIGINT (CTRL+C) for global shutdown.
	if (signal == SIGTERM || signal == SIGINT)
	{
		globalShutdown.store(true);
	}
}


bool mshandling(std::vector <std::string> *m_messages, bool m_response, int m_ok, int m_fail)
{
	//! Provides configurable message display for completion of stages of operation
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

/*!  PLACEHOLDER for OpenMPI code (Shashi to integrate)
int openmpiInit(int argc, char *argv[])
{
    int rank, size, next, prev, message, tag = 201;

    //! Start up MPI

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //! Calculate the rank of the next process in the ring.  Use the
    //! modulus operator so that the last process "wraps around" to
    //! rank zero.

    next = (rank + 1) % size;
    prev = (rank + size - 1) % size;

    //! If we are the "master" process (i.e., MPI_COMM_WORLD rank 0),
    //! put the number of times to go around the ring in the
    //! message.

    if (0 == rank) {
        message = 10;

        printf("Process 0 sending %d to %d, tag %d (%d processes in ring)\n",
               message, next, tag, size);
        MPI_Send(&message, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        printf("Process 0 sent to %d\n", next);
    }

    //! Pass the message around the ring.  The exit mechanism works as
    //! follows: the message (a positive integer) is passed around the
    //! ring.  Each time it passes rank 0, it is decremented.  When
    //! each processes receives a message containing a 0 value, it
    //! passes the message on to the next process and then quits.  By
    //! passing the 0 message first, every process gets the 0 message
    //! and can quit normally.

    while (1) {
        MPI_Recv(&message, 1, MPI_INT, prev, tag, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        if (0 == rank) {
            --message;
            printf("Process 0 decremented value: %d\n", message);
        }

        MPI_Send(&message, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        if (0 == message) {
            printf("Process %d exiting\n", rank);
            break;
        }
    }

    //! The last process does one extra send to process 0, which needs
    //! to be received before the program can exit

    if (0 == rank) {
        MPI_Recv(&message, 1, MPI_INT, prev, tag, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    }

    //! All done

    MPI_Finalize();
    return 0;
}
 */

std::vector<Universe*> CreateUniverse(std::chrono::time_point<Clock> event_time, std::vector<Universe*> *toAddto)
{
	/*!
	 * Function to create a Universe instance. Universes could be simulation, emulation,
	 * real or contemplative (What-if)
	 */

	//! First, there is nothing. Then there was something...
	double UniverseEnergy = 999999999.0;        //! Defined energy level of Universe

	//! Begin with singularity
	Universe* myUniverse; //! Create instance of Universe from Universe class
	myUniverse = new Universe();

	/*!
	 * Set an energy level and attempt to maintain physics laws by keeping the total in the
	 * Universe the same. Uses the maximum value for double. Levels of abstraction used to
	 * cater for environment limitations
	 */
	myUniverse->SetEnergy(event_time, UniverseEnergy);
	myUniverse->Update(event_time); //! Cause initialisation

	//! Use copy otherwise data is destroyed on exiting function
	std::copy(&myUniverse, &myUniverse + 1, std::back_inserter(*toAddto));

	return *toAddto; //! Return with pointer to the expanded list of Universes.
}


bool CompareSwapElementaryParticle(std::chrono::time_point<Clock> event_time, std::vector<ElementaryParticle*>& origin, int l_origin_Swap, int l_origin_Candidate1, int l_origin_Candidate2)
{
	/*!
	 * Test which Candidate is closest to being 3 away in the charge values and move that
	 * Candidate next to the Origin.
	 */
	bool l_switch = true;
	int l_origin = origin[l_origin_Swap]->GetCharge(event_time);
	int l_origin_Test1 = origin[l_origin_Candidate1]->GetCharge(event_time);
	int l_origin_Test2 = origin[l_origin_Candidate2]->GetCharge(event_time);
	int l_origin_Test3 = std::abs(l_origin - l_origin_Test1);
	int l_origin_Test4 = std::abs(l_origin - l_origin_Test2);
	int l_origin_Test5 = (3.0 - l_origin_Test3);
	int l_origin_Test6 = (3.0 - l_origin_Test4);

	l_switch = false;

	if(l_origin_Test5 > l_origin_Test6 && l_origin != l_origin_Candidate2)
	{
		iter_swap(origin.begin() + l_origin_Candidate1, origin.begin() + l_origin_Candidate2);
		l_switch = true;
	}

	return l_switch; //! Return, answering whether or not an exchange occurred
}

int DistanceBetweenNodes(std::chrono::time_point<Clock> event_time, std::vector<Point> *nodesQuery, std::vector<int> *nodes_list, int nodesDimensions, double desired_distance )
{
	/*!
	 * Provide distance between two nodes.
	 * For optimisation, may be replaced with vtkMath::Distance2BetweenPoints(p0, p1) but adapted
	 * to multiple dimensions.
	 */
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

	for(unsigned int node_loop = 0; node_loop < nodes_list->size(); node_loop++ )
	{
		firstX = (*nodesQuery)[node_loop].GetPointPosition(event_time)[0];
		firstY = (*nodesQuery)[node_loop].GetPointPosition(event_time)[1];
		secondX = (*nodesQuery)[node_loop].GetPointPosition(event_time)[0];
		secondY = (*nodesQuery)[node_loop].GetPointPosition(event_time)[1];
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
			angleDEG = angleDEG + 90.0;
		}

		if(firstX > secondX && firstY > secondY)
		{
			angleDEG = angleDEG + 180.0;
		}

		if(firstX > secondX && firstY < secondY)
		{
			angleDEG = angleDEG + 270.0;
		}

		angleRAD = angleDEG * DEG2RAD;

		direction = actualDistance - desired_distance;

		if(direction > -1.0 and direction < 1.0)
		{
			//!        diffX = 0;
			//!        diffY = 0;

			/*
             if(desired_distance < actualDistance)
             {
             diffX = sin(angleRAD);
             diffY = cos(angleRAD);
             }

             if(desired_distance > actualDistance)
             {
             diffX = sin(angleRAD + ONERAD);
             diffY = cos(angleRAD + ONERAD);
             }
			 */
			diffX = actualDistance * cos(diffX / actualDistance);
			diffY = actualDistance * sin(diffY / actualDistance);



			/*
             if(desired_distance != 0)
             {
             if((actualDistance / desired_distance) > 0.95 && (actualDistance / desired_distance) < 1.05)
             {
             (*nodesQuery)[(*nodes_list)[0]]->SetPointDifferential(0);
             (*nodesQuery)[(*nodes_list)[0]]->SetPointMove(0);
             (*nodesQuery)[(*nodes_list)[1]]->SetPointDifferential(0);
             (*nodesQuery)[(*nodes_list)[1]]->SetPointMove(0);
			 */
			/*
             (*nodesQuery)[(*nodes_list)[2]]->SetPointDifferential(0);
             (*nodesQuery)[(*nodes_list)[2]]->SetPointMove(0);
             (*nodesQuery)[(*nodes_list)[3]]->SetPointDifferential(0);
             (*nodesQuery)[(*nodes_list)[3]]->SetPointMove(0);
			 */
			/*
             }
             else
             {
			 */
			for(int nloop = 0; nloop < int((*nodesQuery)[node_loop].GetPointDifferential(event_time).size()); nloop++)
			{
				//!        (*nodesQuery)[node_loop].SetPointDifferential((((*nodesQuery)[node_loop].GetPointDifferential()[nloop] + diffX)/2.0))[nloop];
				//!        (*nodesQuery)[node_loop].SetPointDifferential((((*nodesQuery)[node_loop].GetPointDifferential()[nloop] + diffY)/2.0))[nloop];
			}
			//!                (*nodesQuery)[(*nodes_list)[2]]->SetPointDifferential((((*nodesQuery)[(*nodes_list)[2]].getPointDifferential() - diffX)/2));
			//!                (*nodesQuery)[(*nodes_list)[3]]->SetPointDifferential((((*nodesQuery)[(*nodes_list)[3]].getPointDifferential() - diffY)/2));

			//!                }
			//!            }
		}
	}
	return EXIT_SUCCESS;
}

bool compare_swapSynapse(std::chrono::time_point<Clock> event_time, std::vector<Synapse*> origin, int l_origin_Swap, int l_origin_Candidate1, int l_origin_Candidate2)
{
	/*!
	 * Test which Candidate is closest to being 3 away in the charge values and move that
	 * Candidate next to the Origin.
	 */
	bool l_switch = true;
	int l_origin = origin[l_origin_Swap]->GetDemand(event_time);
	int l_origin_Test1 = origin[l_origin_Candidate1]->GetDemand(event_time);
	int l_origin_Test2 = origin[l_origin_Candidate2]->GetDemand(event_time);
	int l_origin_Test3 = std::abs(l_origin - l_origin_Test1);
	int l_origin_Test4 = std::abs(l_origin - l_origin_Test2);
	int l_origin_Test5 = (l_origin_Test3);
	int l_origin_Test6 = (l_origin_Test4);

	l_switch = false;

	if(l_origin_Test5 > l_origin_Test6 && l_origin != l_origin_Candidate2)
	{
		iter_swap(origin.begin() + l_origin_Candidate1, origin.begin() + l_origin_Candidate2);
		l_switch = true;
	}

	return l_switch; //! Return answering whether or not an exchange occurred
}


bool analyseStream(std::chrono::time_point<Clock> event_time, CognitiveNetwork* cognitive_network, std::vector<Neuron*> neuron_list, std::vector<Point*> aPoint, int start_point, int end_point, int stepPoint, int neural_sequence)
{
	/*!
	 * Provide an input stream of data to the Cognitive Network
	 */
	double feed;
	bool neuronStimulated = false;
	/*
     for(int analyse_loop = start_point; analyse_loop < end_point; analyse_loop = analyse_loop + stepPoint)
     {
     feed = aPoint[analyse_loop]->GetPointPosition(event_time);
     neuronStimulated = false;

     for(int gate_loop = 0; gate_loop < int(neuron_list.size()); gate_loop++)
     {
     if(int(neuron_list.size()) > 0)
     {
     if(neuron_list[gate_loop]->GetCounter(event_time) == neural_sequence)
     {
     if(neuron_list[gate_loop]->OpenGate(feed) == true)
     {
     neuronStimulated = true;
     for(int stimulate_loop = gate_loop + 1; stimulate_loop < gate_loop + 5; stimulate_loop++)
     {
     if(stimulate_loop < int(neuron_list.size()))
     {
     if(neuron_list[stimulate_loop]->GetCounter(event_time) == neural_sequence)
     {
     neuron_list[stimulate_loop]->OpenGate(feed);
     }
     }
     }
     }
     }
     }
     else
     {
     cognitive_network->AddNeuron(event_time, 1);
     cognitive_network->GetNeurons(event_time).back().setGateKeeper(feed);
     cognitive_network->GetNeurons(event_time).back().setChannelMin(feed - 1.0);
     cognitive_network->GetNeurons(event_time).back().setChannelMax(feed + 1.0);
     cognitive_network->GetNeurons(event_time).back().setCounter(neural_sequence);
     neuronStimulated = true;

     }
     }
     if(neuronStimulated == false)
     {
     cognitive_network->AddNeuron(event_time, 1);
     cognitive_network->GetNeurons(event_time).back().setGateKeeper(feed);
     cognitive_network->GetNeurons(event_time).back().setChannelMin(feed - 1.0);
     cognitive_network->GetNeurons(event_time).back().setChannelMax(feed + 1.0);
     cognitive_network->GetNeurons(event_time).back().setCounter(neural_sequence);
     }
     }
     for(int readoutLoop = 0; readoutLoop < int(neuron_list.size()); readoutLoop++)
     {
     if(neuron_list[readoutLoop]->GetCounter(event_time) == neural_sequence)
     {
     //!            std::cout << "Sequence: " << neural_sequence << " " << readoutLoop << ": Value: " << (*neuron_list)[readoutLoop].GetGateKeeper(event_time) << " Energy: " << (*neuron_list)[readoutLoop].getEnergy() << std::endl;
     }
     }
	 */
	return false;
}


void ClearDimensionSelection(std::vector<int> *dimension_list)
{
	/*!
	 * Empty the Dimensions list
	 */
	dimension_list->clear();
}

void SelectDimension(const int PossibleDimensions[10], std::vector<int> *dimension_list, int whichDimension)
{
	/*!
	 * BrainHarmonics can work beyond 2D or 3D space but the dimensions do need
	 * careful handling.
	 */
	int l_counter = 0;
	for(int nloop = 0; nloop < 10; nloop++)
	{
		for(int zloop = 0; zloop < PossibleDimensions[nloop]; zloop++)
		{
			l_counter++;
			if (zloop == whichDimension)
			{
				(*dimension_list).push_back(l_counter);
			}
		}
	}
}

void SelectMultiDimensions(const int PossibleDimensions[10], std::vector<int> *dimension_list, int how_manyDimensions)
{
	for(int nloop = 0; nloop < how_manyDimensions; nloop++)
	{
		SelectDimension(PossibleDimensions, &(*dimension_list), nloop);
	}
}


bool ClearDynapse(caerDeviceHandle *usb_handle)
{
	/*!
	 * This is accelerator specific to reset the Dynap-se. Accelerator configuration should
	 * move to a set of selectable modules to allow for different and multiple accelerators to
	 * be simultaneously configured.
	 */

	//! Let's take a look at the information we have on the device.
	dynapse_info = caerDynapseInfoGet(*usb_handle);

	printf("%s --- ID: %d, Master: %d,  Logic: %d.\n",
			dynapse_info.deviceString, dynapse_info.deviceID,
			dynapse_info.deviceIsMaster, dynapse_info.logicVersion);

	//! Let's turn on blocking data-get mode to avoid wasting resources.
	caerDeviceConfigSet(*usb_handle, CAER_HOST_CONFIG_DATAEXCHANGE, CAER_HOST_CONFIG_DATAEXCHANGE_BLOCKING, true);

	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_RUN, true);

	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_AER, DYNAPSE_CONFIG_AER_RUN, true);

	//! chip id is DYNAPSE_CONFIG_DYNAPSE_U2
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_MUX, DYNAPSE_CONFIG_MUX_FORCE_CHIP_BIAS_ENABLE, true);

	printf("Configuring silent biases...");
	std::ifstream input( DEFAULTBIASES);
	for (std::string line; getline(input, line);)
	{
		int i_dec = atoi(line.c_str());
		caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, i_dec);
	}
	input.close();
	printf(" Done.\n");

	printf("Configuring sram content...");
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_DEFAULT_SRAM, DYNAPSE_CONFIG_DYNAPSE_U2, 0);
	printf(" Done.\n");

	printf("Configuring cam content...");
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CLEAR_CAM, DYNAPSE_CONFIG_DYNAPSE_U2, 0);
	printf(" Done.\n");

	//! close config
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_RUN, false);

	//close aer communication
	caerDeviceConfigSet(*usb_handle, DYNAPSE_CONFIG_AER, DYNAPSE_CONFIG_AER_RUN, false);
	//caerDeviceDataStop(usb_handle);

	return true;
}

//! Clear memory to cleanly exit application
void exitCB()
{
	/*!
	 * First call to exit the program cleanly.
	 */

	#ifdef _WIN32
	std::cout << "Exiting Program. Press Any key to complete." << std::endl;
	/* A pause for Any key to be pressed, only needed for Windows to stop console window closing*/
	std::cin.get();
#endif

	//! Clear vectors in reverse order to free-up memory before exiting

	//! Remember to clear vectors / free memory before returning
}

int init(int argc, const char * argv[])
{
	srand (time(NULL));    //* Initialise random seed

	atexit(exitCB);        //* Set application exit callback

	return 0;        //* Return success
}

//! Macro required otherwise return value upsets calling function
#if PY_MAJOR_VERSION >= 3
int
#else
void
#endif
init_numpy()
{
	/*!
	 * Simple initialisation to ready Numpy for potential use within application
	 */
    import_array();
#if PY_MAJOR_VERSION >= 3
	return 0;
#endif
}

class UpdateAllCommand : public vtkCommand
{
	/*!
	 * Regularly called to provide calculation updates across all objects and then select
	 * a subset for display.
	 */
public:
	vtkTypeMacro(UpdateAllCommand, vtkCommand);

	static UpdateAllCommand *New()
	{
		UpdateAllCommand *update_all_callback = new UpdateAllCommand;
		update_all_callback->TimerCount = 0;
		return update_all_callback;
	}

	virtual void Execute(vtkObject * vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData))
	{
		if (vtkCommand::TimerEvent == eventId)
		{
			++this->TimerCount;
			std::cout << this->TimerCount << endl;

			int id_counter = 0;
			int cellarrays_group_counter = static_cellarrays_counter + 1;
			int polydata_group_counter = static_polydata_counter + 1;
			int surfaces_group_counter = static_surfaces_counter;
			int contourfilter_group_counter = static_contourfilter_counter;
			int reversals_group_counter = static_reversals_counter;
			int datamappers_group_counter = static_datamappers_counter;
			int actors_group_counter = static_actors_counter;
			int renderers_group_counter = static_renderers_counter + 1;
			auto event_time = std::chrono::high_resolution_clock::now();

			std::vector<Universe*> set_of_update_pointers;
			std::vector<Universe*>::iterator universe_iter;
			for(universe_iter = universe_list.begin(); universe_iter != universe_list.end(); ++universe_iter)
			{
				//! Call universe update
				//(*universe_iter)->Update(event_time);
				std::cout << ".";

				//! For each Universe locate solids for visualisation
				bool surfaces_found = false;
				bool solids_found = false;
				std::vector<Universe*> set_of_solid_pointers = (*universe_iter)->GetSolids(event_time);
				std::vector<Universe*>::iterator solid_iter;
				for(solid_iter = set_of_solid_pointers.begin(); solid_iter != set_of_solid_pointers.end(); ++solid_iter)
				{
					auto current_solid_pointer = dynamic_cast<Solid*>(*solid_iter);
					if(current_solid_pointer)
					{
						std::cout << "S";
						//! Each solid is made up of a set of polyhedrons
						id_counter = 0;
						//vtkSmartPointer<vtkPoints> solid_points = vtkSmartPointer<vtkPoints>::New();
						vtkSmartPointer<vtkAppendPolyData> append_polydata = vtkSmartPointer<vtkAppendPolyData>::New();
						bool polyhedrons_found = false;
						std::vector<Solid*> set_of_polyhedron_pointers = current_solid_pointer->GetPolyhedrons(event_time);
						std::vector<Solid*>::iterator polyhedron_iter;
						bool points_found = false;
						for(polyhedron_iter = set_of_polyhedron_pointers.begin(); polyhedron_iter != set_of_polyhedron_pointers.end(); ++polyhedron_iter)
						{
							auto current_polyhedron_pointer = dynamic_cast<Polyhedron*>(*polyhedron_iter);
							if(current_polyhedron_pointer)
							{
								//! Each polyhedron is made up of a set of points
								std::vector<Point*> set_of_point_pointers = current_polyhedron_pointer->GetPoints(event_time);
								std::vector<Point*>::iterator point_iter;
								int starting_point = id_counter;
								for(point_iter = set_of_point_pointers.begin(); point_iter != set_of_point_pointers.end(); ++point_iter)
								{
									auto current_point_pointer = dynamic_cast<Point*>(*point_iter);
									if(current_point_pointer)
									{
										std::vector<double> point_values = current_point_pointer->GetPointPosition(event_time);
										if(point_values.size() > 2)
										{
											define_points->InsertPoint(id_counter, point_values[0], point_values[1], point_values[2]);
											//solid_points->InsertPoint(id_counter, point_values[0], point_values[1], point_values[2]);
											id_counter++;
											points_found = true;
										}
									}
								}
								if(starting_point != id_counter)
								{
									vtkSmartPointer<vtkIdList> set_of_ids = vtkSmartPointer<vtkIdList>::New();
									for(int id_loop = starting_point; id_loop < id_counter; id_loop++)
									{
										set_of_ids->InsertNextId(id_loop);
									}
									define_cellarrays[cellarrays_group_counter]->InsertNextCell(set_of_ids);
								}
							}
						}
						if(points_found)
						{
							vtkSmartPointer<vtkPolyData> append_points = vtkSmartPointer<vtkPolyData>::New();
							append_points->SetPoints(define_points);
							append_points->SetVerts(define_cellarrays[cellarrays_group_counter]);
							std::cout << "Points: " << define_points->GetNumberOfPoints() << " Cells: " << define_cellarrays[cellarrays_group_counter]->GetNumberOfCells() << std::endl;
							append_polydata->AddInputData(append_points);
							polyhedrons_found = true;
							cellarrays_group_counter++;
							points_found = false;
						}

						if(polyhedrons_found)
						{
							append_polydata->Update();
							if(define_polydata.size() > polydata_group_counter)
							{
								define_polydata[polydata_group_counter] = vtkSmartPointer<vtkPolyData>::New();
							}
							else
							{
								define_polydata.push_back(vtkSmartPointer<vtkPolyData>::New());
								dynamic_polydata_counter = define_polydata.size();
							}

							define_polydata[polydata_group_counter] = append_polydata->GetOutput();

							if(define_surfaces.size() > surfaces_group_counter)
							{
								define_surfaces[surfaces_group_counter] = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
							}
							else
							{
								define_surfaces.push_back(vtkSmartPointer<vtkSurfaceReconstructionFilter>::New());
								dynamic_surfaces_counter = define_surfaces.size();
							}

							define_surfaces[surfaces_group_counter]->SetInputData(define_polydata[polydata_group_counter]);

							if(define_contourfilters.size() > contourfilter_group_counter)
							{
								define_contourfilters[contourfilter_group_counter] = vtkSmartPointer<vtkContourFilter>::New();
							}
							else
							{
								define_contourfilters.push_back(vtkSmartPointer<vtkContourFilter>::New());
								dynamic_contourfilter_counter = define_contourfilters.size();
							}

							define_contourfilters[contourfilter_group_counter]->SetInputConnection(define_surfaces[surfaces_group_counter]->GetOutputPort());
							define_contourfilters[contourfilter_group_counter]->SetValue(0, 0.0);

							//! Sometimes the contouring algorithm can create a volume whose gradient
							//! vector and ordering of polygon (using the right hand rule) are
							//! inconsistent. vtkReverseSense cures this problem.

							if(define_reversals.size() > reversals_group_counter)
							{
								define_reversals[reversals_group_counter] = vtkSmartPointer<vtkReverseSense>::New();
							}
							else
							{
								define_reversals.push_back(vtkSmartPointer<vtkReverseSense>::New());
								dynamic_reversals_counter = define_reversals.size();
							}

							define_reversals[reversals_group_counter]->SetInputConnection(define_contourfilters[contourfilter_group_counter]->GetOutputPort());
							define_reversals[reversals_group_counter]->ReverseCellsOn();
							define_reversals[reversals_group_counter]->ReverseNormalsOn();
							define_reversals[reversals_group_counter]->Update();
							solids_found = true;
							polyhedrons_found = false;
							define_polydata[polydata_group_counter] = vtkSmartPointer<vtkPolyData>::New();
							define_polydata[polydata_group_counter] = TransformBack(define_points, define_reversals[reversals_group_counter]->GetOutput());

							if(define_datamappers.size() > datamappers_group_counter)
							{
								define_datamappers[datamappers_group_counter] = vtkSmartPointer<vtkPolyDataMapper>::New();
							}
							else
							{
								define_datamappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
								dynamic_datamappers_counter = define_datamappers.size();
							}

							define_datamappers[datamappers_group_counter]->SetInputConnection(define_reversals[reversals_group_counter]->GetOutputPort());
							define_datamappers[datamappers_group_counter]->ScalarVisibilityOff();

							if(define_actors.size() > actors_group_counter)
							{
								define_actors[actors_group_counter] = vtkSmartPointer<vtkActor>::New();
							}
							else
							{
								define_actors.push_back(vtkSmartPointer<vtkActor>::New());
								dynamic_actors_counter = define_actors.size();
							}

							define_actors[actors_group_counter]->SetMapper(define_datamappers[datamappers_group_counter]);
							define_actors[actors_group_counter]->GetProperty()->SetDiffuseColor(1.0000, 0.3882, 0.2784);
							define_actors[actors_group_counter]->GetProperty()->SetSpecularColor(1, 1, 1);
							define_actors[actors_group_counter]->GetProperty()->SetSpecular(.4);
							define_actors[actors_group_counter]->GetProperty()->SetSpecularPower(50);

							//! Add the actors to the renderer
							if(define_renderers.size() > renderers_group_counter)
							{
								define_renderers[renderers_group_counter]->AddActor(define_actors[actors_group_counter]);
							}
							else
							{
								define_renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
								dynamic_renderers_counter = define_renderers.size();
								define_renderers[renderers_group_counter]->SetBackground(1, 1, 1);
								define_renderers[renderers_group_counter]->GetActiveCamera()->SetFocalPoint(0, 0, 0);
								define_renderers[renderers_group_counter]->GetActiveCamera()->SetPosition(1, 0, 0);
								define_renderers[renderers_group_counter]->GetActiveCamera()->SetViewUp(0, 0, 1);
								define_renderers[renderers_group_counter]->ResetCamera();
								define_renderers[renderers_group_counter]->GetActiveCamera()->Azimuth(20);
								define_renderers[renderers_group_counter]->GetActiveCamera()->Elevation(30);
								define_renderers[renderers_group_counter]->GetActiveCamera()->Dolly(1.2);
								define_renderers[renderers_group_counter]->ResetCameraClippingRange();
								define_renderers[renderers_group_counter]->ResetCamera();
								define_renderers[renderers_group_counter]->AddActor(define_actors[actors_group_counter]);
							}

							polydata_group_counter++;
							surfaces_group_counter++;
							contourfilter_group_counter++;
							reversals_group_counter++;
							datamappers_group_counter++;
							actors_group_counter++;
							surfaces_found = true;
							surfaces_group_counter++;
							solids_found = false;
						}
					}
				}
			}
			render_window->Render();
		}
	}
private:
	int TimerCount;
};

int main(int argc, const char * argv[])
{
	/*! This application is designed to create an AARNN Cognitive AI network constructed using
	 *  either simulated neurons or emulated neuromorphic chipsets
	 */

	int initialiseProgram = init(argc, argv);
	if (initialiseProgram)
	{
		std::cout << "Program initialisation failed!" << std::endl;
		return EXIT_FAILURE;
	}

	/*! Initialise hardware if located. Additional coding is required to enable hot-pluggable
	 * and failed accelerator. Extension needs to account for multiple accelerators rather than
	 * simply a bool answer.
	 */

	bool device_attached = true;  //! Bool flag is set to false when communication fails to discover hardware


	//! Install Dynap-se signal handler for global shutdown.
#if defined(_WIN32)
	if (signal(SIGTERM, &globalShutdownSignalHandler) == SIG_ERR)
	{
		caerLog(CAER_LOG_CRITICAL, "ShutdownAction", "Failed to set signal handler for SIGTERM. Error: %d.", errno);
		return (EXIT_FAILURE);
	}

	if (signal(SIGINT, &globalShutdownSignalHandler) == SIG_ERR)
	{
		caerLog(CAER_LOG_CRITICAL, "ShutdownAction", "Failed to set signal handler for SIGINT. Error: %d.", errno);
		return (EXIT_FAILURE);
	}
#else
	struct sigaction shutdownAction;

	shutdownAction.sa_handler = &globalShutdownSignalHandler;
	shutdownAction.sa_flags = 0;
	sigemptyset(&shutdownAction.sa_mask);
	sigaddset(&shutdownAction.sa_mask, SIGTERM);
	sigaddset(&shutdownAction.sa_mask, SIGINT);

	if (sigaction(SIGTERM, &shutdownAction, NULL) == -1)
	{
		caerLog(CAER_LOG_CRITICAL, "ShutdownAction", "Failed to set signal handler for SIGTERM. Error: %d.", errno);
		return (EXIT_FAILURE);
	}

	if (sigaction(SIGINT, &shutdownAction, NULL) == -1)
	{
		caerLog(CAER_LOG_CRITICAL, "ShutdownAction", "Failed to set signal handler for SIGINT. Error: %d.", errno);
		return (EXIT_FAILURE);
	}
#endif

	//! Verify connection to all Dynap-se boards/chips and then ensure the chips are set to a basic known configuration.

	//! Open the communication with Dynap-se, give it a device ID of 1, and don't care about USB bus or SN restrictions.

	caerDeviceHandle usb_handle = caerDeviceOpen(1, CAER_DEVICE_DYNAPSE, 0, 0, NULL);

	if (usb_handle == NULL)
	{
		printf("No devices attached. Using simulation system only.\n");
		device_attached = false;
		//!        return (EXIT_FAILURE);  //! Not required because this program can run without dedicated hardware.
	}

	if(device_attached)
	{
		//! Verify or amend code to ensure all chips are reset at the beginning
		ClearDynapse(&usb_handle);
		caerDeviceClose(&usb_handle);

		//! Now re-open the communication with Dynap-se for a clean connection.
		usb_handle = caerDeviceOpen(1, CAER_DEVICE_DYNAPSE, 0, 0, NULL);

		if (usb_handle == NULL)
		{
			printf("Device communication failed.\n");
			device_attached = false;
			//!        return (EXIT_FAILURE);
		}
	}

	//! End of initial hardware detection. Further communications errors will disable hardware use

	//! Define bit-setting variables for hardware
	uint32_t genBits = 0;
	uint8_t dynap_Dx = 0;
	uint8_t dynap_Sx = 0;
	uint8_t dynap_Dy = 0;
	uint8_t dynap_Sy = 0;
	uint16_t destinationCoreId;
	std::string::size_type sz;

	//! Index arrays for instances of classes described above
	//! Early versions of this software maintained direct pointers to all objects. Now it is recoded
	//! to access through Get/Set class methods with the exception of the initial Universe class.
	std::vector <Dimension*>          dimension_list;          //! Add Dimensions for spatial identification     */
	std::vector <ElementaryParticle*> elementary_particle_list; //! Follow with the creation of quarks/leptons    */
	std::vector <ElementaryForce*>    elementary_force_list;    //! Define Force interaction between fundamentals */
	std::vector <CompositeForceParticle*>     composite_forceparticle_list;     //! Define Particle Force interaction between Composites, Protons/Neutrons   */
	std::vector <Law*>                law_list;                //! Specify how Composites interact               */
	std::vector <Matter*>             matter_list;             //! Composites form elements of periodic table    */
	std::vector <Monomer*>            monomer_list;            //! Composites form molecules                     */
	std::vector <Polymer*>            polymer_list;            //! Composites form complex molecules             */
	std::vector <Solid*>              solid_list;              //! Materials are a combination of Matter         */
	std::vector <Polyhedron*>         polyhedron_list;         //! Materials can be formed into multiDimensional shapes */
	std::vector <Polygon*>            polygon_list;            //! Complex shapes are a combination of simpler forms */
	std::vector <Quad*>               quad_list;               //! Reducing high Dimensions to lower             */
	std::vector <Line*>               line_list;               //! Further reduction                             */
	std::vector <Point*>              point_list;              //! Fundamental spatial description               */
	//!    std::vector <Node>               Node;               //! Node class for A* search                      */
	std::vector <AppTimer*>           Apptimer;           //! Interim function describing time before inclusion as Dimension */

	//! Higher level of abstraction. Initial naming. Ideally use Get/Set methods rather than store pointers here.
	std::vector <CognitiveNetwork*> cognitivenetwork;  //! Network container for all AI components       */
	std::vector <Orbital*> orbital;                    //! Example of orbital timing containing neurons  */
	std::vector <Neuron*> neuron;                      //! Neuron container for other neuron components  */
	std::vector <DendriteCleft*> dendritecleft;        //! Dendritic synaptic cleft, input to the neuron */
	std::vector <Neuroreceptor*> neuroreceptor;        //! Neuroreceptor, component of dendritic cleft   */
	std::vector <Synapse*> synapse;                    //! Synapse, area of stimulus transmission/reception */
	std::vector <InterneuronSpace*> interneuronspace;  //! Between neurons is an energy pool */
	std::vector <Membrane*> membrane;                  //! Membrane, outer component of the neuron       */
	std::vector <MembraneChannel*> membranechannel;    //! Potassium/Sodium channel, component of the membrane  */
	std::vector <Dendrite*>  dendrite;                 //! Dendrite, pre-Soma component of a neuron      */
	std::vector <DendriteBranch*> dendritebranch;      //! Dendrite branch, division/join of dendrites   */
	std::vector <Soma*> soma;                          //! Soma, component of a neuron                   */
	std::vector <AxonHillock*> AxonHillock;            //! Axon Hillock, component of Soma               */
	std::vector <Axon*> axon;                          //! Axon, connected to Axon Hillock               */
	std::vector <AxonBranch*> axonbranch;              //! Axon branch, division/join of Axon            */
	std::vector <MyelinSheath*> myelinsheath;          //! Myelin sheath, wraps around Axon              */
	std::vector <SchwannCell*> schwanncell;            //! Schwann Cell, component of a Myelin sheath    */
	std::vector <AxonBouton*> axonbouton;                //! Axon synaptic cleft, output area of neuron    */
	std::vector <SynapticVesicle*> synapticvesicle;    //! Synaptic vesicle, container of neurotransmitters */
	std::vector <Neurotransmitter*> neurotransmitter;  //! Neurotransmitter, transfer component between clefts */
	std::vector <Spike*> Spike;                        //! Spike */

	const int infinite_loop_prevention_threshold = 800;

	//CCP Abstraction
	std::vector <int> nodeList;

	std::vector <int> selectedDimensions;

	//! The initial parameters are to be read from an XML Parameter file but for now are hard-coded.

	const int num_universes = 10;     //! Internal display, Physical material and spatial references
	std::vector <int> num_dimensions_in_universe = {3, 1, 4, 2, 2, 3, 3, 3, 3, 1};
	//! U1 = Internal Time, X, Y & Z
	//! U2 = Physical
	//! U3 = Spatial X,Y,Z & Time
	//! U4 = CPP
	//! U5 = Spikes
	//! U6 = Neurotransmitters
	//! U7 = Connectome
	//! U8 = Synapses
	//! U9 = Orbital example

	//! Initial number of starting components for each subproject

	/*! The Physics problem.
	 *  Periodic checking of elemental forces helps to align the emulated environment beyond
	 *  a simple simulation.
	 */
	std::vector <int> num_elementary_particles_in_universe = {0, 10, 0, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_elementary_forces_in_universe = {0, 10, 0, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_composite_forceparticles_in_universe;

	for(int build_outer_composite_loop = 0; build_outer_composite_loop < num_elementary_particles_in_universe.size(); build_outer_composite_loop++)
	{
		for(int build_inner_composite_loop = 0; build_inner_composite_loop < num_elementary_forces_in_universe.size(); build_inner_composite_loop++)
		{
			num_composite_forceparticles_in_universe.push_back(num_elementary_particles_in_universe[build_outer_composite_loop] * num_elementary_forces_in_universe[build_inner_composite_loop]);
		}
	}

	//! Attempt to stimulate particle bonding by moving attracted objects nearer to each other.
	const int initial_particle_alignment = 20;


	/*! The Cognitive problem.
	 *  Support objects such that the interaction enables emergent properties. This is the
	 *  fundamental core of AARNN.
	 *  Cognitive objects are made up of orbital stimuli that in turn are made up of neurons.
	 */
	std::vector <int> num_cognitive_networks_in_universe = { 0, 0, 5, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_orbitals_in_cognitive_network = {0, 0, 100, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_neurons_in_cognitive_network = {0, 0, 500, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_synapses_in_cognitive_network = {0, 0, 2000, 0, 0, 0, 0, 0, 0, 0};

	std::vector <int> num_neurotransmitters_in_cognitive_network = {0, 0, 2000, 0, 0, 0, 0, 0, 0, 0};

	//! Attempt to stimulate neuron pairing by moving attracted objects nearer to each other.
	const int initial_synapse_alignment = 20;

	const int num_layers_in_cognitive_network = 6;

	std::vector<int> orbital_layers;
	orbital_layers.clear();

	//! The setup of neurons, orbitals and cognitive networks are initial. Changes to configuration occurs dynamically depending on stimulation.
	for (int build_outer_loop = 0; build_outer_loop < num_cognitive_networks_in_universe.size(); build_outer_loop++)
	{
		for (int build_inner_loop = 0; build_inner_loop < num_layers_in_cognitive_network; build_inner_loop++)
		{
			//! How many neuron groups in each layer. May want to add some random variation in layer values.
			orbital_layers.push_back((num_orbitals_in_cognitive_network[build_outer_loop] / num_layers_in_cognitive_network) * build_inner_loop);
		}
		//! Ensure the end value is also added.
		orbital_layers.push_back(num_orbitals_in_cognitive_network[build_outer_loop] + 1);
	}

	//! Brain calculations
	const int initial_axon_branches = 4;
	const int initial_dendrites = 64;

	double compareFirst;
	double compareSecond;

	int status_of_call_request;
	bool patternFound = false;

	double l_screenX = 1000.0;            //! Define graphics window size, X axis*/
	double l_screenY = 800.0;            //! Define graphics window size, Y axis*/
	//double l_scale = 300;               //! Vertices are multiplied by this factor to enable fitting within the graphics window. Adjust to suit environment */
	std::string l_screenTitle = "Developed from Project NeuralMimicry - the basis of an AARNN Cognitive AI System";
	std::stringstream l_displayString;

	int counter_Charge = -1; //! Used to loop between min 0 and max 6
	int counter_Spin = 0;
	int counter_Walk = 0;
	int counter_infinite_loop_prevention = 0;

	int l_spaPointBase = 0; //! Base of data points (Moves because of use by internal graphics for points control too
	int how_many_particles = 0;
	int how_many_Synapses = 0;
	int how_many_Neurons = 0;
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

	std::vector<double> distance_to_move;
	double radialDistance;
	double s;
	double t;
	std::vector<double> point_origin;
	double xd;
	double yd;
	double zd;
	double pointDistance;
	double pointDistance2;
	double effect;
	double calcX;
	double calcY;
	double calcZ;
	double calcXoffset;
	double calcYoffset;
	double calcZoffset;
	double calcXscale;
	double calcYscale;
	double calcZscale;
	double colourMax;
	int colourY;

	std::vector<std::string> l_inputData;

	char * l_dir = getcwd(NULL, 0);
	l_inputData.clear();
	int numSynapses;
	//int initial_neurons;
	int paramCounter;
	std::string entry;
	std::string buf;
	std::istringstream iss("");
	//!    std::string::size_type sz;   //! alias of size_t
	int l_tabCycle = 0;

	double l_synapseX = 0.0;
	double l_synapseY = 0.0;
	double l_neuronX = 0.0;
	double l_neuronY = 0.0;
	double l_desired_distance = 0.0;
	double l_demandCounter = 0.0;
	double l_direction = 1.0;
	double l_diffX = 0.0;
	double l_diffX2 = 0.0;
	double l_diffY = 0.0;
	double l_diffY2 = 0.0;
	double l_slope = 0.0;
	double l_angleRAD = 0.0;
	double l_angleDEG = 0.0;
	double l_actualDistance = 0.0;
	double l_minimumDistance = 0.1f;
	std::vector <double> l_transferArray;
	int NumRows = 0;
	int NumInputs = 0;

	std::chrono::time_point<Clock> event_time;
	std::chrono::time_point<Clock> clockTime;
	std::chrono::time_point<Clock> lastClockTime;
	std::chrono::time_point<Clock> startTime;

	double counter_gravitation = 0.0;
	double counter_weak = 0.0;
	double counter_weak_electroweak = 0.0;
	double counter_electromagnetic = 0.0;
	double counter_electromagnetic_electroweak = 0.0;
	double counter_strong = 0.0;
	double counter_stronfundamental = 0.0;
	double counter_stronresidual = 0.0;

	setenv("PYTHONPATH", ".", 0); //! Setup the Python environment for integrating K-means clustering solution or other frameworks

	int pyArgc = 4;
	//!    const char pyArgv[] = { ' ','b','h','c','o','m','p','u','t','e',' ','m','u','l','t','i','p','l','y',' ','3',' ','4','\0'}

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	PyObject *pArrayArgs;
	int *pTransferArray;

	//!    int i;

	int result = EXIT_FAILURE;

	Py_Initialize();
	if(!Py_IsInitialized())
	{
		fprintf(stderr, "Python failed to initialise.\n");
		return EXIT_FAILURE;
	}

	if(PyArray_API == NULL)
	{
		init_numpy(); //! Numpy array initialisation
	}

	pName = PyUnicode_FromString("bhcompute");    //! File to be called. Must be in the same folder as the C++ executable and with a .py extension
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, "multiply");
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

	//! Prepare screens for visualisation

	//! VTK Screens

	//! Setup rectangle points for drawing screen

	double lower_left_x = 900.0;
	double lower_right_x = 1000.0;
	double upper_right_x = 1000.0;
	double upper_left_x = 900.0;

	double lower_left_y = 0.0;
	double lower_right_y = 0.0;
	double upper_right_y = 0.0;
	double upper_left_y = 0.0;

	define_cellarrays.push_back(vtkSmartPointer<vtkCellArray>::New());
	static_cellarrays_counter = 0;

	for(unsigned int insert_rectangle_loop = 0; insert_rectangle_loop < 8; insert_rectangle_loop++)
	{
		lower_left_y = ((((double(insert_rectangle_loop) - 1) / 2) + 1) * 25.0);
		lower_right_y = lower_left_y;
		upper_left_y = ((((double(insert_rectangle_loop) - 1) / 2) + 1) * 25.0) + 50.0;
		upper_right_y = upper_left_y;

		define_points->InsertNextPoint(lower_left_x, lower_left_y, 0.0);
		define_points->InsertNextPoint(lower_right_x, lower_right_y, 0.0);
		define_points->InsertNextPoint(upper_right_x, upper_right_y, 0.0);
		define_points->InsertNextPoint(upper_left_x, upper_left_y, 0.0);
		static_points_counter+=4;

		//! Create the polygon that defines a rectangle from the points added.
		vtkSmartPointer<vtkPolygon> define_polygon = vtkSmartPointer<vtkPolygon>::New();
		define_polygon->GetPointIds()->SetNumberOfIds(4);
		define_polygon->GetPointIds()->SetId(0, (0 + (insert_rectangle_loop * 4)));
		define_polygon->GetPointIds()->SetId(1, (1 + (insert_rectangle_loop * 4)));
		define_polygon->GetPointIds()->SetId(2, (2 + (insert_rectangle_loop * 4)));
		define_polygon->GetPointIds()->SetId(3, (3 + (insert_rectangle_loop * 4)));
		static_polygons_counter++;

		//! Add the polygon to a cell array
		define_cellarrays[static_cellarrays_counter]->InsertNextCell(define_polygon);
	}

	lower_left_y = 0.0;
	lower_right_y = 0.0;
	upper_right_y = 200.0;
	upper_left_y = 200.0;

	unsigned int current_num_of_defined_points = define_points->GetNumberOfPoints();

	define_points->InsertNextPoint(lower_left_x, lower_left_y, 0.0);
	define_points->InsertNextPoint(lower_right_x, lower_right_y, 0.0);
	define_points->InsertNextPoint(upper_right_x, upper_right_y, 0.0);
	define_points->InsertNextPoint(upper_left_x, upper_left_y, 0.0);
	static_points_counter+=4;

	vtkSmartPointer<vtkPolygon> define_polygon = vtkSmartPointer<vtkPolygon>::New();
	define_polygon->GetPointIds()->SetNumberOfIds(4);
	define_polygon->GetPointIds()->SetId(0, (0 + current_num_of_defined_points));
	define_polygon->GetPointIds()->SetId(1, (1 + current_num_of_defined_points));
	define_polygon->GetPointIds()->SetId(2, (2 + current_num_of_defined_points));
	define_polygon->GetPointIds()->SetId(3, (3 + current_num_of_defined_points));
	static_polygons_counter++;

	//! Add the polygon to a cell array
	define_cellarrays[static_cellarrays_counter]->InsertNextCell(define_polygon);

	//! Test for correct polygon insertion
	vtkIdType num_cells = define_cellarrays[static_cellarrays_counter]->GetNumberOfCells();
	vtkIdType cell_location = 0; //! the index inside the cell array

	for (vtkIdType cellarray_loop = 0; cellarray_loop < num_cells; cellarray_loop++)
	{
		vtkIdType num_ids;
		vtkIdType *point_ids;
		//define_cellarrays[static_cellarrays_counter]->GetCell(cell_location, num_ids, point_ids);
		cell_location += 1 + num_ids;
	}

	std::cout << "Test cell: " << cell_location << "  Actual cells: " << num_cells << std::endl;

	//! Assign Colour
	unsigned char red[3] = {255, 0, 0};
	unsigned char green[3] = {0, 255, 0};
	unsigned char blue[3] = {0, 0, 255};

	vtkSmartPointer<vtkUnsignedCharArray> colours = vtkSmartPointer<vtkUnsignedCharArray>::New();
	colours->SetNumberOfComponents(3);
	colours->SetName("Colors");
	for(unsigned int colour_loop = 0; colour_loop < define_points->GetNumberOfPoints(); colour_loop++)
	{
		colours->InsertNextTypedTuple(red);
	}

	//! Create PolyData
	if(define_polydata.size() > static_polydata_counter)
	{
		define_polydata[static_polydata_counter]->Initialize();
	}
	else
	{
		define_polydata.push_back(vtkSmartPointer<vtkPolyData>::New());
		define_polydata[static_polydata_counter]->Initialize();
	}
	define_polydata[static_polydata_counter]->SetPoints(define_points);
	define_polydata[static_polydata_counter]->SetLines(define_cellarrays[static_cellarrays_counter]);
	define_polydata[static_polydata_counter]->Modified();

	vtkSmartPointer<vtkCoordinate> coordinate_system = vtkCoordinate::New();
	coordinate_system->SetCoordinateSystemToDisplay();

	//! Setup the text and add it to the renderer
	//! Build display text
	vtkSmartPointer<vtkTextActor> text_actor;

	std::string textOptions[11][11];

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput ( "Initialising..." );
	text_actor->SetDisplayPosition( 400, 0 );
	text_actor->GetTextProperty()->SetFontSize ( 24 );
	text_actor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
	define_textactors.push_back(text_actor);

	textOptions[1][0] = "Read Only";
	textOptions[1][1] = "Read Write";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[1][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[2][0] = "Level";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[2][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[3][0] = "TOP";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[3][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[4][0] = "< ^ v >";
	textOptions[4][1] = "<      ";
	textOptions[4][2] = "  ^    ";
	textOptions[4][3] = "    v  ";
	textOptions[4][4] = "      >";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[4][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[5][0] = "Quantity";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[5][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[6][0] = "0000";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[6][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[7][0] = "Patterns";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[7][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[8][0] = "0000";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[8][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[9][0] = "ZOOM";
	textOptions[9][1] = "PAN";
	textOptions[9][2] = "ROTATE";
	textOptions[9][3] = "MOVE";
	textOptions[9][4] = "CHOOSE";
	textOptions[9][5] = "MODIFY";
	textOptions[9][6] = "TIME";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[9][0].c_str() );
	define_textactors.push_back(text_actor);

	textOptions[10][0] = "0000";

	text_actor = vtkSmartPointer<vtkTextActor>::New();
	text_actor->SetInput( textOptions[10][0].c_str() );
	define_textactors.push_back(text_actor);

	for (unsigned int text_loop = 1; text_loop < define_textactors.size(); text_loop++)
	{
		define_textactors[text_loop]->SetDisplayPosition(900.0, (((double(text_loop) - 1)/2)+1) * 25.0);
		define_textactors[text_loop]->GetTextProperty()->SetFontSize ( 12 );
		define_textactors[text_loop]->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
	}

	//! Create polydata mapper and actor
	if(define_datamappers2D.size() > static_datamappers2D_counter)
	{
		define_datamappers2D[static_datamappers2D_counter] = vtkSmartPointer<vtkPolyDataMapper2D>::New();
	}
	else
	{
		define_datamappers2D.push_back(vtkSmartPointer<vtkPolyDataMapper2D>::New());
	}
	define_datamappers2D[static_datamappers2D_counter]->SetInputData(define_polydata[static_polydata_counter]);
	define_datamappers2D[static_datamappers2D_counter]->SetTransformCoordinate(coordinate_system);
	define_datamappers2D[static_datamappers2D_counter]->ScalarVisibilityOn();
	define_datamappers2D[static_datamappers2D_counter]->SetScalarModeToUsePointData();
	define_datamappers2D[static_datamappers2D_counter]->Update();

	if(define_actors2D.size() > static_actors2D_counter)
	{
		define_actors2D[static_actors2D_counter] = vtkSmartPointer<vtkActor2D>::New();
	}
	else
	{
		define_actors2D.push_back(vtkSmartPointer<vtkActor2D>::New());
	}
	define_actors2D[static_actors2D_counter]->SetMapper(define_datamappers2D[static_datamappers2D_counter]);
	define_actors2D[static_actors2D_counter]->GetProperty()->SetLineWidth(2);

	//! Create a renderer
	if(define_renderers.size() > static_renderers_counter)
	{
		define_renderers[static_renderers_counter] = vtkSmartPointer<vtkRenderer>::New();
	}
	else
	{
		define_renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
	}

	define_renderers[static_renderers_counter]->SetBackground ( 0, 0, 0 ); //! Set background colour to white

	//! Add the VTK actors to the scene
	define_renderers[static_renderers_counter]->AddActor2D(define_actors2D[static_actors2D_counter]);
	define_actors2D[static_actors2D_counter]->GetProperty()->SetColor(0,1,0);
	define_actors2D[static_actors2D_counter]->GetProperty()->SetPointSize(2);
	for(unsigned int i = 0; i < define_textactors.size(); i++)
	{
		define_renderers[static_renderers_counter]->AddActor2D(define_textactors[i]);
	}

	//! Create a render window
	render_window = vtkSmartPointer<vtkRenderWindow>::New();
	render_window->AddRenderer ( define_renderers[static_renderers_counter] );
	render_window->SetSize(l_screenX, l_screenY);

	//! Create an interactor
	render_window_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//! render_window_interactor->SetRenderWindow ( render_window );

	//! Set-up the simulation environment. Currently a skeletal environment.
	std::cout << "Brain Harmonics - Using neuron concepts to solve problems" << std::endl << std::endl;
	std::cout << "First we need to create the environment:" << std::endl << std::endl;
	std::cout << "The Big Bang..." << std::endl;

	//! Synchronise events
	event_time = std::chrono::high_resolution_clock::now();

	//! universe_list is a vector of pointers to the Universe objects.
	//! Typically use one Universe per experiment.

	universe_list.clear();    //! Ensure vector is empty

	for (int universe_loop = 0; universe_loop <= num_universes - 1 ; universe_loop++)
	{
		//! Pass the universe_list address to the create function to keep all Universes within the same vector
		status_of_call_request = CreateUniverse(event_time, &universe_list).size();

		if (status_of_call_request == 0)
		{
			std::cout << "Universe creation failed!" << std::endl;
			return EXIT_FAILURE;
		}

		std::cout << "No.:" << universe_list.size() << " universe address created." << std::endl;

		std::cout << num_dimensions_in_universe[universe_loop] << " dimensions addresses to create." << std::endl;

		//! Cycle through Universes allocating n Dimensions and updating total with reported back size.
		num_dimensions_in_universe[universe_loop] = (universe_list[universe_loop]->AddDimensions(event_time, num_dimensions_in_universe[universe_loop])).size();

		std::cout << num_dimensions_in_universe[universe_loop] << " dimension addresses available in Universe: " << universe_loop << std::endl;

		//! Create new Elementary Particles - Quarks etc
		std::cout << num_elementary_particles_in_universe[universe_loop] << " elementary particle addresses to create." << std::endl;

		//! Cycle through Universes allocating n Elementary Particles and updating total with reported back size.
		num_elementary_particles_in_universe[universe_loop] = (universe_list[universe_loop]->AddElementaryParticles(event_time, num_elementary_particles_in_universe[universe_loop])).size();

		std::cout << num_elementary_particles_in_universe[universe_loop] << " elementary particle addresses available." << std::endl;

		counter_Charge = 0;

		for (int particle_loop = 0; particle_loop < num_elementary_particles_in_universe[universe_loop]; particle_loop++)
		{
			counter_Charge++;
			if(counter_Charge > 6) counter_Charge = 0;
			counter_Spin = int(1 - counter_Spin);
			//! Try to ensure we get variations of particles. Not all one type by changing Charge and Spin.
			(universe_list[universe_loop]->GetElementaryParticles(event_time))[particle_loop]->SetCharge(event_time, counter_Charge);
			(universe_list[universe_loop]->GetElementaryParticles(event_time))[particle_loop]->SetSpin(event_time, counter_Spin);
		}

		//! Create new Elementary Forces
		std::cout << num_elementary_forces_in_universe[universe_loop] << " elementary force addresses to create." << std::endl;

		//! Cycle through Universes allocating n Elementary Forces and updating total with reported back size.
		num_elementary_forces_in_universe[universe_loop] = (universe_list[universe_loop]->AddElementaryForces(event_time, num_elementary_forces_in_universe[universe_loop])).size();

		std::cout << num_elementary_forces_in_universe[universe_loop] << " elementary force addresses available." << std::endl;

		counter_gravitation = 0;
		counter_weak = 0;
		counter_weak_electroweak = 0;
		counter_electromagnetic = 0;
		counter_electromagnetic_electroweak = 0;
		counter_strong = 0;
		counter_stronfundamental = 0;
		counter_stronresidual = 0;

		for (int force_loop = 0; force_loop < num_elementary_forces_in_universe[universe_loop]; force_loop++)
		{
			counter_gravitation += 1;
			if(counter_gravitation > 3)
			{
				counter_gravitation = 0;
				counter_weak += 1;
			}
			if(counter_weak > 2)
			{
				counter_weak = 0;
				counter_weak_electroweak += 1;
			}
			if(counter_weak_electroweak > 4)
			{
				counter_weak_electroweak = 0;
				counter_electromagnetic += 1;
			}
			if(counter_electromagnetic > 6)
			{
				counter_electromagnetic = 0;
				counter_electromagnetic_electroweak += 1;
			}
			if(counter_electromagnetic_electroweak > 3)
			{
				counter_electromagnetic_electroweak = 0;
				counter_strong += 1;
			}
			if(counter_strong > 3)
			{
				counter_strong = 0;
				counter_stronfundamental += 1;
			}
			if(counter_stronfundamental > 7)
			{
				counter_stronfundamental = 0;
				counter_stronresidual += 0;
			}
			if(counter_stronresidual >3)
			{
				counter_stronresidual = 0;
			}
			//! Try to ensure we get variations of forces. Not all one type by changing parameters.
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetGravitation(event_time, counter_gravitation);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetWeak(event_time, counter_weak);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetWeakElectroweak(event_time, counter_weak_electroweak);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetElectromagnetic(event_time, counter_electromagnetic);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetElectromagneticElectroweak(event_time, counter_electromagnetic_electroweak);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetStrong(event_time, counter_strong);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetStrongFundamental(event_time, counter_stronfundamental);
			(universe_list[universe_loop]->GetElementaryForces(event_time))[force_loop]->SetStrongResidual(event_time, counter_stronresidual);
		}

		//! Create new Composite Force Particles - Protons / Neutrons
		std::cout << num_composite_forceparticles_in_universe[universe_loop] << " composite force particle addresses to create." << std::endl;

		//! Cycle through Universes allocating n Composite Force Particles and updating total with reported back size.
		num_composite_forceparticles_in_universe[universe_loop] = (universe_list[universe_loop]->AddCompositeForceParticles(event_time, num_composite_forceparticles_in_universe[universe_loop])).size();

		std::cout << num_composite_forceparticles_in_universe[universe_loop] << " composite force particle addresses available." << std::endl;

		how_many_particles = int(universe_list[universe_loop]->GetElementaryParticles(event_time).size());

		/*
         //! Rearrange vector of new Particles in an order closer to how they're likely to interact.
         for (int qloop = 0; qloop <= initial_particle_alignment * how_many_particles; qloop++)
         {
         counter_Walk = 0;
         current_Distance = 0;
         counter_infinite_loop_prevention = 0;

         do {
         counter_infinite_loop_prevention++;
         max_Distance = current_Distance;
         current_Distance = 0;
         while(counter_Walk <= (how_many_particles - 3))
         {
         l_switch = CompareSwapElementaryParticle(universe_list[universe_loop]->GetElementaryParticles(event_time), counter_Walk, counter_Walk + 1, counter_Walk + 2);
         if (l_switch) counter_Walk--; else counter_Walk++;//! If Switch occurred retest previous Origin
         if (counter_Walk < 0) counter_Walk = 0;

         l_origin = elementary_particle_list[counter_Walk]->GetCharge();
         l_origin_Test1 = elementary_particle_list[counter_Walk + 1]->GetCharge();
         l_origin_Test3 = l_origin_Test1 - l_origin;
         l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
         current_Distance = current_Distance + l_origin_Test5;
         }
         } while ( current_Distance < max_Distance && counter_infinite_loop_prevention < infinite_loop_prevention_threshold);


         counter_Walk = (how_many_particles - 1);
         current_Distance = 0;
         counter_infinite_loop_prevention = 0;

         do
         {
         counter_infinite_loop_prevention++;
         max_Distance = current_Distance;
         current_Distance = 0;
         while(counter_Walk >= 2)
         {
         l_switch = CompareSwapElementaryParticle(elementary_particle_list, counter_Walk, counter_Walk - 1, counter_Walk - 2);
         if (l_switch) counter_Walk++; else counter_Walk--;
         if (counter_Walk > (how_many_particles - 1)) counter_Walk = (how_many_particles - 1);

         l_origin = elementary_particle_list[counter_Walk]->GetCharge();
         l_origin_Test1 = elementary_particle_list[counter_Walk - 1]->GetCharge();
         l_origin_Test3 = l_origin_Test1 - l_origin;
         l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
         current_Distance = current_Distance + l_origin_Test5;
         }
         }
         while ( current_Distance < max_Distance && counter_infinite_loop_prevention < infinite_loop_prevention_threshold);
         }
		 */

		//! Make Elements - Hydrogen, Helium, Lithium etc
		matter_list.clear();
		/*
         std::vector<Matter*> matter_for_this_universe =  universe_list[1].AddMatter(event_time, initial_matter);
         matter_list = *matter_for_this_universe;
		 */
		/*
         status_of_call_request = AddMatter(& matter_list, & composite_particle_list,  int( composite_particle_list.size() - 1));
         if (status_of_call_request)
         {
         std::cout << "Matter addition failed!" << std::endl;
         return EXIT_FAILURE;
         }

         std::cout <<  matter_list.size() << " matter addresses created." << std::endl;
		 */
		//! Make Monomers - Carbohydrates/Sugars etc
		monomer_list.clear();
		/*
         std::vector<Monomer*> monomer_for_this_universe =  universe_list[1].AddMonomer(event_time, initial_monomer);
         monomer_list = *monomer_for_this_universe;
		 */
		/*
         status_of_call_request = AddMonomer(& monomer_list, & matter_list,  int( matter_list.size() - 1));
         if (status_of_call_request)
         {
         std::cout << "Monomer addition failed!" << std::endl;
         return EXIT_FAILURE;
         }

         std::cout <<  monomer_list.size() << " monomer addresses created." << std::endl;
		 */
		polymer_list.clear();
		/*
         std::vector<Polymer*> polymer_for_this_universe =  universe_list[1].AddPolymer(event_time, initial_polymer);
         polymer_list = *polymer_for_this_universe;
		 */
		/*
         status_of_call_request = AddPolymer(& polymer_list, & monomer_list,  int( monomer_list.size() - 1));
         if (status_of_call_request)
         {
         std::cout << "Polymer addition failed!" << std::endl;
         return EXIT_FAILURE;
         }

         std::cout <<  polymer_list.size() << " polymer addresses created." << std::endl;
		 */

		//! Cycle through Universes allocating n Cognitive Networks and updating total with reported back size.
		num_cognitive_networks_in_universe[universe_loop] = ( universe_list[universe_loop]->AddCognitiveNetworks(event_time, num_cognitive_networks_in_universe[universe_loop])).size();

		std::cout << num_cognitive_networks_in_universe[universe_loop] << " cognitive network addresses available." << std::endl;

		auto current_universe_pointer = universe_list[universe_loop];
		for(int cognitive_network_loop; cognitive_network_loop < num_cognitive_networks_in_universe[universe_loop]; cognitive_network_loop++)
		{
			//! Add Orbital objects to Cognitive Network which is derived from Universe
			auto current_cognitivenetwork_pointer = current_universe_pointer->GetCognitiveNetwork(event_time, cognitive_network_loop);

			if(auto cognitive_pointer = dynamic_cast<CognitiveNetwork*>(current_cognitivenetwork_pointer))
			{
				//! Cause initialisation
				cognitive_pointer->Update(event_time);

				num_orbitals_in_cognitive_network[cognitive_network_loop] = (cognitive_pointer->CreateOrbitals(event_time, num_orbitals_in_cognitive_network[cognitive_network_loop])).size();
				for(int init_loop = 0; init_loop < num_orbitals_in_cognitive_network[cognitive_network_loop]; init_loop++)
				{
					auto init_pointer = dynamic_cast<Orbital*>(cognitive_pointer->GetOrbital(event_time, init_loop));
					init_pointer->Update(event_time);
				}

				std::cout << num_orbitals_in_cognitive_network[cognitive_network_loop] << " orbital addresses available." << std::endl;

				//! Add Neuron objects to Cognitive Network which is derived from Universe
				num_neurons_in_cognitive_network[cognitive_network_loop] = (cognitive_pointer->CreateNeurons(event_time, num_neurons_in_cognitive_network[cognitive_network_loop])).size();
				for(int init_loop = 0; init_loop < num_neurons_in_cognitive_network[cognitive_network_loop]; init_loop++)
				{
					std::cout << "Retrieving: " << init_loop << std::endl;
					auto init_pointer = dynamic_cast<Neuron*>(cognitive_pointer->GetNeuron(event_time, init_loop));
					init_pointer->Update(event_time);
				}

				std::cout << num_neurons_in_cognitive_network[cognitive_network_loop] << " neuron addresses available." << std::endl;

				//! Add Synapse objects to Cognitive Network which is derived from Universe
				num_synapses_in_cognitive_network[cognitive_network_loop] = (cognitive_pointer->CreateSynapses(event_time, num_synapses_in_cognitive_network[cognitive_network_loop])).size();
				for(int init_loop = 0; init_loop < num_synapses_in_cognitive_network[cognitive_network_loop]; init_loop++)
				{
					auto init_pointer = dynamic_cast<Synapse*>(cognitive_pointer->GetSynapse(event_time, init_loop));
					init_pointer->Update(event_time);
				}

				std::cout << num_synapses_in_cognitive_network[cognitive_network_loop] << " synapse addresses available." << std::endl;

				//! Add Neurotransmitter objects to Cognitive Network which is derived from Universe
				num_neurotransmitters_in_cognitive_network[cognitive_network_loop] = (cognitive_pointer->CreateNeurotransmitters(event_time, num_neurotransmitters_in_cognitive_network[cognitive_network_loop]).size());
				for(int init_loop = 0; init_loop < num_neurotransmitters_in_cognitive_network[cognitive_network_loop]; init_loop++)
				{
					auto init_pointer = dynamic_cast<Neurotransmitter*>(cognitive_pointer->GetNeurotransmitter(event_time, init_loop));
					init_pointer->Update(event_time);
				}

				std::cout << num_neurotransmitters_in_cognitive_network[cognitive_network_loop] << " neurotransmitter addresses available." << std::endl;
			}

			//! For later development if spikes need to be simulated per CognitiveNetwork
			/*
             Spike.clear();
             for(int nloop = 0;nloop < initial_spikes; nloop++)
             {
             //!                status_of_call_request = AddSpike(& Spike);
             if (status_of_call_request)
             {
             std::cout << "Spike addition failed!" << std::endl;
             return EXIT_FAILURE;
             }
             //!                if (! Spike.empty())  Spike.back().creation();
             }

             std::cout <<  Spike.size() << " spike addresses created." << std::endl;
			 */
		}
	}

	int intDimensionsStart = 0;
	//! Physics dimensionality - calculating quark interactions
	int phyDimensionsStart = intDimensionsStart + num_dimensions_in_universe[0];
	//! Spatial dimensionality - real world representation
	int spaDimensionsStart = phyDimensionsStart + num_dimensions_in_universe[1];
	//! Synapse delivery problem - separate project
	int ccpDimensionsStart = spaDimensionsStart + num_dimensions_in_universe[2];
	//! Focus on spikes
	int spkDimensionsStart = ccpDimensionsStart + num_dimensions_in_universe[3];
	//! Focus on neurotransmitter calculations
	int ntrDimensionsStart = spkDimensionsStart + num_dimensions_in_universe[4];
	//! Focus on dendrite calculations
	int denDimensionsStart = ntrDimensionsStart + num_dimensions_in_universe[5];
	//! Focus on neuron calculations
	int nrnDimensionsStart = denDimensionsStart + num_dimensions_in_universe[6];
	//! Focus on synapse calculations
	int synDimensionsStart = nrnDimensionsStart + num_dimensions_in_universe[7];
	//! Focus on orbital example
	int orbDimensionsStart = synDimensionsStart + num_dimensions_in_universe[8];

	//! After screen layout the second set of points is for the quantum environment
	//
	//!    point_list.clear();
	l_spaPointBase = 0;

	for(int universe_loop = 0; universe_loop < num_universes; universe_loop++)
	{
		auto current_universe_pointer = universe_list[universe_loop];

		l_spaPointBase = int(current_universe_pointer->GetPoints(event_time).size());

		status_of_call_request = ( current_universe_pointer->AddPoints(event_time, num_elementary_particles_in_universe[universe_loop])).size();

		for (int eloop = 1; eloop < num_elementary_particles_in_universe[universe_loop]; eloop++)
		{
			auto current_elementaryparticle_pointer = current_universe_pointer->GetElementaryParticle(event_time, eloop);
			auto previous_elementaryparticle_pointer = current_universe_pointer->GetElementaryParticle(event_time, eloop - 1);

			ElementaryParticle* elementaryparticle_pointer1 = dynamic_cast<ElementaryParticle*>(current_elementaryparticle_pointer);
			ElementaryParticle* elementaryparticle_pointer2 = dynamic_cast<ElementaryParticle*>(previous_elementaryparticle_pointer);

			//! Work out the charge difference between neighbouring particles to indicate how far apart they should be.
			l_lastCharge = l_charge;
			l_charge = double (3 - std::abs(int( elementaryparticle_pointer1->GetCharge(event_time) -  elementaryparticle_pointer2->GetCharge(event_time))));
			//!        std::cout << "Charge: " << l_charge << std::endl;
			//! This angle to later be dynamic to adjust for different particle types and considering placement of existing particles
			s = (s + (180.0 - ((l_charge * l_lastCharge) * 10.0)) * DEG2RAD) / 2.0; //! in Radians
			t = (t + (180.0 - ((l_charge * l_lastCharge) * 10.0)) * DEG2RAD) / 2.0; //! in Radians
			radialDistance = l_charge;
			//!        for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + num_dimensions[2]; nloop++) {

			//! To calculate the position on the surface of a sphere is:
			//! ( where radialDistance is radius and s & t are angles in Radians. The Origin is 0,0,0 )
			//! x = radialDistance * cos(s) * sin(t)
			//! y = radialDistance * sin(s) * sin(t)
			//! z = radialDistance * cos(t)

			//! radians = angleInDegrees * Math.PI / 180
			distance_to_move.clear();

			distance_to_move = {0.0,0.0,0.0,0.0};

			auto current_point_pointer = current_universe_pointer->GetPoint(event_time, l_spaPointBase + eloop);

			Point* point_pointer = dynamic_cast<Point*>(current_point_pointer);

			point_origin =  point_pointer->GetPointPosition(event_time);

			//! Calculate position on the surface of a sphere
			//! The sphere takes the previous particle as it's Origin and the radius is related to the charge.
			//! The position on the surface will be affected by proximity to other particles.
			distance_to_move = {radialDistance * cos(s) * sin(t), radialDistance * sin(s) * sin(t), radialDistance * cos(t), 0.0};
			//!            break;

			point_pointer->SetPointPosition(event_time, distance_to_move);
			point_pointer->SetPointPositionMaxOverflow(event_time, {2});
			point_pointer->SetPointPositionMinOverflow(event_time, {2});
			point_pointer->SetPointMove(event_time, {1});
			point_pointer->SetPointMoveMaxOverflow(event_time, {2});
			point_pointer->SetPointMoveMinOverflow(event_time, {2});
			point_pointer->SetPointDifferential(event_time, {0});
		}
	}

	//!           distance_to_move = distance_to_move + point_origin;
	//!            std::cout << "d:" << distance_to_move << " r:" << radialDistance << " s:" << s << " t:" << t << std::endl;
	//!            std::cout <<  current_universe_pointer->GetPoints(event_time).back().getPointPosition() << ", ";
	//!        }
	//!        std::cout << std::endl;
	//!    }

	//!   std::cout <<  current_universe_pointer->GetPoints(event_time).size() << " point addresses created." << std::endl;

	/*
     //! Add lines to points
     for (int eloop = 1; eloop < int( elementary_particle_list.size()); eloop++)
     {
     for (int nloop = spaDimensionsStart; nloop < spaDimensionsStart + num_dimensions[2]; nloop++)
     {
     status_of_call_request = AddLine(& line_list, & polygon_list, nloop);
     if (status_of_call_request)
     {
     std::cout << "Line addition failed!" << std::endl;
     return EXIT_FAILURE;
     }
     if (! line_list.empty())  line_list.back().creation();
     if (! line_list.empty())  line_list.back().resetLine();
     }
     }
	 */

	for(int universe_loop = 0; universe_loop < num_universes; universe_loop++)
	{
		auto current_universe_pointer = universe_list[universe_loop];

		for(int cognitivenetwork_loop = 0; cognitivenetwork_loop < num_cognitive_networks_in_universe[universe_loop]; cognitivenetwork_loop++)
		{
			//! Add Orbital objects to Cognitive Network which is derived from Universe
			auto current_cognitivenetwork_pointer = current_universe_pointer->GetCognitiveNetwork(event_time, cognitivenetwork_loop);

			CognitiveNetwork* cognitive_pointer = dynamic_cast<CognitiveNetwork*>(current_cognitivenetwork_pointer);

			std::string build_filename = l_dir;
			build_filename += "/ccp" + std::to_string(universe_loop) + "x" + std::to_string(cognitivenetwork_loop) + ".in";

			std::ifstream dataFile(build_filename);
			if(!dataFile)
			{
				std::cout << "Skipped: " << build_filename << std::endl;
			}
			else
			{
				//! Read number of synapses and initial number of neurons
				std::cout << "Reading: " << build_filename << std::endl;
				entry = "";
				std::getline(dataFile, entry);
				iss.clear();
				iss.str(entry);
				buf = "";
				//! Walks through 1 row of 2 numbers
				paramCounter = 0;
				while (iss >> buf)
				{
					if(buf != "" && buf != " " && paramCounter < 10)
					{
						paramCounter++;
						//!            std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
						l_inputData.push_back(buf);
					}
				}

				numSynapses = std::stoi(l_inputData[0],&sz);
				int initial_neurons = std::stoi(l_inputData[1],&sz);

				//neuron.clear();
				//! Add initial 50 neurons
				/*
                 for(int nloop = 0; nloop < 50; nloop++)
                 {
                 status_of_call_request = CreateNeuron(& neuron, & dimension_list,  int( dimension_list.size() - 1));
                 if (status_of_call_request)
                 {
                 std::cout << "Neuron addition failed!" << std::endl;
                 return EXIT_FAILURE;
                 }
                 }
				 */

				num_neurons_in_cognitive_network[2] = (cognitive_pointer->CreateNeurons(event_time, 50)).size();

				//! Read in synapse demand data from file
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
						//! Walks through 5 rows of 10 numbers
						paramCounter = 0;
						while (iss >> buf)
						{
							if(buf != "" && buf != " " && paramCounter < 10)
							{
								paramCounter++;
								//!                    std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
								l_inputData.push_back(buf);
							}
						}
					}
					else
					{
						nloop--;
					}
				}

				/*
                 synapse.clear();
                 for(int nloop = 0; nloop < 50; nloop++)
                 {
                 //! Add synapse demands
                 status_of_call_request = AddSynapse(& synapse, & neuron,  int( neuron.size() - 1));
                 if (status_of_call_request)
                 {
                 std::cout << "Synapse addition failed!" << std::endl;
                 return EXIT_FAILURE;
                 }
                 if (! synapse.empty() && !l_inputData[nloop].empty())
                 {
                 synapse.back()->SetDemand(std::stoi(l_inputData[nloop],&sz));
                 //!            std::cout << "Synapse: " << nloop << " Demand: " <<  synapse.back().getDemand() << std::endl;
                 }
                 }
				 */
				num_synapses_in_cognitive_network[1] = (cognitive_pointer->CreateSynapses(event_time, 50)).size();

				//!    std::cout << std::endl;

				//! Load capacity data to each neuron
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
						//! Walks through 5 rows of 10 numbers
						paramCounter = 0;
						while (iss >> buf)
						{
							if(buf != "" && buf != " " && paramCounter < 10)
							{
								paramCounter++;
								//!                        std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
								l_inputData.push_back(buf);
							}
						}
					}
					else
					{
						nloop--;
					}
				}

				for(int nloop = 0; nloop < (cognitive_pointer->GetNeurons(event_time)).size(); nloop++)
				{
					auto current_neuron_pointer = cognitive_pointer->GetNeuron(event_time, nloop);
					Neuron* neuron_pointer = dynamic_cast<Neuron*>(current_neuron_pointer);

					if (neuron_pointer && !l_inputData[nloop].empty()) neuron_pointer->SetCapacity(event_time, std::stoi(l_inputData[nloop],&sz));
				}

				//! Load distance data from 50 synapses to each neuron
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
							//! Walks through 5 rows of 10 numbers
							paramCounter = 0;
							while (iss >> buf)
							{
								if(buf != "" && buf != " " && paramCounter < 10)
								{
									//!                        std::cout << buf << " ";
									paramCounter++;
									//!                        std::copy(&buf, &buf + 1, std::back_inserter(l_inputData));
									l_inputData.push_back(buf);
								}
							}
							//!                std::cout << std::endl;
						}
						else
						{
							nloop--;
						}
					}
				}

				//! Close data file - all data read in.
				iss.clear();
				dataFile.close();

				//! Transfer distance data to synapse instances
				for(int xloop = 0; xloop < 50; xloop++)
				{
					for(int nloop = 0; nloop < (cognitive_pointer->GetSynapses(event_time).size()); nloop++)
					{
						auto current_synapse_pointer = cognitive_pointer->GetSynapse(event_time, nloop);
						//!            std::cout << l_inputData[(xloop * 50) + nloop] << " ";
						if (current_synapse_pointer && !l_inputData[(xloop * 50) + nloop].empty())
						{
							//!                 current_synapse_pointer->AddDistance(& neuron[nloop], std::stod(l_inputData[(xloop * 50) + nloop],&sz));
						}
					}
				}
				//!    std::cout << std::endl;


				/*
                 for(int nloop = 0; nloop < 50; nloop++)
                 {
                 synapse[nloop].GetNeuronList(event_time);
                 }
				 */


				how_many_Synapses = int((cognitive_pointer->GetSynapses(event_time)).size());

				std::cout << how_many_Synapses << " synapses to consider." << std::endl;

				//! Rearrange new Synapses in an order closer to how they're likely to group with neurons.
				/*
                 for (int qloop = 0; qloop <= initial_synapse_alignment * how_many_Synapses; qloop++)
                 {

                 counter_Walk = 0;
                 current_Distance = 0;
                 counter_infinite_loop_prevention = 0;

                 do {
                 counter_infinite_loop_prevention++;
                 max_Distance = current_Distance;
                 current_Distance = 0;
                 while(counter_Walk <= (how_many_Synapses - 3))
                 {
                 l_switch = compare_swapSynapse(& synapse, counter_Walk, counter_Walk + 1, counter_Walk + 2);
                 if (l_switch) counter_Walk--; else counter_Walk++;//! If Switch occurred retest previous Origin
                 if (counter_Walk < 0) counter_Walk = 0;

                 l_origin =  synapse[counter_Walk].GetDemand(event_time);
                 l_origin_Test1 =  synapse[counter_Walk + 1].GetDemand(event_time);
                 l_origin_Test3 = l_origin_Test1 - l_origin;
                 l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
                 current_Distance = current_Distance + l_origin_Test5;
                 }
                 } while ( current_Distance < max_Distance && counter_infinite_loop_prevention < infinite_loop_prevention_threshold);


                 counter_Walk = (how_many_Synapses - 1);
                 current_Distance = 0;
                 counter_infinite_loop_prevention = 0;

                 do {
                 counter_infinite_loop_prevention++;
                 max_Distance = current_Distance;
                 current_Distance = 0;
                 while(counter_Walk >= 2)
                 {
                 l_switch = compare_swapSynapse(& synapse, counter_Walk, counter_Walk - 1, counter_Walk - 2);
                 if (l_switch) counter_Walk++; else counter_Walk--;
                 if (counter_Walk > (how_many_Synapses - 1)) counter_Walk = (how_many_Synapses - 1);

                 l_origin =  synapse[counter_Walk].GetDemand(event_time);
                 l_origin_Test1 =  synapse[counter_Walk - 1].GetDemand(event_time);
                 l_origin_Test3 = l_origin_Test1 - l_origin;
                 l_origin_Test5 = l_origin_Test3 * l_origin_Test3;
                 current_Distance = current_Distance + l_origin_Test5;
                 }
                 } while ( current_Distance < max_Distance && counter_infinite_loop_prevention < infinite_loop_prevention_threshold);
                 }
				 */
				int maxCapacity = 120;
				int currentCapacity = 0;

				for(int nloop = 0; nloop < (cognitive_pointer->GetSynapses(event_time).size()); nloop++)
				{
					auto current_synapse_pointer = cognitive_pointer->GetSynapse(event_time, nloop);
					Synapse* synapse_pointer = dynamic_cast<Synapse*>(current_synapse_pointer);

					if(currentCapacity +  synapse_pointer->GetDemand(event_time) <= maxCapacity)
					{
						currentCapacity +=  synapse_pointer->GetDemand(event_time);
					}
				}

				orbital.clear();

				int pollCapture = 0;

				//! Orbital function for interaction.
				/*
                 for (int zloop = 0; zloop < num_orbitals_in_cognitive_network[current_cognitive_network]; zloop++)
                 {
                 for (int nloop = orbDimensionsStart; nloop < orbDimensionsStart + num_dimensions[9]; nloop++)
                 {
                 status_of_call_request = AddOrbital(& orbital, & dimension_list, nloop, 0);
                 if (status_of_call_request)
                 {
                 std::cout << "Orbital addition failed!" << std::endl;
                 return EXIT_FAILURE;
                 }
                 if (! orbital.empty())  orbital.back()->SetPhase(TWORAD / zloop);
                 }
                 }
				 */

				l_pointStart = int(l_spaPointBase);
				l_ccpPointStart = int( current_universe_pointer->GetPoints(event_time).size());
				/*
                 //! 50 synapses and 50 possible neurons
                 for(int xloop = 0; xloop < 100; xloop++)
                 {
                 for (int nloop = ccpDimensionsStart; nloop < ccpDimensionsStart + num_dimensions[3]; nloop++)
                 {
                 //!        std::cout << "Dimension Loop: " << nloop << " ";
                 status_of_call_request = AddPoint(& current_universe_pointer->GetPoints(event_time), & dimension_list, nloop);
                 if (status_of_call_request)
                 {
                 std::cout << "Point addition failed!" << std::endl;
                 return EXIT_FAILURE;
                 }
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->resetPoint();  //! Initialise first point to location zero.
                 //! Synapse points first
                 if(xloop < 50)
                 {
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPosition(rand() % 2 - 1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMin(-1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMinOverflow(2.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMax(1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMaxOverflow(2.0);  //! Initialise to ne coordinate.
                 }
                 else
                 {
                 //! Neuron points second
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPosition(rand() % 2 - 1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMin(-1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMinOverflow(2.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMax(1.0);  //! Initialise to ne coordinate.
                 if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPositionMaxOverflow(2.0);  //! Initialise to ne coordinate.
                 }
                 }
                 }
				 */
			}
		}

		int l_ccpPointEnd = int( current_universe_pointer->GetPoints(event_time).size());
		//! End of CCP draw points

		//! Start of Spike draw points
		int l_spkPointStart = int( current_universe_pointer->GetPoints(event_time).size());
		int initial_spikes = 1;


		int l_spkPointEnd = int( current_universe_pointer->GetPoints(event_time).size());
		//! End of CCP draw points

		//! Start of Orbital draw points
		int l_orbPointStart = int( current_universe_pointer->GetPoints(event_time).size());

		/*
         for(int qloop = 0; qloop < num_orbitals_in_cognitive_network[current_cognitive_network][0]; qloop++)
         {
         for (int nloop = orbDimensionsStart; nloop < orbDimensionsStart + num_dimensions_in_universe[9]; nloop++)
         {
         dimension_list[nloop]->SetOffset(0);
         dimension_list[nloop]->SetScale(100);
         status_of_call_request = AddPoint(& current_universe_pointer->GetPoints(event_time), & dimension_list, nloop);
         if (status_of_call_request)
         {
         std::cout << "Point addition failed!" << std::endl;
         return EXIT_FAILURE;
         }
         if (! current_universe_pointer->GetPoints(event_time).empty())  current_universe_pointer->GetPoints(event_time).back()->SetPointPosition(qloop);
         }
         }
		 */
		int l_orbPointEnd = int( current_universe_pointer->GetPoints(event_time).size());
		//! End of Orbital Points
		int l_pointEnd = int( current_universe_pointer->GetPoints(event_time).size());
	}

	//! Configure Dynap-se, if attached to reflect simulation configuration

	if(device_attached)
	{
		//! Let's take a look at the information we have on the device.
		dynapse_info = caerDynapseInfoGet(usb_handle);

		printf("%s --- ID: %d, Master: %d,  Logic: %d.\n",
				dynapse_info.deviceString, dynapse_info.deviceID,
				dynapse_info.deviceIsMaster, dynapse_info.logicVersion);


		caerDeviceConfigSet(usb_handle, CAER_HOST_CONFIG_DATAEXCHANGE, CAER_HOST_CONFIG_DATAEXCHANGE_BLOCKING, true);

		caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_RUN, true);

		caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_AER, DYNAPSE_CONFIG_AER_RUN, true);

		caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);

		//! force chip to be enable even if aer is off
		caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_MUX, DYNAPSE_CONFIG_MUX_FORCE_CHIP_BIAS_ENABLE, true);

		printf("Configuring low power biases...");
		std::ifstream inputbiases( LOWPOWERBIASES);
		for (std::string line; std::getline(inputbiases, line);) {
			int i_dec = atoi(line.c_str());
			caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP,
					DYNAPSE_CONFIG_CHIP_CONTENT, i_dec);
		}
		inputbiases.close();
		printf(" Done.\n");

		caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_ID, DYNAPSE_CONFIG_DYNAPSE_U2);

		int sramId = 1;

		for(int coreId = 0; coreId < DYNAPSE_CONFIG_NUMCORES; coreId++)
		{
			destinationCoreId = 2^coreId;
			caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_MONITOR_NEU, coreId, 0); //! core 0-3 neu 0

			for(int neuronId = 0; neuronId < DYNAPSE_CONFIG_NUMNEURONS_CORE; neuronId++)
			{
				if(((1 + neuronId) * ((neuronId % 3) > 0)) > 0 && ((1 + neuronId) * ((neuronId % 3) > 0)) < DYNAPSE_CONFIG_NUMNEURONS_CORE)
				{
					genBits = neuronId << 7 | sramId << 5 | coreId << 15 | 1 << 17 | 1 << 4 | destinationCoreId << 18 | dynap_Sy << 27 | dynap_Dy << 25 | dynap_Dx << 22 | dynap_Sx << 24 | coreId << 28;
					caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, genBits);
					//! Handle, PreNeuron[0,1023], PostNeuron[0,1023], Cam[0,63], Type
					//caerDynapseWriteCam(usb_handle, neuronId, ((1 + neuronId) * ((neuronId % 3) > 0)), 0, DYNAPSE_CONFIG_CAMTYPE_F_EXC);
				}
				if(neuronId > 2 && (((neuronId - 2) * (((1 + neuronId) * ((neuronId % 3) > 0) == 0)) + (1 * ((neuronId % 3) == 0)))) > 0 && (((neuronId - 2) * (((1 + neuronId) * ((neuronId % 3) > 0) == 0)) + (1 * ((neuronId % 3) == 0)))) < DYNAPSE_CONFIG_NUMNEURONS_CORE)
				{
					genBits = neuronId << 7 | sramId << 5 | coreId << 15 | 1 << 17 | 1 << 4 | destinationCoreId << 18 | dynap_Sy << 27 | dynap_Dy << 25 | dynap_Dx << 22 | dynap_Sx << 24 | coreId << 28;
					caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, genBits);
					//! Handle, PreNeuron[0,1023], PostNeuron[0,1023], Cam[0,63], Type
					//caerDynapseWriteCam(usb_handle, neuronId, (((neuronId - 2) * (((1 + neuronId) * ((neuronId % 3) > 0) == 0)) + (1 * ((neuronId % 3) == 0)))), 1, DYNAPSE_CONFIG_CAMTYPE_F_EXC);
				}
				for(int innerLoop = 2; innerLoop < 7; innerLoop++)
				{
					//!                    if(((int(neuronId / (2^(neuronId + 1))) + 8) * ((neuronId % 3) == 0)) > 0 && ((int(neuronId / (2^(innerLoop + 1))) + 8) * ((neuronId % 3) == 0)) < DYNAPSE_CONFIG_NUMNEURONS_CORE)
					{
						genBits = neuronId << 7 | sramId << 5 | coreId << 15 | 1 << 17 | 1 << 4 | destinationCoreId << 18 | dynap_Sy << 27 | dynap_Dy << 25 | dynap_Dx << 22 | dynap_Sx << 24 | coreId << 28;
						caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, genBits);
						//caerDynapseWriteCam(usb_handle, neuronId, ((int(neuronId / (2^(neuronId + 1))) + 8) * ((neuronId % 3) == 0)), innerLoop, DYNAPSE_CONFIG_CAMTYPE_F_EXC);
					}
				}
			}
		}


	}


	//! Now let's start getting some data from the device. We just loop, no notification needed.
	if(device_attached)
	{
		caerDeviceDataStart(usb_handle, NULL, NULL, NULL, NULL, NULL);
		printf("Start connected devices...\n");
	}

	for(int add_renderers_loop = 0; add_renderers_loop < static_renderers_counter + dynamic_renderers_counter + 1; add_renderers_loop++)
	{
		define_renderers[add_renderers_loop]->SetBackground(1, 1, 1);
		define_renderers[add_renderers_loop]->GetActiveCamera()->SetFocalPoint(0, 0, 0);
		define_renderers[add_renderers_loop]->GetActiveCamera()->SetPosition(1, 0, 0);
		define_renderers[add_renderers_loop]->GetActiveCamera()->SetViewUp(0, 0, 1);
		define_renderers[add_renderers_loop]->ResetCamera();
		define_renderers[add_renderers_loop]->GetActiveCamera()->Azimuth(20);
		define_renderers[add_renderers_loop]->GetActiveCamera()->Elevation(30);
		define_renderers[add_renderers_loop]->GetActiveCamera()->Dolly(1.2);
		define_renderers[add_renderers_loop]->ResetCameraClippingRange();
		define_renderers[add_renderers_loop]->ResetCamera();
	}


	//! The program will loop whilst the graphics window is open
	clockTime = std::chrono::high_resolution_clock::now();
	lastClockTime = clockTime;
	event_time = clockTime;
	startTime = clockTime;
	uint64_t dynapTime = 1000000000000;
	int duration = 0;
	caerEventPacketContainer packetContainer;


	//! Remove Initialising banner from screen.
	define_textactors[0]->SetInput("");
	render_window->SetWindowName("BrainHarmonics (c) 2020, Linaro Ltd."); //! Set the title

	//! Establish Screen
	render_window_interactor->SetRenderWindow(render_window);
	render_window_interactor->Initialize();
	render_window_interactor->CreateRepeatingTimer(100); //! in milliseconds
	UpdateAllCommand * update_all_callback = UpdateAllCommand::New();
	render_window_interactor->AddObserver(vtkCommand::TimerEvent, update_all_callback);

	//! Begin visualisation
	render_window->Render();
	//! Prepared for multiscreen
	//!         screen =  screens[ screen]->runScreen(window);

	if(device_attached)
	{
		//! Retrieve data from Dynap-se (if any)
		//std::cout << "Retrieve data from device...";
		packetContainer = caerDeviceDataGet(usb_handle);
		//std::cout << " Complete." << std::endl;
	}

	std::cout << "Window rendered..." << std::endl;
	sleep(5);

	/*
     //std::cout << clockTime.time_since_epoch().count() << std::endl;
     duration = std::chrono::duration_cast<std::chrono::nanoseconds>(clockTime - lastClockTime).count();
     duration *=  dimension_list[0]->GetTime();
     //std::cout << duration << std::endl;
     event_time += std::chrono::nanoseconds(duration);
     lastClockTime = clockTime;

     if(device_attached)
     {
     if (packetContainer != NULL)
     {
     int32_t packetNum = caerEventPacketContainerGetEventPacketsNumber(packetContainer);

     //printf("\nGot event container with %d packets (allocated).\n", packetNum);

     for (int32_t i = 0; i < packetNum; i++)
     {
     caerEventPacketHeader packetHeader = caerEventPacketContainerGetEventPacket(packetContainer, i);
     if (packetHeader == NULL)
     {
     //printf("Packet %d is empty (not present).\n", i);
     continue; //! Skip if nothing there.
     }

     //printf("Packet %d of type %d -> size is %d.\n", i,
     //!   caerEventPacketHeaderGetEventType(packetHeader),
     //!   caerEventPacketHeaderGetEventNumber(packetHeader));

     if (caerEventPacketHeaderGetEventType(packetHeader) == SPIKE_EVENT)
     {

     caerSpikeEventPacket evts = (caerSpikeEventPacket) packetHeader;

     //! read all events
     CAER_SPIKE_ITERATOR_ALL_START(evts)

     uint64_t ts = caerSpikeEventGetTimestamp(
     caerSpikeIteratorElement);
     uint64_t neuronId = caerSpikeEventGetNeuronID(
     caerSpikeIteratorElement);
     uint64_t sourcecoreId = caerSpikeEventGetSourceCoreID(
     caerSpikeIteratorElement); //! which core is from
     uint64_t coreId = caerSpikeEventGetChipID(
     caerSpikeIteratorElement);//! destination core (used as chip id)

     //!                    printf("SPIKE: ts %llu , neuronID: %llu , sourcecoreID: %llu, ascoreID: %llu\n",ts, neuronId, sourcecoreId, coreId);
     if(ts < dynapTime)
     {
     dynapTime = ts;
     }
     uint64_t syncTime = (ts - dynapTime) *  dimension_list[0]->GetTime();
     if(int(std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - (startTime + std::chrono::microseconds(syncTime))).count()) < 0)
     {
     event_time = startTime + std::chrono::microseconds(syncTime);
     }
     if(neuronId <  orbital.size())
     {
     orbital[int(neuronId)].AddTemporalAdjustment(startTime + std::chrono::microseconds(syncTime), 20000.0);
     }
     //std::cout << int((neuronId)) << " ";

     //std::cout << int((neuronId % 6)) << " " << syncTime << " " << int(std::chrono::duration_cast<std::chrono::nanoseconds>(event_time - (startTime + std::chrono::microseconds(syncTime))).count()) << "  " <<  orbital[int(neuronId % 6)].GetEnergy() << std::endl;
     CAER_SPIKE_ITERATOR_ALL_END
     }
     }

     caerEventPacketContainerFree(packetContainer);
     }
     }

     poll_capture = sniffex(2,list<char>& {"sniffex","en0"});

     for (int nloop = 0; nloop < num_orbitals_in_cognitive_network[current_cognitive_network]; nloop++)
     {
     orbital[nloop].Update(event_time);
     }

     pauseLoop++;
     if(pauseLoop > 50000)
     {
     //! Synthetic periodic stimulus
     if(!device_attached)
     {
     for (int nloop = 0; nloop < 6; nloop++)
     {
     orbital[nloop].AddTemporalAdjustment(event_time, 20000.0);
     }
     }
     pauseLoop = 0;
     //!            sleep(2);
     //!                std::cout << "Actual: " << time(0) << " Virtual: " <<  universe_list[0].theTimeNow() << std::endl;
     }
	 */
	/*
     for(int ploop = 0; ploop < 10000; ploop++)
     {

     }
	 */
	/*
     //! Early calculation for colliding elementary particles and the effect on direction and acceleration
     for(int n = 0; n < l_pointEnd; n = n + 4)
     {
     for(int p = 0; p < l_pointEnd; p = p + 4)
     {
     if(n != p)
     {
     xd =  current_universe_pointer->GetPoint(event_time, p].getPointPosition() -  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time);
     yd =  current_universe_pointer->GetPoint(event_time, p + 1].getPointPosition() -  current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time);
     zd =  current_universe_pointer->GetPoint(event_time, p + 2].getPointPosition() -  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time);
     pointDistance2 = (xd * xd + yd * yd + zd * zd);
     effect = 1 + (1 / pointDistance2);
     current_universe_pointer->GetPoint(event_time, n]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, n].GetPointDifferential(event_time) * effect);
     current_universe_pointer->GetPoint(event_time, p]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, p].GetPointDifferential(event_time) * effect);
     current_universe_pointer->GetPoint(event_time, n + 1]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, n + 1].GetPointDifferential(event_time) * effect);
     current_universe_pointer->GetPoint(event_time, p + 1]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, p + 1].GetPointDifferential(event_time) * effect);
     current_universe_pointer->GetPoint(event_time, n + 2]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, n + 2].GetPointDifferential(event_time) * effect);
     current_universe_pointer->GetPoint(event_time, p + 2]->SetPointDifferential( current_universe_pointer->GetPoint(event_time, p + 2].GetPointDifferential(event_time) * effect);
     }
     }
     }
	 */

	/*
     for (int qloop = 0; qloop < orbital_layers.size() - 1; qloop++)
     {
     for (int zloop = orbital_layers[qloop]; zloop <= (orbital_layers[qloop + 1]); zloop++)
     {
     for (int nloop = orbital_layers[qloop]; nloop <= (orbital_layers[qloop + 1]); nloop++)
     {
     if (zloop != nloop)
     {
     compareFirst =  orbital[zloop].GetPosition(event_time) /  orbital[nloop].GetPosition(event_time);
     if(0.5 - compareFirst > -0.1f && 0.5 - compareFirst < 0.1f)
     {
     if (zloop < nloop)
     {
     //! Start of stimulus emulation
     if( orbital[zloop].GetEnergy() > 1.0)
     {
     orbital[zloop].AddTemporalAdjustment(event_time, 1.0);
     //! orbital[nloop].AddTemporalAdjustment(event_time, 10.0);
     //iter_swap( orbital.begin() + (zloop),  orbital.begin() + (zloop + 1));
     OrbConnection myOrbConnection;
     myOrbConnection.OrbOne = zloop;
     myOrbConnection.OrbTwo = nloop;
     myOrbConnection.OrbConnectionStrength = 5.0;
     myOrbConnection.OrbConnectionModifier = 1.0;
     myOrbConnection.OrbSpike = true;
     myOrbConnection.OrbOnePosition = 0.0;
     myOrbConnection.OrbTwoPosition = 0.0;
     OrbConnectionList.push_back(myOrbConnection);
     }
     }
     }
     }
     }
     }
     }

     for(int qloop = 0; qloop < OrbConnectionList.size() - 1; qloop++)
     {
     for(int zloop = qloop + 1; zloop < OrbConnectionList.size(); zloop++)
     {
     if(OrbConnectionList[qloop].OrbOne == OrbConnectionList[zloop].OrbOne)
     {
     if(OrbConnectionList[qloop].OrbTwo == OrbConnectionList[zloop].OrbTwo)
     {
     OrbConnectionList[qloop].OrbConnectionStrength += OrbConnectionList[zloop].OrbConnectionStrength;
     OrbConnectionList[zloop].OrbConnectionStrength = 0.0;
     OrbConnectionList[qloop].OrbConnectionModifier *= OrbConnectionList[zloop].OrbConnectionModifier;
     OrbConnectionList[zloop].OrbConnectionModifier = 0.0;
     OrbConnectionList[qloop].OrbSpike = true;
     }
     }
     }
     }
     if(pauseLoop % 1 == 0)
     {
     OrbConnectionList.erase( std::remove_if(OrbConnectionList.begin(), OrbConnectionList.end(), []( const OrbConnection& item) { return (item.OrbConnectionStrength < 0.1f ); }), OrbConnectionList.end());
     }

     for(int qloop = 0; qloop < OrbConnectionList.size() - 1; qloop++)
     {
     if(OrbConnectionList[qloop].OrbSpike)
     {
     if( orbital[OrbConnectionList[qloop].OrbOne].GetEnergy(event_time) > (OrbConnectionList[qloop].OrbConnectionStrength) * OrbConnectionList[qloop].OrbConnectionModifier)
     {
     orbital[OrbConnectionList[qloop].OrbOne].AddTemporalAdjustment(event_time, (OrbConnectionList[qloop].OrbConnectionStrength) * OrbConnectionList[qloop].OrbConnectionModifier);
     orbital[OrbConnectionList[qloop].OrbTwo].AddTemporalAdjustment(event_time, (OrbConnectionList[qloop].OrbConnectionStrength) * OrbConnectionList[qloop].OrbConnectionModifier);
     }
     else
     {
     orbital[OrbConnectionList[qloop].OrbOne].AddTemporalAdjustment(event_time,  orbital[OrbConnectionList[qloop].OrbOne].GetEnergy(event_time));
     orbital[OrbConnectionList[qloop].OrbTwo].AddTemporalAdjustment(event_time,  orbital[OrbConnectionList[qloop].OrbOne].GetEnergy(event_time));
     }
     OrbConnectionList[qloop].OrbSpike = false;
     }
     else
     {
     OrbConnectionList[qloop].OrbConnectionStrength *= 0.99;
     OrbConnectionList[qloop].OrbConnectionModifier *= 0.99;
     }
     }

     if(pauseLoop % 2500 == 0)
     {
     std::cout << "Sending stimuli..." << std::endl;
     //Send spike to Dynapse
     genBits = 1 << 20; //! CAM address (8 bits)
     genBits += 0 << 18; //! Core address (2 bits)
     genBits += 0 << 16; //! Hard code (2 bits)
     genBits += 0 << 14; //! Padding (2 bits)
     genBits += 1 << 13; //! Hard code (1 bits)
     genBits += 0 << 10; //! Padding (3 bits)
     genBits += 0 << 9; //! N/S Direction (1 bit)
     genBits += 0 << 7; //! Skip chips (2 bits)
     genBits += 0 << 6; //! E/W Direction (1 bit)
     genBits += 0 << 4; //! Skip chips (2 bits)
     genBits += 1; //! Core (4 bits)


     caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, 0, 0); //! core 0-3 neu 0

     genBits = neuronId << 7 | sramId << 5 | coreId << 15 | 1 << 17 | 1 << 4 | destinationCoreId << 18 | dynap_Sy << 27 | dy << 25 | dynap_Dx << 22 | dynap_Sx << 24 | coreId << 28;

     caerDeviceConfigSet(usb_handle, DYNAPSE_CONFIG_CHIP, DYNAPSE_CONFIG_CHIP_CONTENT, genBits);
     std::cout << "Sent stimuli." << std::endl;
     }

     //! Transfer orbital details to points
     for (int nloop = l_orbPointStart; nloop < l_orbPointEnd; nloop++)
     {
     calcY =  orbital[nloop - l_orbPointStart].GetPosition(event_time);
     calcYoffset =  dimension_list[orbDimensionsStart + ((nloop - l_orbPointStart) % num_dimensions[9])].GetOffset(event_time);
     calcYscale =  dimension_list[orbDimensionsStart + ((nloop - l_orbPointStart) % num_dimensions[9])].GetScale(event_time);
     calcY = calcY + calcYoffset;
     calcY = calcY * calcYscale;

     current_universe_pointer->GetPoint(event_time, nloop]->SetPointPosition(event_time, calcY);
     //std::cout << calcX << "   ";
     }
     //! std::cout << std::endl;
	 */

	/*
     for(int x = l_ccpPointStart; x < l_ccpPointStart + 100; x = x + 2)
     {
     for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
     {
     l_desired_distance =  synapse[int((x - l_ccpPointStart)/2)].GetDistance(event_time, int((n - (l_ccpPointStart + 100))/2.0));
     nodeList.clear();
     nodeList.push_back(x);
     nodeList.push_back(x + 1);
     nodeList.push_back(n);
     nodeList.push_back(n + 1);

     //!                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desired_distance << std::endl;

     status_of_call_request = DistanceBetweenNodes(& current_universe_pointer->GetPoints(event_time), &nodeList, 2, l_desired_distance);

     //!                std::cout << "Retrieved : " <<  current_universe_pointer->GetPoint(event_time, nodeList[0]].GetPointDifferential(event_time) << ", " <<  current_universe_pointer->GetPoint(event_time, nodeList[1]].GetPointDifferential(event_time) << ", " <<  current_universe_pointer->GetPoint(event_time, nodeList[2]].GetPointDifferential(event_time) << ", " <<  current_universe_pointer->GetPoint(event_time, nodeList[3]].GetPointDifferential(event_time) << std::endl;

     }
     }

     for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
     {
     l_demandCounter = 0;
     for(int x = l_ccpPointStart; x < l_ccpPointStart + 100; x = x + 2)
     {
     l_desired_distance =  synapse[int((x - l_ccpPointStart)/2)].getDistance(int((n - (l_ccpPointStart + 100))/2.0));
     nodeList.clear();
     nodeList.push_back(n);
     nodeList.push_back(n + 1);
     nodeList.push_back(x);
     nodeList.push_back(x + 1);

     //!                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desired_distance << std::endl;

     status_of_call_request = DistanceBetweenNodes(& current_universe_pointer->GetPoints(event_time), &nodeList, 2, l_desired_distance);

     if( synapse[int((x - l_ccpPointStart)/2)].GetAllocatedNeuron(event_time) == int( n - (l_ccpPointStart + 100 ))/2)
     {
     l_demandCounter = l_demandCounter +  synapse[int((x - l_ccpPointStart)/2)].GetDemand(event_time);
     }
     //!                std::cout << ((n - (l_ccpPointStart + 100)) / 2) << " - " <<  synapse[int((x - l_ccpPointStart)/2)].GetAllocatedNeuron(event_time) << " - " << int( n - (l_ccpPointStart + 100 ))/2 << " - " << l_demandCounter << std::endl;
     }
     }

     for(int n = l_ccpPointStart + 100; n < l_ccpPointStart + 200 ; n = n + 2)
     {
     for(int x = l_ccpPointStart + 100; x < l_ccpPointStart + 200; x = x + 2)
     {
     if (n != x)
     {
     l_desired_distance = 0.1;
     nodeList.clear();
     nodeList.push_back(n);
     nodeList.push_back(n + 1);
     nodeList.push_back(x);
     nodeList.push_back(x + 1);

     //!                std::cout << "Request nodes: " << nodeList[0] << ", " << nodeList[1] << ", " << nodeList[2] << ", " << nodeList[3] << " Dist:" << l_desired_distance << std::endl;

     status_of_call_request = DistanceBetweenNodes(& current_universe_pointer->GetPoints(event_time), &nodeList, 2, l_desired_distance);
     }
     }
     }

     pArgs = NULL;
     pArrayArgs = NULL;
     pTransferArray = NULL;
     pValue = NULL;
     pArgs = PyTuple_New(2);
     //!        pValue = PyInt_FromLong(3);
     npy_intp dims[2] = {2,15}
     pArrayArgs = PyArray_SimpleNew(2, dims, NPY_INT);
     //! The pointer to the array data is accessed using PyArray_DATA()
     pTransferArray = (int *) PyArray_DATA(pArrayArgs);
     //! Copy the data from the "array of arrays" to the contiguous numpy array.
     l_transferArray.clear();
     for (int tloop = l_ccpPointStart; tloop < l_ccpPointStart + 30; tloop++)
     {
     l_transferArray.push_back((int)round( current_universe_pointer->GetPoint(event_time, tloop].GetPointPosition(event_time)));
     //!            std::cout << l_transferArray.back() << ", ";
     }
     //!        std::cout << std::endl;
     std::memcpy(pTransferArray, &l_transferArray, sizeof(int) * 30);
     PyTuple_SetItem(pArgs,0,pArrayArgs);
     pValue = PyInt_FromLong(2);
     PyTuple_SetItem(pArgs,1,pValue);

     //!        pValue = PyObject_CallObject(pFunc, pArgs);
     pValue = PyObject_CallObject(pFunc, pArgs);
     //!        Py_DECREF(pArgs);
     //!        Py_DECREF(pArrayArgs);
     if (pValue != NULL) {
     //!            printf("Result of call: %ld\n", PyInt_AsLong(pValue));
     //!            Py_DECREF(pValue);
     //!            Py_DECREF(pTransferArray);
     //!            pValue = NULL;
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
     //!            std::cout << n << " ";
     current_universe_pointer->GetPoint(event_time, n].PointPoll(event_time, 1);
     current_universe_pointer->GetPoint(event_time, n].OverflowPoll(event_time);
     }
     //!        std::cout << std::endl;
	 */
	/*
     patternFound = analyseStream(& neuron, & current_universe_pointer->GetPoints(event_time), l_pointStart, (l_ccpPointStart + 0) - num_dimensions[2], num_dimensions[2],1);
     patternFound = analyseStream(& neuron, & current_universe_pointer->GetPoints(event_time), l_pointStart + 1, (l_ccpPointStart + 1) - num_dimensions[2], num_dimensions[2],2);
     patternFound = analyseStream(& neuron, & current_universe_pointer->GetPoints(event_time), l_pointStart + 2, (l_ccpPointStart + 2) - num_dimensions[2], num_dimensions[2],3);

     patternFound = analyseStream(& neuron, & current_universe_pointer->GetPoints(event_time), l_ccpPointStart, (l_pointEnd + 0) - num_dimensions[3], num_dimensions[3],1);
     patternFound = analyseStream(& neuron, & current_universe_pointer->GetPoints(event_time), l_ccpPointStart + 1, (l_pointEnd + 1) - num_dimensions[3], num_dimensions[3],2);
	 */
	//! Now to put all the calculations into something visual. Drawing to the screen. Scaled and orientated.
	//!   define_points.clear();
	/*
     for(int n = l_pointStart; n < l_ccpPointStart; n = n + num_dimensions[2])
     {
     calcX =  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time);
     calcY =  current_universe_pointer->GetPoint(event_time, n+1].GetPointPosition(event_time);
     calcZ =  current_universe_pointer->GetPoint(event_time, n+2].GetPointPosition(event_time);
     calcXoffset =  dimension_list[0].GetOffset(event_time);
     calcYoffset =  dimension_list[1].GetOffset(event_time);
     calcZoffset =  dimension_list[2].GetOffset(event_time);
     calcXscale =  dimension_list[0].GetScale(event_time);
     calcYscale =  dimension_list[1].GetScale(event_time);
     calcZscale =  dimension_list[2].GetScale(event_time);
     calcX = calcX + calcXoffset;
     calcY = calcY + calcYoffset;
     calcZ = calcZ + calcZoffset;
     calcX = calcX * calcXscale;
     calcY = calcY * calcYscale;
     calcZ = calcZ * calcZscale;
     calcX = calcX / calcZ;
     calcY = calcY / calcZ;
     calcX = calcX + ( l_screenX / 2.0);
     calcY = l_screenY - (calcY + ( l_screenY / 2.0));

     define_points.push_back(sf::Vertex(sf::Vector2f(calcX, calcY), sf::Color(255,255,0,255)));
     //! define_points.push_back(sf::Vertex(sf::Vector2f((( current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenX / 2), l_screenY - ((( current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenY / 2))), sf::Color(255,255,0,255)));
     //!            std::cout << n << " = " << (( current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenX / 2) << " : " << l_screenY - ((( current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenY / 2)) << std::endl;
     }
	 */
	/*
     for(int n = l_ccpPointStart; n < l_ccpPointEnd; n = n + num_dimensions[3])
     {
     calcX =  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time);
     calcY =  current_universe_pointer->GetPoint(event_time, n+1].GetPointPosition(event_time);
     calcXoffset =  dimension_list[0].GetOffset(event_time);
     calcYoffset =  dimension_list[1].GetOffset(event_time);
     calcXscale =  dimension_list[0].GetScale(event_time);
     calcYscale =  dimension_list[1].GetScale(event_time);
     calcX = calcX + calcXoffset;
     calcY = calcY + calcYoffset;
     calcX = calcX * calcXscale;
     calcY = calcY * calcYscale;
     calcX = calcX + ( l_screenX / 2.0);
     calcY = l_screenY - (calcY + ( l_screenY / 2.0));

     define_points.push_back(sf::Vertex(sf::Vector2f(calcX, calcY), sf::Color(128,255,128,255)));
     //! define_points.push_back(sf::Vertex(sf::Vector2f((( current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time)))+100, l_screenY - ((( current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time)))+100)), sf::Color(128,255,128,255)));
     //!            std::cout << n << " = " << (( current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenX / 2) << " : " << l_screenY - ((( current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time) /  current_universe_pointer->GetPoint(event_time, n + 2].GetPointPosition(event_time)) * l_scale) + (l_screenY / 2)) << std::endl;
     }
	 */
	/*
     for(int n = l_spkPointStart; n < l_spkPointEnd; n = n + num_dimensions[4])
     {
     calcX =  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time);
     calcY =  current_universe_pointer->GetPoint(event_time, n+1].GetPointPosition(event_time);
     calcXoffset =  dimension_list[0].GetOffset(event_time);
     calcYoffset =  dimension_list[1].GetOffset(event_time);
     calcXscale =  dimension_list[0].GetScale(event_time);
     calcYscale =  dimension_list[1].GetScale(event_time);
     calcX = calcX + calcXoffset;
     calcY = calcY + calcYoffset;
     calcX = calcX * calcXscale;
     calcY = calcY * calcYscale;
     calcX = calcX + ( l_screenX / 2.0);
     calcY = l_screenY - (calcY + ( l_screenY / 2.0));

     define_points.push_back(sf::Vertex(sf::Vector2f(calcX, calcY), sf::Color(255,0,0,255)));
     //! define_points.push_back(sf::Vertex(sf::Vector2f((( current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time)))+100, l_screenY - ((( current_universe_pointer->GetPoint(event_time, n + 1].GetPointPosition(event_time)))+100)), sf::Color(255,0,0,255)));
     //!            std::cout <<  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time) << ":" <<  current_universe_pointer->GetPoint(event_time, n+1].GetPointPosition(event_time) << ", ";
     }
	 */
	//!        std::cout << std::endl;

	/*
     draw_lines.clear();
     colourMax = 0.0;
     for(int n2 = 0; n2 <= l_orbPointEnd - l_orbPointStart; n2 = n2 + num_dimensions[9])
     {
     if( orbital[n2].GetEnergy(event_time) > colourMax)
     colourMax =  orbital[n2].GetEnergy(event_time);
     }
     colourMax = 255.0 / colourMax;
     for(int n = l_orbPointStart; n < l_orbPointEnd; n = n + num_dimensions[9])
     {
     if( orbital[n - l_orbPointStart].GetEnergy(event_time) > 0)
     {
     calcX = ((2.0 / (l_orbPointEnd - l_orbPointStart)) * (n - l_orbPointStart)) - 1.0;
     //std::cout << "X: " << calcX << std::endl;
     calcY =  current_universe_pointer->GetPoint(event_time, n].GetPointPosition(event_time);
     calcXoffset =  dimension_list[0].GetOffset(event_time);
     calcYoffset =  dimension_list[1].GetOffset(event_time);
     calcXscale =  dimension_list[0].GetScale(event_time);
     calcYscale =  dimension_list[1].GetScale(event_time);
     calcX = calcX + calcXoffset;
     calcY = calcY + calcYoffset;
     calcX = calcX * calcXscale;
     calcY = calcY * calcYscale;
     calcX = calcX * 320.0;
     calcY = calcY * 50.0;
     for (int zloop = 0; zloop < orbital_layers.size() - 1; zloop++)
     {
     if ((n - l_orbPointStart) >= orbital_layers[zloop] && (n - l_orbPointStart) < orbital_layers[zloop + 1])
     {
     calcX += (zloop * 10);
     }
     }
     calcX = calcX + ( l_screenX / 2.0);
     calcY = l_screenY - (calcY + ( l_screenY / 2.0));
     colourY = int(colourMax *  orbital[n - l_orbPointStart].GetEnergy(event_time));

     draw_lines.push_back(sf::Vertex(sf::Vector2f(calcX, l_screenY - ( l_screenY / 2)), sf::Color(0,0,255,255)));
     draw_lines.push_back(sf::Vertex(sf::Vector2f(calcX, calcY), sf::Color(int(( current_universe_pointer->GetPoint(event_time, n].getPointPosition()+1)*127),colourY,255,255)));
     //std::cout << "X: " << calcX << "  Y: " << calcY << std::endl;
     for (int zloop = 0; zloop < OrbConnectionList.size(); zloop++ )
     {
     if (n - l_orbPointStart == OrbConnectionList[zloop].OrbOne &&  orbital[OrbConnectionList[zloop].OrbOne].GetEnergy(event_time) > 0)
     {
     OrbConnectionList[zloop].OrbOnePosition = calcX;
     }
     if (n - l_orbPointStart == OrbConnectionList[zloop].OrbTwo &&  orbital[OrbConnectionList[zloop].OrbTwo].GetEnergy(event_time) > 0)
     {
     OrbConnectionList[zloop].OrbTwoPosition = calcX;
     }
     }
     }
     }
     if(pauseLoop % 1 == 0)
     {
     double connectionLength = 0.0;
     for (int n = 0; n < OrbConnectionList.size(); n++ )
     {
     connectionLength = OrbConnectionList[n].OrbTwoPosition - OrbConnectionList[n].OrbOnePosition;
     for (int z = n + 1; z < OrbConnectionList.size(); z++ )
     {
     if(connectionLength > OrbConnectionList[z].OrbTwoPosition - OrbConnectionList[z].OrbOnePosition)
     {
     iter_swap(OrbConnectionList.begin() + (n), OrbConnectionList.begin() + (z));
     }
     }
     }
     double xx2 = 0.0;
     for (int n = 0; n < OrbConnectionList.size(); n++ )
     {
     xx2 = OrbConnectionList[n].OrbTwoPosition;
     for (int z = n + 1; z < OrbConnectionList.size(); z++ )
     {
     if(OrbConnectionList[z].OrbOnePosition >= xx2)
     {
     xx2 = OrbConnectionList[z].OrbTwoPosition;
     OrbConnectionList.insert(OrbConnectionList.begin() + (n + 1), OrbConnectionList[z]);
     iter_swap(OrbConnectionList.begin() + (n + 1), OrbConnectionList.begin() + (z + 1));
     OrbConnectionList.erase(OrbConnectionList.begin() + (z + 1));
     n++;
     }
     }
     }
     }
     int yy = 350;
     double xx = 0;
     for (int n = 0; n < OrbConnectionList.size(); n++ )
     {
     if (OrbConnectionList[n].OrbOnePosition > 0.0 && OrbConnectionList[n].OrbTwoPosition > 0.0 &&  orbital[OrbConnectionList[n].OrbOne].GetEnergy(event_time) > 0 &&  orbital[OrbConnectionList[n].OrbTwo].GetEnergy(event_time) > 0)
     {
     if(yy > 0)
     {
     draw_lines.push_back(sf::Vertex(sf::Vector2f(OrbConnectionList[n].OrbOnePosition, yy), sf::Color( orbital[OrbConnectionList[n].OrbOne].GetEnergy(event_time),OrbConnectionList[n].OrbConnectionStrength,255,255)));
     draw_lines.push_back(sf::Vertex(sf::Vector2f(OrbConnectionList[n].OrbTwoPosition, yy), sf::Color( orbital[OrbConnectionList[n].OrbTwo].GetEnergy(event_time),OrbConnectionList[n].OrbConnectionStrength,255,255)));
     }
     if (OrbConnectionList[n].OrbOnePosition >= xx)
     {
     xx = OrbConnectionList[n].OrbTwoPosition;
     }
     else
     {
     xx = 0;
     yy--;
     }
     }
     }

	 */
	/*
     for(int n = 0; n < l_LineEnd; n++)
     {
     draw_lines.push_back(sf::Vertex(sf::Vector2f(( line_list[n].GetLineX1(event_time) * l_scale) + (l_screenX / 2), l_screenY - (( line_list[n].GetLineY1(event_time) * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) *  current_universe_pointer->GetPoint(event_time, n].GetXYTTL(event_time)),0,0,255)));
     draw_lines.push_back(sf::Vertex(sf::Vector2f(( line_list[n].GetLineX2(event_time) * l_scale) + (l_screenX / 2), l_screenY - (( line_list[n].GetLineY2(event_time) * l_scale) + (l_screenY / 2))), sf::Color::Color(255 - (int(255 / 8) *  current_universe_pointer->GetPoint(event_time, n].GetXYTTL(event_time)),0,0,255)));
     }
	 */
	//! window.clear();

	//!        window.pushGLStates();
	//!  window.draw(& drawQuads[0],  drawQuads.size(), sf::Quads);
	//!        window.popGLStates();

	//!        window.pushGLStates();
	//!  window.draw(& define_points[0],  define_points.size(), sf::Points);
	//!        window.popGLStates();

	//!        window.pushGLStates();
	//!  window.draw(& draw_lines[0],  draw_lines.size(), sf::Lines);
	//!        window.popGLStates();

	//! Group quads
	//!         draw_rectangles[1].setPosition(sf::Vector2f(((l_screenX / 2 ) - (20 / 2)) + (25 *  toggle), 30));
	/*
     for(int loopRectangles = 0; loopRectangles < int( draw_rectangles.size()); loopRectangles++)
     {
     draw_rectangles[loopRectangles].setPosition( current_universe_pointer->GetPoint(event_time, loopRectangles * 2.0].getPointPosition(),  current_universe_pointer->GetPoint(event_time, (loopRectangles * 2.0) + 1.0].GetPointPosition(event_time));
     //!            window.pushGLStates();
     window.draw( draw_rectangles[loopRectangles]);
     //!            window.popGLStates();
     }

     for(int loopText = 1; loopText < int( draw_text.size()); loopText++)
     {
     draw_text[loopText].SetPosition(event_time, current_universe_pointer->GetPoint(event_time, (loopText * 2.0) + (int( draw_rectangles.size()) * 2.0)].GetPointPosition(event_time),  current_universe_pointer->GetPoint(event_time, (loopText * 2.0) + 1.0 + (int( draw_rectangles.size()) * 2.0)].GetPointPosition(event_time));
     //!            window.pushGLStates();
     window.draw( draw_text[loopText]);
     //!            window.popGLStates();
     //!            std::cout << "X:" <<  current_universe_pointer->GetPoint(event_time, (loopText * 2) + (int( draw_rectangles.size())*2)].GetPointPosition(event_time) << " Y:" <<  current_universe_pointer->GetPoint(event_time, (loopText * 2) + 1 + (int( draw_rectangles.size())*2)].GetPointPosition(event_time) << std::endl;
     }

	 */

	//! Continue interaction until window closed

	render_window_interactor->Start();
	sleep(10);
	if(device_attached)
	{
		caerDeviceDataStop(usb_handle);
		caerDeviceClose(&usb_handle);
		printf("Dynap-se shutdown successful.\n");
	}
	//! Empty vectors before exiting (in reverse of creation)
	//!    for(int dloop = int( current_universe_pointer->GetPoints(event_time).size()); dloop > 0; --dloop) delete (& current_universe_pointer->GetPoint(event_time, dloop - 1]);
	std::cout << "Clearing memory..." << std::endl;
	Py_XDECREF(pFunc);
	Py_DECREF(pModule);
	Py_Finalize();
	orbital.clear();
	dendrite.clear();
	neuron.clear();
	Spike.clear();
	//!    point_list.clear();
	matter_list.clear();
	composite_forceparticle_list.clear();
	elementary_force_list.clear();
	elementary_particle_list.clear();
	dimension_list.clear();
	universe_list.clear();

	return EXIT_SUCCESS;
}

vtkSmartPointer<vtkPolyData> TransformBack(vtkSmartPointer<vtkPoints> pt, vtkSmartPointer<vtkPolyData> pd)
{
	//! The reconstructed surface is transformed back to where the
	//! original points are. (Hopefully) it is only a similarity
	//! transformation.

	//! 1. Get bounding box of pt, get its minimum corner (left, bottom, least-z), at c0, pt_bounds

	//! 2. Get bounding box of surface pd, get its minimum corner (left, bottom, least-z), at c1, pd_bounds

	//! 3. compute scale as:
	//!       scale = (pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0]);

	//! 4. transform the surface by T := T(pt_bounds[0], [2], [4]).S(scale).T(-pd_bounds[0], -[2], -[4])



	//! 1.
	double pt_bounds[6];  //! (xmin,xmax, ymin,ymax, zmin,zmax)
	pt->GetBounds(pt_bounds);


	//! 2.
	double pd_bounds[6];  //! (xmin,xmax, ymin,ymax, zmin,zmax)
	pd->GetBounds(pd_bounds);

	//!   //! test, make sure it is isotropic
	//!   std::cout<<(pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0])<<std::endl;
	//!   std::cout<<(pt_bounds[3] - pt_bounds[2])/(pd_bounds[3] - pd_bounds[2])<<std::endl;
	//!   std::cout<<(pt_bounds[5] - pt_bounds[4])/(pd_bounds[5] - pd_bounds[4])<<std::endl;
	//!   //! TEST


	//! 3
	double scale = (pt_bounds[1] - pt_bounds[0])/(pd_bounds[1] - pd_bounds[0]);


	//! 4.
	vtkSmartPointer<vtkTransform> transp = vtkSmartPointer<vtkTransform>::New();
	transp->Translate(pt_bounds[0], pt_bounds[2], pt_bounds[4]);
	transp->Scale(scale, scale, scale);
	transp->Translate(- pd_bounds[0], - pd_bounds[2], - pd_bounds[4]);

	vtkSmartPointer<vtkTransformPolyDataFilter> tpd = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	tpd->SetInputData(pd);
	tpd->SetTransform(transp);
	tpd->Update();


	return tpd->GetOutput();
}
