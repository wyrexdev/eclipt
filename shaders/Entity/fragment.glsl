#version 450 core

uniform vec4 backgroundColor;

in vec2 vUV;
out vec4 FragColor;

uniform float radiusTL;
uniform float radiusTR;
uniform float radiusBL;
uniform float radiusBR;

void main()
{
    float x = vUV.x;
    float y = vUV.y;

    float r = 0.0;

    if (x < radiusTL && y > 1.0 - radiusTL) {
        float dx = radiusTL - x;
        float dy = y - (1.0 - radiusTL);
        if (dx*dx + dy*dy > radiusTL*radiusTL)
            discard;
    }

    if (x > 1.0 - radiusTR && y > 1.0 - radiusTR) {
        float dx = x - (1.0 - radiusTR);
        float dy = y - (1.0 - radiusTR);
        if (dx*dx + dy*dy > radiusTR*radiusTR)
            discard;
    }

    if (x < radiusBL && y < radiusBL) {
        float dx = radiusBL - x;
        float dy = radiusBL - y;
        if (dx*dx + dy*dy > radiusBL*radiusBL)
            discard;
    }

    if (x > 1.0 - radiusBR && y < radiusBR) {
        float dx = x - (1.0 - radiusBR);
        float dy = radiusBR - y;
        if (dx*dx + dy*dy > radiusBR*radiusBR)
            discard;
    }

    FragColor = backgroundColor;
}