#version 450 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;

out vec2 vUV;

void main()
{
    gl_Position = model * vec4(aPos, 1.0);

    vec2 pos = aPos.xy;
    vUV = pos * 0.5 + 0.5;
}
