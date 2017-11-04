#include <glad/glad.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include "common/shader.hpp"
#include <stdio.h>

int main () {
    // making window
    GLFWwindow* window;
    if(!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640,480,"book shader exercise",NULL,NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "made window now shader loading " << std::endl;    
    
    // compile shaders and stuff
    glfwMakeContextCurrent(window);
    // possible time to include the glad or other extension loader library tool
    // this line must be called before we have access to the glfunctions
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // create the things needed for the actual drawing
    GLuint program = LoadShaders("../simple.vert","../simple.frag");
    GLuint vertex_array;
    glGenVertexArrays(1,&vertex_array);
    glBindVertexArray(vertex_array);


    while(!glfwWindowShouldClose(window)){
        // setting up viewport
        float ratio;
        int width,height;

        glfwGetFramebufferSize(window,&width,&height);
        ratio = (float) width/(float)height;
        glViewport(0,0,width,height);
        const GLfloat back_color[] = {0.0f,0.2f,0.0f,1.0f};
        glClearBufferfv(GL_COLOR,0,back_color);

        //setting up the camera its a matrix I guess?
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //what is the -1.f buisiness?this is for the float casting on the fly, its more appropriate according to arthur
        glOrtho(-ratio,ratio,-1.f,1.f,1.f,-1.f);
        glMatrixMode(GL_MODELVIEW);
        // this is getting the perspective matrix, but making it be equal to all ones I think
        glLoadIdentity();
        glUseProgram(program);
        //call use prog, and then move into the attribute assignment
        GLfloat atrb[] = {(float) sin(glfwGetTime()),
            (float) cos(glfwGetTime()),0.0f,0.5f};
        float modVal = rand() / (1.0f * RAND_MAX * 10);
        GLfloat color[] = {(float) cos(glfwGetTime())+modVal,(float) sin(glfwGetTime())+modVal,0.0f,1.0f};
        glVertexAttrib4fv(0,atrb);
        glVertexAttrib4fv(1,color);
        glDrawArrays(GL_TRIANGLES,0,3);
        // swap the buffering for the window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




    
    
