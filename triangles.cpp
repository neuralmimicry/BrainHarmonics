#include <glad/glad.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include <iostream>


using std::vector;
using std::rand;
using std::srand;

typedef GLfloat gfloat;



//freeze the animation
bool freeze = false;

//rotation angles and zoom factor for 3D rendering
GLfloat alpha=210.0f, beta=-70.0f, zoom=2.0f;
GLboolean locked = GL_FALSE;

int cursorX = 0;
int cursorY = 0;

typedef struct {
    gfloat x,y,z;
    gfloat r,g,b,a;
} Vertex;


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
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_SPACE:
			freeze=!freeze;
			break;
		case GLFW_KEY_LEFT:
			alpha += 5.0f;
			break;
		case GLFW_KEY_RIGHT:
			alpha -= 5.0f;
			break;
		case GLFW_KEY_UP:
			beta -= 5.0f;
			break;
		case GLFW_KEY_DOWN:
			beta += 5.0f;
			break;
		case GLFW_KEY_PAGE_UP:
			zoom -= 0.25f;
			if (zoom < 0.0f)
				zoom = 0.0f;
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
		locked = GL_TRUE;
	}
	else
	{
		locked = GL_FALSE;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

//========================================================================
// Callback function for cursor motion events
//========================================================================
void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	//if the mouse button is pressed
	if (locked)
	{
		alpha += (GLfloat) (x - cursorX) / 10.0f;
		beta += (GLfloat) (y - cursorY) / 10.0f;
	}
	//update the cursor position
	cursorX = (int) x;
	cursorY = (int) y;
}

//========================================================================
// Callback function for scroll events
//========================================================================
void scroll_callback(GLFWwindow* window, double x, double y)
{
	zoom += (float) y / 4.0f;
	if (zoom < 0.0f)
		zoom = 0.0f;
}

/*  Purpose: calls back when the mouse has changed perspective position 
 *   
 */
void framebuffer_size_callback (GLFWwindow* window,int width,int height) {
    const float fovY = 45.0f; // this is the angle for the two lines running between top and bottom corners of the near and far plane
    const float front = 0.1f;// distance to the near clipping plane
    const float back =128.0f;// distance to the far 
    float ratio= 1.0f;
    if (height >0) {
        ratio =(float) width/(float) height;
    }
    // virtual camera
    glViewport(0,0,width,height);
    // matrix operations to be able to project to the matrix stack 
    glMatrixMode(GL_PROJECTION);
    // identity matrix is the default here
    glLoadIdentity();
    //perspective camera
    const double DEG2RAD = 3.1459/180;
    double tangent = tan(fovY/2*DEG2RAD);
    double height_f = front*tangent;
    double width_f = height_f * ratio;
    //make the projection matrix
    glFrustum(-width_f,width_f,-height_f,height_f,front,back);
}
   


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
gfloat randCeil   (float ceil) {
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

                Vertex v = {randCeil(1),randCeil(1),0.0f,randCeil(1),randCeil(1),randCeil(1)};
                vertex_vect.push_back(v);
                std::cout << v.x << " "  <<v.y << " "  <<v.z<< std::endl;
            }
            all_v.push_back(vertex_vect);
        }
    }
    makeTriangles(all_v);
}


int main () {
    //
    unsigned int seed = 5;
    std::srand(seed);
    // making window
    GLFWwindow* window;
    int width,height;
    if(!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640,480,"first exercise",NULL,NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	//initialize the callbacks for event handling
	//keyboard input callback
	glfwSetKeyCallback(window, key_callback);
	//framebuffer size callback - i.e., window resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//mouse movement callback
	glfwSetCursorPosCallback(window, cursor_position_callback);
	//mouse scroll callback
	glfwSetScrollCallback(window, scroll_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//get the frame buffer (window) size
	glfwGetFramebufferSize(window, &width, &height);
	//initial call to the framebuffer callback, and initialize the OpenGL
	//camera and other properties there
	framebuffer_size_callback(window, width, height);


	//enable anti-aliasing
	glEnable(GL_BLEND);
	//smooth the points
	glEnable(GL_LINE_SMOOTH);
	//smooth the lines
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//needed for alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST) ;

	//initialize all parameters
	float sigma = 0.1f;
	float sign = 1.0f;
	float step_size = 0.01f;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//draw the scene
		//switch to modelview so the tranformation applies to entire model
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//move the object back and forth based on the zoom level
		glTranslatef(0.0, 0.0, -zoom);
		// rotate beta degrees around the x-axis
		glRotatef(beta, 1.0, 0.0, 0.0);
		// rotate alpha degrees around the z-axis
		glRotatef(alpha, 0.0, 0.0, 1.0);

        trianglesSet(5,height,width);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}




    
