#version 420
void main () {
    const vec4 vertices[3] = vec4[3](vec4(.25,-.25,.5,1.0),
    vec4(-.25,.25,.5,1.0),
    vec4(-.25,-.25,.5,1.0));

    gl_Position= vertices[gl_VertexID];
}
