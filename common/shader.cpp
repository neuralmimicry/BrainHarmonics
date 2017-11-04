#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "shader.hpp"

/*  Purpose: helper function for reading file 
 *   
 */
std::string readSourceFile (const char * path) {
    std::string code; 
    std::ifstream file_stream(path,std::ios::in);
    if(file_stream.is_open()) {
        std::string line = "";
        while(getline(file_stream,line)) // nice way to get all words
            code += "\n" + line;
        file_stream.close();
        return code;
    } else {
        printf("couldn't open");
        return "";
    }

}

/*  Purpose: compile the code (interesting!!) 
 *   
 */
void CompileShader (std::string program_code,GLuint shader_id) {
    printf("going to compile the shader\n");
    GLint result = GL_FALSE; 
    int infolog_length;
    char const * program_code_pointer = program_code.c_str();
    glShaderSource(shader_id,1,&program_code_pointer,NULL);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id,GL_COMPILE_STATUS,&result);
    glGetShaderiv(shader_id,GL_INFO_LOG_LENGTH,&infolog_length);
    if ( infolog_length > 0) {
        std::vector<char> error_msg(infolog_length+1);
        glGetShaderInfoLog(shader_id,infolog_length,NULL,&error_msg[0]);
        printf("%s\n",&error_msg[0]);
    }
    printf("finished compiling\n");
}
   
/*  Purpose: actually load the shaders 
 *   
 */
GLuint LoadShaders (const char * vertex_file_path,const char * fragment_file_path) {
    printf("loading the shaders\n");
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertex_shader_code= readSourceFile(vertex_file_path);
    if(vertex_shader_code == "") return 0;
    std::string fragment_shader_code = readSourceFile(fragment_file_path);
    if(fragment_shader_code == "") return 0;
    printf("compiling thhe vertex shader: %s\n",vertex_file_path);
    CompileShader(vertex_shader_code,vertex_shader_id);
    printf("compiling the fragment shader: %s\n",fragment_file_path);
    CompileShader(fragment_shader_code,fragment_shader_id);
    //second half
    GLint result = GL_FALSE;
    int infolog_length;
    printf("linking \n");
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id,vertex_shader_id);
    glAttachShader(program_id,fragment_shader_id);
    glLinkProgram(program_id);
    // linking complete

    //double check the linking
    //similar to checking the compiling, this could be a single function that we use?
    glGetProgramiv(program_id,GL_LINK_STATUS,&result);
    glGetProgramiv(program_id,GL_INFO_LOG_LENGTH,&infolog_length);
    if ( infolog_length > 0 ) {
        std::vector<char> program_error_msg(infolog_length+1);
        glGetProgramInfoLog(program_id,infolog_length,NULL,&program_error_msg[0]);// probably populates the error message
        printf("%s\n",&program_error_msg[0]);
    } else {
        printf("link success!");
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
   
