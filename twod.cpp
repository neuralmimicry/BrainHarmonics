#include <glad/glad.h>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>


using namespace std;


typedef GLfloat gfloat;

typedef struct {
    gfloat x,y,z;
    gfloat r,b,g,a;

} Vertex;

void drawPoint (Vertex v,gfloat size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor4f(v.r,v.b,v.g,v.a);// how to unpack in c++?
    glVertex3f(v.x,v.y,v.z);
    glEnd();
}

void makePointsDance() {
    for (gfloat i = 0;i<= 1.0f;i+=.2f) {
        //
        double control = 10.0d;
        int scale = fmod(glfwGetTime(),control);
        Vertex v= {(gfloat) i/scale,(gfloat) i,0.0f,0.0f,0.0f,1.0f,1.0f};
        std::cout << scale  << std::endl;
        drawPoint(v,(gfloat)5.0f);
    }
}

/*  Purpose: line segment draws a straight piece between the vertices passed in  
    
*/
void lineSegment (Vertex v1, Vertex v2,gfloat width) {
    glLineWidth(width); 
    glBegin(GL_LINES);
    glColor4f(v1.r,v1.g,v1.b,v1.a);
    glVertex3f(v1.x,v1.y,v1.z);
    glColor4f(v2.r,v2.g,v2.b,v2.a);
    glVertex3f(v2.x,v2.y,v2.z);
    glEnd();
}
 
void lineDance() {
    for (gfloat i = 0;i<= 1.0f;i+=.2f) {
        //
        double control = 10.0d;
        int scale = fmod(glfwGetTime(),control);
        Vertex v1= {(gfloat) i/scale,(gfloat) i,0.0f,0.0f,0.0f,1.0f*i,1.0f};
        Vertex v2= {(gfloat) (i-.2f)/scale,(gfloat) (i-.2f),0.0f,0.0f,0.0f,1.0f*i,1.0f};
        std::cout << scale  << std::endl;
        lineSegment(v1,v2,20.0f -20.0f*i );
    }
}

void gridLines(gfloat gridWidth,int height,int width) {
    // create the vertical lines
    for (gfloat xpos=-width; xpos < width;xpos+=gridWidth) {
        Vertex v1 = {xpos,-height,0.0f, 1.0f,1.0f,1.0f,1.0f};  
        Vertex v2 = {xpos,height,0.0f, 1.0f,1.0f,1.0f,1.0f};  
        lineSegment(v1,v2,1.0f);
    }
    for (gfloat ypos=-height; ypos < height;ypos+=gridWidth) {
        Vertex v1 = {-width,ypos,0.0f, 1.0f,1.0f,1.0f,1.0f};  
        Vertex v2 = {width,ypos,0.0f, 1.0f,1.0f,1.0f,1.0f};  
        lineSegment(v1,v2,1.0f);
    }
    // add a point at each vertex 
}
  
/*  Purpose: grid form using points instead of lines 
    
*/
void gridPoints (gfloat gridWidth,int yspan,int height,int width) {
    //just trying the  
    for(gfloat xpos=-width;xpos < width;xpos+=gridWidth) {
        for(gfloat ypos=-yspan*gridWidth;ypos < yspan*gridWidth;ypos+= gridWidth) {
            float spanColor = sqrt(pow(ypos/(yspan*gridWidth),2));
            float animColor = fmod(glfwGetTime(),15);
            Vertex v = {xpos,ypos,0.0f, spanColor ,animColor,0.0f,1.0f};  
            drawPoint(v,10.0f);
        }
    }
    std::cout << "done"  << std::endl;
}
   


int main () {
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
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // probably want this before any of the calls to gl
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);// what does the hinting do?
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

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
        gridLines(.05f,height,width);
        gridPoints(.05f,20,height,width);
        //create a loop to draw the points
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




    
    
