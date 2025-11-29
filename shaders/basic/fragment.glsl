#version 450 core

uniform vec4 backgroundColor;
uniform vec4 borderColor;
uniform float borderSize;
uniform bool drawBorder;

uniform sampler2D textTexture;
uniform bool hasText;
uniform bool useMSDF;
uniform vec4 textColor;
uniform float msdfRange;

in vec2 vShapeUV;
in vec2 vTextUV;
out vec4 FragColor;

uniform float radiusTL;
uniform float radiusTR;
uniform float radiusBL;
uniform float radiusBR;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    float x = vShapeUV.x;
    float y = vShapeUV.y;

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

    float distLeft   = x;
    float distRight  = 1.0 - x;
    float distBottom = y;
    float distTop    = 1.0 - y;

    float edgeDist = min(min(distLeft, distRight),
                         min(distTop, distBottom));

    if (x < radiusTL && y > 1.0 - radiusTL) {
        float dx = radiusTL - x;
        float dy = y - (1.0 - radiusTL);
        float d = radiusTL - sqrt(dx*dx + dy*dy);
        edgeDist = d;
    }

    if (x > 1.0 - radiusTR && y > 1.0 - radiusTR) {
        float dx = x - (1.0 - radiusTR);
        float dy = y - (1.0 - radiusTR);
        float d = radiusTR - sqrt(dx*dx + dy*dy);
        edgeDist = d;
    }

    if (x < radiusBL && y < radiusBL) {
        float dx = radiusBL - x;
        float dy = radiusBL - y;
        float d = radiusBL - sqrt(dx*dx + dy*dy);
        edgeDist = d;
    }

    if (x > 1.0 - radiusBR && y < radiusBR) {
        float dx = x - (1.0 - radiusBR);
        float dy = radiusBR - y;
        float d = radiusBR - sqrt(dx*dx + dy*dy);
        edgeDist = d;
    }

    if (hasText) {
        float alpha;

        if (useMSDF) {
            vec3 msdf = texture(textTexture, vTextUV).rgb;
            float sd = median(msdf.r, msdf.g, msdf.b) - 0.5;
            alpha = clamp(sd / fwidth(sd) + 0.5, 0.0, 1.0);
        } else {
            alpha = texture(textTexture, vTextUV).r;
        }

        if(alpha < 0.01) 
            discard;

        FragColor = vec4(textColor.rgb, alpha * textColor.a);
        return;
    }

    bool isBorder = drawBorder && (edgeDist >= 0.0 && edgeDist < borderSize);
    if(isBorder) {
        FragColor = borderColor;
        return;
    }

    FragColor = backgroundColor;
    
    if(drawBorder) {
        discard;
    }
}