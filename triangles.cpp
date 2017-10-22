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

typedef struct {
    gfloat x,y,z;
    gfloat r,g,b,a;
} Vertex;

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
    if(!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640,480,"first exercise",NULL,NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    // possible time to include the glad or other extension loader library tool
    //
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while(!glfwWindowShouldClose(window)){
        // setting up viewport
        float ratio;
        int width,height;

        glfwGetFramebufferSize(window,&width,&height);
        ratio = (float) width/(float)height;
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT);

        //setting up the camera its a matrix I guess?
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //what is the -1.f buisiness?this is for the float casting on the fly, its more appropriate according to arthur
        glOrtho(-ratio,ratio,-1.f,1.f,1.f,-1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // drawing part
        
        trianglesSet(5,height,width);    
        
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


    
