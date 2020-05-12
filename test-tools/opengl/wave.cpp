/*****************************************************************************
 * Wave Simulation in OpenGL
 * (C) 2002 Jakob Thomsen
 * http://home.in.tum.de/~thomsen
 * Modified for GLFW by Sylvain Hellegouarch - sh@programmationworld.com
 * Modified for variable frame rate by Marcus Geelnard
 * 2003-Jan-31: Minor cleanups and speedups / MG
 * 2010-10-24: Formatting and cleanup - Camilla Berglund
 *****************************************************************************/

#if defined(_MSC_VER)
 // Make MS math.h define M_PI
 #define _USE_MATH_DEFINES
#endif
#include <glad/glad.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include <iostream>



#include <stdio.h>
#include <stdlib.h>
#include <linmath.h>

using std::vector;
using std::rand;
using std::srand;


// Maximum delta T to allow for differential calculations
#define MAX_DELTA_T 0.01

// Animation speed (10.0 looks good)
#define ANIMATION_SPEED 10.0

GLfloat alpha = 210.f, beta = -70.f;
GLfloat zoom = 2.f;

double cursorX;
double cursorY;

typedef GLfloat gfloat;

struct Vertex
{
    GLfloat x, y, z;
    GLfloat r, g, b,a;
};

vector<vector<Vertex>> all_v;

/*  Purpose: make a triangle given vertices 
 *   
 */
void makeTriangle (vector<Vertex> vct) {
    glBegin(GL_TRIANGLES); 
    // iterate over the vertices
    for (Vertex v: vct) {
        glColor4f(v.r,v.g,v.b,v.a);
        glVertex3f(v.x,v.y,v.z);
    }
    glEnd();
}


/*  Purpose: generate all the triangles for the vector set 
 *   
 */
void makeTriangles (vector<vector<Vertex>> vct) {
    for (vector<Vertex> subV:vct) {
            makeTriangle(subV);
    }
}
   




/*  Purpose: this function gives a number between 0 and ceil 
 *   
 */
gfloat randCeil  (float ceil) {
    float randVal = rand();
    float val = randVal/RAND_MAX*(2*ceil) -ceil;
    //
    gfloat returnVal = (gfloat) val*ceil;
    //std::cout << "randval " << randVal << "randval" << val << "top is "<< RAND_MAX  << " rv is " << returnVal << std::endl;

    return returnVal;
}
/*  Purpose: make group of triangles 
 *   
 */
void trianglesSet (int number,int height,int width) {
    auto animTime = fmod(glfwGetTime(),5)*10;
    std::cout << animTime  << std::endl;
    if( animTime < 1.0f) {
        std::cout << "in creating vertex"  << std::endl;
        for ( int i = 0 ;i < number;i++ ) {
            vector<Vertex> vertex_vect;
            for ( int j = 0;j < 3;j++ ) {

                Vertex v = {randCeil(1),randCeil(1),randCeil(1),randCeil(1),randCeil(1),randCeil(1)};
                vertex_vect.push_back(v);
                std::cout << v.x << " "  <<v.y << " "  <<v.z<< std::endl;
            }
            all_v.push_back(vertex_vect);
        }
    }
    makeTriangles(all_v);
}

   



//========================================================================
// Print errors
//========================================================================

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


//========================================================================
// Handle key strokes
//========================================================================

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_SPACE:
            break;
        case GLFW_KEY_LEFT:
            alpha += 5;
            break;
        case GLFW_KEY_RIGHT:
            alpha -= 5;
            break;
        case GLFW_KEY_UP:
            beta -= 5;
            break;
        case GLFW_KEY_DOWN:
            beta += 5;
            break;
        case GLFW_KEY_PAGE_UP:
            zoom -= 0.25f;
            if (zoom < 0.f)
                zoom = 0.f;
            break;
        case GLFW_KEY_PAGE_DOWN:
            zoom += 0.25f;
            break;
        default:
            break;
    }
}


//========================================================================
// Callback function for mouse button events
//========================================================================

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT)
        return;

    if (action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(window, &cursorX, &cursorY);
    }
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


//========================================================================
// Callback function for cursor motion events
//========================================================================

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    {
        alpha += (GLfloat) (x - cursorX) / 10.f;
        beta += (GLfloat) (y - cursorY) / 10.f;

        cursorX = x;
        cursorY = y;
    }
}


//========================================================================
// Callback function for scroll events
//========================================================================

void scroll_callback(GLFWwindow* window, double x, double y)
{
    zoom += (float) y / 4.f;
    if (zoom < 0)
        zoom = 0;
}


//========================================================================
// Callback function for framebuffer resize events
//========================================================================

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    float ratio = 1.f;
    mat4x4 projection;// don't know what the mat4x4 is 

    if (height > 0)
        ratio = (float) width / (float) height;

    // Setup viewport
    glViewport(0, 0, width, height);

    // Change to the projection matrix and set our viewing volume
    glMatrixMode(GL_PROJECTION);
    mat4x4_perspective(projection,
                       60.f * (float) M_PI / 180.f,
                       ratio,
                       1.f, 1024.f);
    glLoadMatrixf((const GLfloat*) projection);
}


void draw_scene(GLFWwindow* window,int height,int width)
{
    float time = glfwGetTime();
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // We don't want to modify the projection matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move back
    glTranslatef(0.0, 0.0, -zoom);
    // Rotate the view
    glRotatef(beta*(time/100), 1.0, 0.0, 0.0);
    glRotatef(alpha*(time/100), 0.0, 0.0, 1.0);

    trianglesSet(5,height,width);

    glfwSwapBuffers(window);
}


//========================================================================
// main
//========================================================================

int main(int argc, char* argv[])
{
    unsigned int seed = 5;
    std::srand(seed);
    GLFWwindow* window;
    double t, dt_total, t_old;
    int width, height;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);


    while (!glfwWindowShouldClose(window))
    {
        // Draw wave grid to OpenGL display
        draw_scene(window,height,width);
        glfwPollEvents();
    }

    exit(EXIT_SUCCESS);
}

