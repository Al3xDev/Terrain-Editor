#version 440 core
layout(location = 0) in vec3 position;
uniform mat4 v;
uniform mat4 p;
uniform float x;
uniform float z;
out float pd;
void main()
{
    gl_Position=p * v * vec4(position.x,position.y,position.z,1.0f);
    pd=sqrt((z-position.z)*(z-position.z)+(x-position.x)*(x-position.x));
}
