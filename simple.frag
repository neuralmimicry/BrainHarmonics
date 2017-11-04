#version 420

in VS_COLOR_PIPE {
    vec4 color;
} fs_in;

out vec4 color_out;
void main() {
    color_out = fs_in.color;
}
