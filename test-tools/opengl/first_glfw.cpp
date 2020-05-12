#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

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
        //rotating triangle part//
        glRotatef((float)glfwGetTime()*50.f,0.f,0.f,1.f);
        glBegin(GL_TRIANGLES);// is this already invoking the opengl code?
        glColor3f(1.f,1.f,0.f); // i think tihs is binding the vertices to the colors
        glVertex3f(-0.6f,-0.4f,0.f);
        glColor3f(1.f,0.f,0.f); // i think tihs is binding the vertices to the colors
        glVertex3f(0.6f,-0.4f,0.f);

        glColor3f(1.f,1.f,0.f); // i think tihs is binding the vertices to the colors
        glVertex3f(0.f,0.6f,0.f);
        glEnd();
        // swap the buffering for the window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




    
    
