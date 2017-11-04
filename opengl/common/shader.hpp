#ifndef SHADER_HPP
#define SHADER_HPP

#include "common.h"
/*  Purpose: bring in the shader 
 *   
 */
GLuint LoadShaders (const char * vertex_file_path,const char * fragment_file_path,const char * tcs_file_path,const char * tes_file_path);
#endif
