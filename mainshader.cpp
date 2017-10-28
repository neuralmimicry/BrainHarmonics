
//=======================================================================
// Authors: Raymond Lo and William Lo
// Chapter 4 - Modern OpenGL - Texture Mapping with 2D images
// Copyrights & Licenses:
//=======================================================================
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std;

//Global variables
GLFWwindow* window;


//default shader programs
static const char * frag_shader_text = 
"#version 420\n"
"in vec3 color;\n"
"out vec4 color_out;\n"
"void main() { "
"    color_out = vec4(color,1.0);\n"
"}";

static const char * vert_shader_text = 
"#version 420\n"
"in vec3 position;\n"
"in vec3 color_in;\n"
"out vec3 color;\n"
"void main () {\n"
"    color = color_in;\n"
"    gl_Position= vec4(position,1.0);\n"
"}\n";

// values for projection matrix, and shader uniform values, ?? don't know what this means presently

/* Frustum configuration */
static GLfloat view_angle = 45.0f;
static GLfloat aspect_ratio = 4.0f/3.0f;
static GLfloat z_near = 1.0f;
static GLfloat z_far = 100.f;

/* Projection matrix */
static GLfloat projection_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

/* Model view matrix */
static GLfloat modelview_matrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

/* Store uniform location for the shaders
 * Those values are setup as part of the process of creating
 * the shader program. They should not be used before creating
 * the program.
 */
static GLuint mesh;
static GLuint mesh_vbo[4];



// shader helper funcitonss
/* Creates a shader object of the specified type using the specified text
 */
static GLuint make_shader(GLenum type, const char* text)
{
    GLuint shader;
    GLint shader_ok;
    GLsizei log_length;
    char info_log[8192];

    shader = glCreateShader(type);
    if (shader != 0)
    {
        std::cout << "about to compile " << std::endl;
        glShaderSource(shader, 1, (const GLchar**)&text, NULL);
        glCompileShader(shader);
        std::cout << "actually compiled " << std::endl;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
        if (shader_ok != GL_TRUE)
        {
            fprintf(stderr, "ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex" );
            glGetShaderInfoLog(shader, 8192, &log_length,info_log);
            fprintf(stderr, "ERROR: \n%s\n\n", info_log);
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

// creation of the program object
/* Creates a program object using the specified vertex and fragment text
 */
static GLuint make_shader_program(const char* vs_text, const char* fs_text)
{
    GLuint program = 0u;
    GLint program_ok;
    GLuint vertex_shader = 0u;
    GLuint fragment_shader = 0u;
    GLsizei log_length;
    char info_log[8192];

    vertex_shader = make_shader(GL_VERTEX_SHADER, vs_text);
    if (vertex_shader != 0u)
    {
        fragment_shader = make_shader(GL_FRAGMENT_SHADER, fs_text);
        if (fragment_shader != 0u)
        {
            /* make the program that connect the two shader and link it */
            program = glCreateProgram();
            if (program != 0u)
            {
                /* attach both shader and link */
                glAttachShader(program, vertex_shader);
                glAttachShader(program, fragment_shader);
                glLinkProgram(program);
                glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

                if (program_ok != GL_TRUE)
                {
                    fprintf(stderr, "ERROR, failed to link shader program\n");
                    glGetProgramInfoLog(program, 8192, &log_length, info_log);
                    fprintf(stderr, "ERROR: \n%s\n\n", info_log);
                    glDeleteProgram(program);
                    glDeleteShader(fragment_shader);
                    glDeleteShader(vertex_shader);
                    program = 0u;
                }
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Unable to load fragment shader\n");
            glDeleteShader(vertex_shader);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Unable to load vertex shader\n");
    }
    return program;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}




int main(int argc, char** argv)
{
    GLFWwindow* window;
    int iter;
    double dt;
    double last_update_time;
    int frame;
    float f;
    GLint uloc_modelview;
    GLint uloc_project;
    int width, height;

    GLuint shader_program;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(800, 600, "GLFW OpenGL3 Heightmap demo", NULL, NULL);
    if (! window )
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Register events callback */

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    /* Prepare opengl resources for rendering */
    shader_program = make_shader_program(vert_shader_text, frag_shader_text);

    if (shader_program == 0u)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glUseProgram(shader_program);
    uloc_project   = glGetUniformLocation(shader_program, "project");
    uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
    f = 1.0f / tanf(view_angle / 2.0f);
    projection_matrix[0]  = f / aspect_ratio;
    projection_matrix[5]  = f;
    projection_matrix[10] = (z_far + z_near)/ (z_near - z_far);
    projection_matrix[11] = -1.0f;
    projection_matrix[14] = 2.0f * (z_far * z_near) / (z_near - z_far);
    glUniformMatrix4fv(uloc_project, 1, GL_FALSE, projection_matrix);

    /* Set the camera position */
    modelview_matrix[12]  = -5.0f;
    modelview_matrix[13]  = -5.0f;
    modelview_matrix[14]  = -20.0f;
    glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix);

    /* Create mesh data */
    /* Create vao + vbo to store the mesh */
    /* Create the vbo to store all the information for the grid and the height */

    /* setup the scene ready for rendering */
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* main loop */
    while (!glfwWindowShouldClose(window))
    {
        /* render the next frame */
        glClear(GL_COLOR_BUFFER_BIT);

        /* display and process events through callbacks */
        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Check the frame rate and update the heightmap if needed */
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

