#version 420

//practice an interface block

out VS_COLOR_PIPE {
    vec4 color;
} vs_out;

layout(location = 0) in vec4 offset;
layout(location = 1) in vec4 color;

void main () {
    const vec4 vertices[3] = vec4[3](vec4(.25,-.25,.5,1.0),
    vec4(-.25,.25,.5,1.0),
    vec4(-.25,-.25,.5,1.0));
    
    gl_Position= vertices[gl_VertexID] * offset+ offset;
    vs_out.color= color;
}
